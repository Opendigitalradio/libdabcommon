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

#ifndef DABCOMMON_TEST_CONSTANTS_TRANSMISSION_MODE__MODE_2_TESTS
#define DABCOMMON_TEST_CONSTANTS_TRANSMISSION_MODE__MODE_2_TESTS

#include <dab/constants/transmission_modes.h>

#include <cute/cute.h>
#include <cute/cute_suite.h>
#include <cutex/descriptive_suite.h>

namespace dab
  {

  namespace test
    {

    namespace constants
      {

      namespace transmission_mode
        {

        CUTE_DESCRIPTIVE_STRUCT(mode_2_tests)
          {
          static cute::suite suite()
            {
            auto suite = cute::suite{};

#define LOCAL_TEST(Test) CUTE_SMEMFUN(mode_2_tests, Test)
            suite += LOCAL_TEST(carriers_equals_384);
            suite += LOCAL_TEST(frame_symbols_equals_75);
            suite += LOCAL_TEST(fic_symbols_equals_3);
            suite += LOCAL_TEST(msc_symbols_equals_72);
            suite += LOCAL_TEST(frame_fibs_equals_3);
            suite += LOCAL_TEST(frame_cifs_equals_1);
            suite += LOCAL_TEST(fib_codeword_bits_equals_768);
#undef LOCAL_TEST

            return suite;
            }

          void carriers_equals_384()
            {
            ASSERT_EQUAL(384, m_mode.carriers);
            }

          void frame_symbols_equals_75()
            {
            ASSERT_EQUAL(75, m_mode.frame_symbols);
            }

          void fic_symbols_equals_3()
            {
            ASSERT_EQUAL(3, m_mode.fic_symbols);
            }

          void msc_symbols_equals_72()
            {
            ASSERT_EQUAL(72, m_mode.msc_symbols);
            }

          void frame_fibs_equals_3()
            {
            ASSERT_EQUAL(3, m_mode.frame_fibs);
            }

          void frame_cifs_equals_1()
            {
            ASSERT_EQUAL(1, m_mode.frame_cifs);
            }

          void fib_codeword_bits_equals_768()
            {
            ASSERT_EQUAL(768, m_mode.fib_codeword_bits);
            }

          private:
            dab::internal::types::transmission_mode const m_mode = dab::kTransmissionMode2;
          };

        }

      }

    }

  }

#endif
