#ifndef DABCOMMON_TEST_CONSTANTS_TRANSMISSION_MODE__MODE_4_TESTS
#define DABCOMMON_TEST_CONSTANTS_TRANSMISSION_MODE__MODE_4_TESTS

#include <constants/transmission_modes.h>

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

        CUTE_DESCRIPTIVE_STRUCT(mode_4_tests)
          {
          static cute::suite suite()
            {
            auto suite = cute::suite{};

#define LOCAL_TEST(Test) CUTE_SMEMFUN(mode_4_tests, Test)
            suite += LOCAL_TEST(carriers_equals_768);
            suite += LOCAL_TEST(frame_symbols_equals_75);
            suite += LOCAL_TEST(fic_symbols_equals_3);
            suite += LOCAL_TEST(msc_symbols_equals_72);
            suite += LOCAL_TEST(frame_fibs_equals_6);
            suite += LOCAL_TEST(frame_cifs_equals_2);
            suite += LOCAL_TEST(fib_codeword_bits_equals_768);
#undef LOCAL_TEST

            return suite;
            }

          void carriers_equals_768()
            {
            ASSERT_EQUAL(768, m_mode.carriers);
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

          void frame_fibs_equals_6()
            {
            ASSERT_EQUAL(6, m_mode.frame_fibs);
            }

          void frame_cifs_equals_2()
            {
            ASSERT_EQUAL(2, m_mode.frame_cifs);
            }

          void fib_codeword_bits_equals_768()
            {
            ASSERT_EQUAL(768, m_mode.fib_codeword_bits);
            }

          private:
            dab::internal::types::transmission_mode const m_mode = dab::transmission_modes::kTransmissionMode4;
          };

        }

      }

    }

  }

#endif
