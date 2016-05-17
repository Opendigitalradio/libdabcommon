#include "constants/transmission_modes.h"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/cute_suite.h>
#include <cute/xml_listener.h>
#include <cute/ide_listener.h>

void test_carriers_equals_1536()
  {
  ASSERT_EQUAL(1536, dab::transmission_modes::kTransmissionMode1.carriers);
  }

void test_frame_symbols_equals_75()
  {
  ASSERT_EQUAL(75, dab::transmission_modes::kTransmissionMode1.frame_symbols);
  }

void test_fic_symbols_equals_3()
  {
  ASSERT_EQUAL(3, dab::transmission_modes::kTransmissionMode1.fic_symbols);
  }

void test_msc_symbols_equals_72()
  {
  ASSERT_EQUAL(72, dab::transmission_modes::kTransmissionMode1.msc_symbols);
  }

void test_frame_fibs_equals_12()
  {
  ASSERT_EQUAL(12, dab::transmission_modes::kTransmissionMode1.frame_fibs);
  }

void test_frame_cifs_equals_4()
  {
  ASSERT_EQUAL(4, dab::transmission_modes::kTransmissionMode1.frame_cifs);
  }

void test_fib_codeword_bits_equals_768()
  {
  ASSERT_EQUAL(768, dab::transmission_modes::kTransmissionMode1.fib_codeword_bits);
  }

int main(int argc, char * * argv)
  {
  auto testSuite = cute::suite{};

  testSuite += cute::test{test_carriers_equals_1536, "Mode 1 should have 1536 carriers"};
  testSuite += cute::test{test_frame_symbols_equals_75, "Mode 1 should have 75 symbols per frame"};
  testSuite += cute::test{test_fic_symbols_equals_3, "Mode 1 should have 3 symbols for the FIC"};
  testSuite += cute::test{test_msc_symbols_equals_72, "Mode 1 should have 72 symbols for the MSC"};
  testSuite += cute::test{test_frame_fibs_equals_12, "Mode 1 should have 12 FIBs per frame"};
  testSuite += cute::test{test_frame_cifs_equals_4, "Mode 1 should have 4 CIFs per frame"};
  testSuite += cute::test{test_fib_codeword_bits_equals_768, "Mode 1 should have 768 bits per FIB codeword"};

  auto xmlFile = cute::xml_file_opener{argc, argv};
  auto listener = cute::xml_listener<cute::ide_listener<>>{xmlFile.out};

  return !cute::makeRunner(listener, argc, argv)(testSuite, "DAB transfer mode 1 descriptor suite");
  }

