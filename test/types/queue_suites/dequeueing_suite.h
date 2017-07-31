#ifndef DABCOMMON_TEST_TYPES__QUEUE_DEQUEUEING_SUITE
#define DABCOMMON_TEST_TYPES__QUEUE_DEQUEUEING_SUITE

#include <types/queue.h>

#include <cute/cute.h>
#include <cute/cute_suite.h>
#include <cute/extensions/descriptive_test_class.h>

#include <algorithm>
#include <chrono>
#include <future>
#include <numeric>
#include <thread>
#include <vector>

#include <cctype>
#include <cstdlib>
#include <cxxabi.h>
#include <memory>
#include <string>
#include <typeinfo>

namespace dabi = dab::internal;


namespace dab
  {

  namespace test
    {

    namespace type
      {

      namespace queue
        {

        namespace internal
          {
          static const auto kInitialData = std::vector<int>{1, 2, 3, 4, 5};
          static const auto kTimeoutTime = std::chrono::milliseconds{500};
          }

        CUTE_DESCRIPTIVE_STRUCT(dequeueing_tests)
          {
          static cute::suite suite()
            {
            auto suite = cute::suite{};

#define LOCAL_TEST(Test) CUTE_SMEMFUN(dequeueing_tests, Test)
            suite += LOCAL_TEST(size_is_one_less_after_dequeueing_an_element);
            suite += LOCAL_TEST(dequeueing_an_element_returns_the_last_enqueued);
            suite += LOCAL_TEST(size_is_block_size_less_after_dequeueing_a_block);
            suite += LOCAL_TEST(dequeueing_a_block_returns_the_last_block_size_elements_enqueued);
            suite += LOCAL_TEST(dequeueing_an_element_on_an_empty_queue_blocks);
            suite += LOCAL_TEST(dequeueing_a_block_on_an_empty_queue_blocks);
            suite += LOCAL_TEST(dequeueing_an_empty_block_on_an_empty_queue_does_not_block);
            suite += LOCAL_TEST(trying_to_dequeue_an_element_on_an_empty_queue_returns_false);
            suite += LOCAL_TEST(trying_to_dequeue_an_element_on_an_empty_queue_leaves_target_intact);
            suite += LOCAL_TEST(trying_to_dequeue_a_block_on_an_empty_queue_returns_false);
            suite += LOCAL_TEST(trying_to_dequeue_a_block_on_an_empty_queue_leaves_target_intact);
            suite += LOCAL_TEST(trying_to_dequeue_a_block_on_a_queue_with_too_few_elements_returns_false);
            suite += LOCAL_TEST(trying_to_dequeue_a_block_on_a_queue_with_too_few_elements_leaves_target_intact);
#undef LOCAL_TEST

            return suite;
            }

          dequeueing_tests()
            {
            m_queue.enqueue(internal::kInitialData);

            ASSERT_EQUAL(internal::kInitialData.size(), m_queue.size());
            }

          void size_is_one_less_after_dequeueing_an_element()
            {
            auto const before = m_queue.size();

            int target{};
            m_queue.dequeue(target);

            ASSERT_EQUAL(before - 1, m_queue.size());
            }

          void dequeueing_an_element_returns_the_last_enqueued()
            {
            int target{};
            m_queue.dequeue(target);

            ASSERT_EQUAL(internal::kInitialData.back(), target);
            }

          void size_is_block_size_less_after_dequeueing_a_block()
            {
            auto const before = m_queue.size();

            std::vector<int> block(3);
            m_queue.dequeue(block);

            ASSERT_EQUAL(before - block.size(), m_queue.size());
            }

          void dequeueing_a_block_returns_the_last_block_size_elements_enqueued()
            {
            std::vector<int> block(3);
            m_queue.dequeue(block);

            ASSERT(equal(block.crbegin(), block.crend(), internal::kInitialData.crbegin()));
            }

          void dequeueing_an_element_on_an_empty_queue_blocks()
            {
            dabi::queue<int> empty{};
            int target{};

            auto op = std::async(std::launch::async, [&]{ empty.dequeue(target); });
            auto status = op.wait_for(internal::kTimeoutTime);

            ASSERT_EQUAL(std::future_status::timeout, status);

            empty.enqueue(42);
            status = op.wait_for(internal::kTimeoutTime);

            ASSERT_EQUAL(std::future_status::ready, status);
            }

          void dequeueing_a_block_on_an_empty_queue_blocks()
            {
            dabi::queue<int> empty{};
            std::vector<int> target(3);

            auto op = std::async(std::launch::async, [&]{ empty.dequeue(target); });
            auto status = op.wait_for(internal::kTimeoutTime);

            ASSERT_EQUAL(std::future_status::timeout, status);

            empty.enqueue(internal::kInitialData);
            status = op.wait_for(internal::kTimeoutTime);

            ASSERT_EQUAL(std::future_status::ready, status);
            }

          void dequeueing_an_empty_block_on_an_empty_queue_does_not_block()
            {
            dabi::queue<int> empty{};
            std::vector<int> block{};

            auto op = std::async(std::launch::async, [&]{ empty.dequeue(block); });
            auto status = op.wait_for(internal::kTimeoutTime);

            ASSERT_EQUAL(std::future_status::ready, status);
            }

          void trying_to_dequeue_an_element_on_an_empty_queue_returns_false()
            {
            dabi::queue<int> empty{};
            int target{};

            ASSERT(!empty.try_dequeue(target));
            }

          void trying_to_dequeue_an_element_on_an_empty_queue_leaves_target_intact()
            {
            dabi::queue<int> empty{};
            int target{42};
            auto const before = target;

            empty.try_dequeue(target);
            ASSERT_EQUAL(before, target);
            }

          void trying_to_dequeue_a_block_on_an_empty_queue_returns_false()
            {
            dabi::queue<int> empty{};
            std::vector<int> target(1);

            ASSERT(!empty.try_dequeue(target));
            }

          void trying_to_dequeue_a_block_on_an_empty_queue_leaves_target_intact()
            {
            dabi::queue<int> empty{};
            std::vector<int> target(1);
            auto const before = target;

            empty.try_dequeue(target);
            ASSERT_EQUAL(before, target);
            }

          void trying_to_dequeue_a_block_on_a_queue_with_too_few_elements_returns_false()
            {
            std::vector<int> target(internal::kInitialData.size() + 1);

            ASSERT(!m_queue.try_dequeue(target));
            }

          void trying_to_dequeue_a_block_on_a_queue_with_too_few_elements_leaves_target_intact()
            {
            std::vector<int> target(internal::kInitialData.size() + 1);
            iota(target.begin(), target.end(), 0);
            auto const before = target;

            m_queue.try_dequeue(target);
            ASSERT_EQUAL(before, target);
            }

          private:
            dab::internal::queue<int, 2, 1> m_queue{};

          };

        }

      }

    }

  }

#endif
