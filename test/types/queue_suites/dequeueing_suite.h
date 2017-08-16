/*
 * Copyright (C) 2017 Opendigitalradio (http://www.opendigitalradio.org/)
 * Copyright (C) 2017 Felix Morgner <felix.morgner@hsr.ch>
 * Copyright (C) 2017 Tobias Stauber <tobias.stauber@hsr.ch>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DABCOMMON_TEST_TYPES_QUEUE__DEQUEUEING_SUITE
#define DABCOMMON_TEST_TYPES_QUEUE__DEQUEUEING_SUITE

#include <dab/types/queue.h>

#include <cute/cute.h>
#include <cute/cute_suite.h>
#include <cutex/descriptive_suite.h>

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
            suite += LOCAL_TEST(dequeueing_an_element_returns_the_first_enqueued);
            suite += LOCAL_TEST(size_is_block_size_less_after_dequeueing_a_block);
            suite += LOCAL_TEST(dequeueing_a_block_returns_the_first_block_size_elements_enqueued);
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

          void dequeueing_an_element_returns_the_first_enqueued()
            {
            int target{};
            m_queue.dequeue(target);

            ASSERT_EQUAL(internal::kInitialData.front(), target);
            }

          void size_is_block_size_less_after_dequeueing_a_block()
            {
            auto const before = m_queue.size();

            std::vector<int> block(3);
            m_queue.dequeue(block);

            ASSERT_EQUAL(before - block.size(), m_queue.size());
            }

          void dequeueing_a_block_returns_the_first_block_size_elements_enqueued()
            {
            std::vector<int> block(3);
            m_queue.dequeue(block);

            ASSERT(equal(block.begin(), block.end(), internal::kInitialData.begin()));
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
