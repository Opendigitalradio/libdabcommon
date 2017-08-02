#ifndef DABCOMMON_TYPES__QUEUE
#define DABCOMMON_TYPES__QUEUE

#include <array>
#include <atomic>
#include <condition_variable>
#include <cstddef>
#include <cstring>
#include <mutex>
#include <utility>
#include <vector>

#ifdef CUTE_TESTING
namespace dab { namespace test { namespace type { namespace queue {
struct enqueueing_tests;
struct dequeueing_tests;
}}}}
#endif

namespace dab
  {

  namespace internal
    {

    /**
     * The default block size used by the queue
     */
    std::size_t constexpr kQueueDefaultBlockSize{8192};

    /**
     * The default number of blocks in a block group
     */
    std::size_t constexpr kQueueDefaultGroupSize{512};

    /**
     * @internal
     * @brief A thread-safe block-allocated SPSC queue
     *
     * This thread-safe queue is designed for SPSC scenarios. It manages memory in a blockwise fashion. The block size, as well
     * as the desired block group size can be specified as template parameters.
     *
     * @tparam ValueType The type of the elements contained in queue
     * @tparam BlockSize The size of the blocks allocated by the queue
     * @tparam GroupSize The size of the block allocation steps
     *
     * @since 1.0.1
     * @author Felix Morgner
     */
    template<typename ValueType, std::size_t BlockSize = kQueueDefaultBlockSize, std::size_t GroupSize = kQueueDefaultGroupSize>
    struct queue
      {
      static auto constexpr block_size = BlockSize;
      static auto constexpr group_size = GroupSize;
      static auto constexpr alloc_size = block_size * group_size;

      /**
       * @brief Construct an empty queue
       *
       * @param nofInitialGroups The number of block groups to preallocate during construction
       */
      explicit queue(std::size_t const nofInitialGroups = 1) : m_backingStore(alloc_size * nofInitialGroups)
        {
        }

      /**
       * @brief Get the current number of elements in the queue
       */
      std::size_t size() const
        {
        auto lock = std::unique_lock<std::mutex>{m_mutex};
        return m_size;
        }

      /**
       * @brief Get the approximate number of elements in the queue
       */
      std::size_t approximate_size() const
        {
        return m_size;
        }

      /**
       * @brief Enqueue a single element into the queue
       *
       * @note This call blocks until the element can be enqueued.
       */
      void enqueue(ValueType const & elem)
        {
        auto lock = std::unique_lock<std::mutex>{m_mutex};
        do_enqueue(elem);
        }

      /**
       * @brief Enqueue a single element into the queue
       *
       * @note This call blocks until the element can be enqueued.
       */
      void enqueue(ValueType && elem)
        {
        auto lock = std::unique_lock<std::mutex>{m_mutex};
        do_enqueue(std::move(elem));
        }

      /**
       * @brief Enqueue an arbitrarily sized block of elements into the queue
       *
       * @note This call blocks until the block can be enqueued.
       */
      void enqueue(std::vector<ValueType> const & block)
        {
        auto lock = std::unique_lock<std::mutex>{m_mutex};
        do_enqueue_block(block);
        }

      /**
       * @brief Enqueue an arbitrarily sized block of elements into the queue
       *
       * @note This call blocks until the block can be enqueued.
       */
      void enqueue(std::vector<ValueType> && block)
        {
        auto lock = std::unique_lock<std::mutex>{m_mutex};
        do_enqueue_block(std::move(block));
        }

      /**
       * @brief Dequeue a single element from the queue
       *
       * @note This call blocks until the element can be dequeued
       */
      void dequeue(ValueType & target)
        {
        auto lock = std::unique_lock<std::mutex>{m_mutex};
        m_hasElements.wait(lock, [&]{ return m_size > 0; });

        do_dequeue(target);
        }

      /**
       * @brief Dequeue a block of elements from the queue
       *
       * @note This call blocks until the block can be dequeued
       */
      void dequeue(std::vector<ValueType> & block)
        {
        auto lock = std::unique_lock<std::mutex>{m_mutex};
        m_hasElements.wait(lock, [&]{ return m_size >= block.size(); });

        do_dequeue_block(block);
        }


      /**
       * @brief Try to dequeue an element from the queue
       *
       * @note This call never blocks
       */
      bool try_dequeue(ValueType & target)
        {
        auto lock = std::unique_lock<std::mutex>{m_mutex};

        if(!m_size)
          {
          return false;
          }

        do_dequeue(target);
        return true;
        }

      /**
       * @brief Try to dequeue a block of elements from the queue
       *
       * @note Tis call never blocks
       */
      bool try_dequeue(std::vector<ValueType> & block)
        {
        auto lock = std::unique_lock<std::mutex>{m_mutex};

        if(m_size < block.size())
          {
          return false;
          }

        do_dequeue_block(block);
        return true;
        }

      private:
#ifdef CUTE_TESTING
        friend dab::test::type::queue::enqueueing_tests;
        friend dab::test::type::queue::dequeueing_tests;
#endif

        static auto constexpr AllocationSize = GroupSize * BlockSize;

        /**
         * @internal
         * @brief Worker function for enqueueing a single element
         *
         * @pre  size() > 0
         * @post size() == OLD(size()) - 1
         * @note This function does **NOT** lock the queue!
         */
        template<typename ElementType>
        void do_enqueue(ElementType && element)
          {
          std::size_t blockNumber{};
          std::size_t blockIndex{};
          std::tie(blockNumber, blockIndex) = enqueueing_point();

          if(blockNumber >= m_backingStore.size())
            {
            m_backingStore.resize(m_backingStore.size() + alloc_size);
            }

          m_backingStore[blockNumber * block_size + blockIndex] = std::forward<ElementType>(element);
          m_size++;
          m_hasElements.notify_one();
          }

        /**
         * @internal
         * @brief Worker function for enqueueing a block of elements
         *
         * @pre  size() >= block.size()
         * @post size() == OLD(size()) - block.size()
         * @note This function does **NOT** lock the queue!
         */
        template<typename BlockType>
        void do_enqueue_block(BlockType && block)
          {
          auto const available = m_backingStore.size();
          auto const required = block.size();

          if(required > available)
            {
            auto factor = (required - available) / AllocationSize + 1;
            m_backingStore.resize(m_backingStore.size() + alloc_size * factor);
            }

          std::size_t blockNumber{};
          std::size_t blockIndex{};
          std::tie(blockNumber, blockIndex) = enqueueing_point();

          auto target = m_backingStore.data() + blockNumber * block_size + blockIndex;
          std::memcpy(target, block.data(), required * sizeof(ValueType));
          m_size += required;
          m_hasElements.notify_one();
          }

        /**
         * @internal
         * @brief Worker function for dequeueing an element from the queue
         *
         * @pre  size() > 0
         * @post size() == OLD(size()) - 1
         * @note This function does **NOT** lock the queue
         */
        void do_dequeue(ValueType & target)
          {
          std::size_t blockNumber{};
          std::size_t blockIndex{};
          std::tie(blockNumber, blockIndex) = dequeueing_point();

          target = std::move(m_backingStore[blockNumber * block_size + blockIndex]);
          --m_size;

          if(++m_current > AllocationSize / 2)
            {
            std::memmove(m_backingStore.data(), m_backingStore.data() + m_current, m_size * sizeof(ValueType));
            m_current = 0;
            }
          }

        /**
         * @internal
         * @brief Worker function for dequeueing a block of elements from the queue
         *
         * @pre  size() >= block.size()
         * @post size() == OLD(size()) - block.size()
         * @note This function does not lock the queue
         */
        void do_dequeue_block(std::vector<ValueType> & block)
          {
          std::size_t blockNumber{};
          std::size_t blockIndex{};
          std::tie(blockNumber, blockIndex) = dequeueing_point();

          for(std::size_t idx = 0; idx < block.size(); ++idx)
            {
            std::ptrdiff_t const offset = blockNumber * block_size + blockIndex + idx;
            block[idx] = std::move(*(m_backingStore.data() + offset));
            }

          m_size -= block.size();
          if((m_current += block.size()) > m_backingStore.size() / 2)
            {
            auto base = m_backingStore.data();
            std::memmove(base, base + m_current, m_size * sizeof(ValueType));
            m_current = 0;
            }
          }

        /**
         * @internal
         * @brief Calculate the position of the first empty slot in the queue
         *
         * @return A pair consisting of the 'block number' and the 'index into the block' of the first empty slot
         */
        std::pair<std::size_t, std::size_t> enqueueing_point() const
          {
          return std::make_pair(m_size / BlockSize, m_size % BlockSize);
          }

        /**
         * @internal
         * @brief Calculate the position of the first element to be dequeued
         *
         * @pre nofElement <= size()
         *
         * @param  nofElements The number of elements to be dequeued
         * @return A pair consisting of the 'block number' and the 'index into the block' of the first element to be dequeued
         */
        std::pair<std::size_t, std::size_t> dequeueing_point() const
          {
          return std::make_pair(m_current / BlockSize, m_current % BlockSize);
          }

        std::atomic_size_t m_size{};
        std::atomic_size_t m_current{};
        std::vector<ValueType> m_backingStore{};
        std::mutex mutable m_mutex{};
        std::condition_variable m_hasElements{};
      };

    }

  }

#endif
