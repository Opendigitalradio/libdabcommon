#include "transmission_mode_suites/mode_1_suite.h"
#include "transmission_mode_suites/mode_2_suite.h"
#include "transmission_mode_suites/mode_3_suite.h"
#include "transmission_mode_suites/mode_4_suite.h"

#include <cute/cute_runner.h>
#include <cute/cute_suite.h>
#include <cute/xml_listener.h>
#include <cute/ide_listener.h>
#include <cutex/descriptive_suite.h>

#include <vector>

int main(int argc, char * * argv)
  {
  auto testSuite = cute::suite{};

  auto xmlFile = cute::xml_file_opener{argc, argv};
  auto listener = cute::xml_listener<cute::ide_listener<>>{xmlFile.out};

  auto success = true;
  auto runner = cute::makeRunner(listener, argc, argv);

  using namespace dab::test::constants::transmission_mode;

  success &= cute::extensions::runSelfDescriptive<mode_1_tests>(runner);
  success &= cute::extensions::runSelfDescriptive<mode_2_tests>(runner);
  success &= cute::extensions::runSelfDescriptive<mode_3_tests>(runner);
  success &= cute::extensions::runSelfDescriptive<mode_4_tests>(runner);

  return !success;
  }
