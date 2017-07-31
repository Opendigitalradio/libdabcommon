#ifndef DABCOMMON_TEST_TYPES__QUEUE_ENQUEUEING_SUITE
#define DABCOMMON_TEST_TYPES__QUEUE_ENQUEUEING_SUITE

#include <types/queue.h>

#include <cute/cute.h>
#include <cute/cute_suite.h>
#include <cute/extensions/descriptive_test_class.h>

#include <vector>

namespace dabi = dab::internal;

namespace dab
  {

  namespace test
    {

    namespace type
      {

      namespace queue
        {

        CUTE_DESCRIPTIVE_STRUCT(enqueueing_tests)
          {
          static cute::suite suite()
            {
            auto suite = cute::suite{};

#define LOCAL_TEST(Test) CUTE_SMEMFUN(enqueueing_tests, Test)
            suite += LOCAL_TEST(size_is_0);
            suite += LOCAL_TEST(size_after_enqueue_is_one_larger_than_before_RVR);
            suite += LOCAL_TEST(size_after_enqueue_is_one_larger_than_before_LVR);
            suite += LOCAL_TEST(size_after_enqueue_block_is_block_size_larger_than_before_RVR);
            suite += LOCAL_TEST(size_after_enqueue_block_is_block_size_larger_than_before_LVR);
            suite += LOCAL_TEST(contents_is_default_initialized);
#undef LOCAL_TEST

            return suite;
            }

          void size_is_0()
            {
            ASSERT_EQUAL(0, m_queue.size());
            }

          void size_after_enqueue_is_one_larger_than_before_RVR()
            {
            auto const before = m_queue.size();

            m_queue.enqueue(42);

            auto const after = m_queue.size();

            ASSERT_EQUAL(before + 1, after);
            }

          void size_after_enqueue_is_one_larger_than_before_LVR()
            {
            auto const before = m_queue.size();

            auto const element = 42;
            m_queue.enqueue(element);

            auto const after = m_queue.size();

            ASSERT_EQUAL(before + 1, after);
            }

          void size_after_enqueue_block_is_block_size_larger_than_before_RVR()
            {
            auto const before = m_queue.size();

            auto && block = std::vector<int>{1, 2, 3, 4};
            auto const blockSize = block.size();
            m_queue.enqueue(std::move(block));

            auto const after = m_queue.size();

            ASSERT_EQUAL(before + blockSize, after);
            }

          void size_after_enqueue_block_is_block_size_larger_than_before_LVR()
            {
            auto const before = m_queue.size();

            auto block = std::vector<int>{1, 2, 3, 4};
            m_queue.enqueue(block);

            auto const after = m_queue.size();

            ASSERT_EQUAL(before + block.size(), after);
            }

          void contents_is_default_initialized()
            {
            int constexpr dummy{};
            for(auto && block : m_queue.m_backingStore)
              {
              for(auto && element : block)
                {
                ASSERT_EQUAL(dummy, element);
                }
              }
            }

          private:
            dab::internal::queue<int, 2, 1> m_queue{};
          };

        }

      }

    }

  }

#endif
