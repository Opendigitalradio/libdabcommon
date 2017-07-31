#ifndef DABCOMMON_TEST_CONSTANTS_TRANSMISSION_MODE__MODE_3_TESTS
#define DABCOMMON_TEST_CONSTANTS_TRANSMISSION_MODE__MODE_3_TESTS

#include <constants/transmission_modes.h>

#include <cute/cute.h>
#include <cute/cute_suite.h>
#include <cute/extensions/descriptive_suite.h>

namespace dab
  {

  namespace test
    {

    namespace constants
      {

      namespace transmission_mode
        {

        CUTE_DESCRIPTIVE_STRUCT(mode_3_tests)
          {
          static cute::suite suite()
            {
            auto suite = cute::suite{};

#define LOCAL_TEST(Test) CUTE_SMEMFUN(mode_3_tests, Test)
            suite += LOCAL_TEST(carriers_equals_192);
            suite += LOCAL_TEST(frame_symbols_equals_152);
            suite += LOCAL_TEST(fic_symbols_equals_8);
            suite += LOCAL_TEST(msc_symbols_equals_144);
            suite += LOCAL_TEST(frame_fibs_equals_4);
            suite += LOCAL_TEST(frame_cifs_equals_1);
            suite += LOCAL_TEST(fib_codeword_bits_equals_1024);
#undef LOCAL_TEST

            return suite;
            }

          void carriers_equals_192()
            {
            ASSERT_EQUAL(192, m_mode.carriers);
            }

          void frame_symbols_equals_152()
            {
            ASSERT_EQUAL(152, m_mode.frame_symbols);
            }

          void fic_symbols_equals_8()
            {
            ASSERT_EQUAL(8, m_mode.fic_symbols);
            }

          void msc_symbols_equals_144()
            {
            ASSERT_EQUAL(144, m_mode.msc_symbols);
            }

          void frame_fibs_equals_4()
            {
            ASSERT_EQUAL(4, m_mode.frame_fibs);
            }

          void frame_cifs_equals_1()
            {
            ASSERT_EQUAL(1, m_mode.frame_cifs);
            }

          void fib_codeword_bits_equals_1024()
            {
            ASSERT_EQUAL(1024, m_mode.fib_codeword_bits);
            }

          private:
            dab::internal::types::transmission_mode const m_mode = dab::transmission_modes::kTransmissionMode3;
          };

        }

      }

    }

  }

#endif
