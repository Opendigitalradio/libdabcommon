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

#ifndef DABCOMMON_TEST_TYPES_QUEUE__ENQUEUEING_SUITE
#define DABCOMMON_TEST_TYPES_QUEUE__ENQUEUEING_SUITE

#include <dab/types/queue.h>

#include <cute/cute.h>
#include <cute/cute_suite.h>
#include <cutex/descriptive_suite.h>

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

          private:
            dab::internal::queue<int, 2, 1> m_queue{};
          };

        }

      }

    }

  }

#endif
