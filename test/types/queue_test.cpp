#include "queue_suites/enqueueing_suite.h"
#include "queue_suites/dequeueing_suite.h"

#include <cute/cute_runner.h>
#include <cute/cute_suite.h>
#include <cute/xml_listener.h>
#include <cute/ide_listener.h>
#include <cute/extensions/descriptive_test_class.h>

#include <vector>

int main(int argc, char * * argv)
  {
  auto testSuite = cute::suite{};

  auto xmlFile = cute::xml_file_opener{argc, argv};
  auto listener = cute::xml_listener<cute::ide_listener<>>{xmlFile.out};

  auto success = true;
  auto runner = cute::makeRunner(listener, argc, argv);

  using namespace dab::test::type::queue;

  success &= CUTE_DESCRIPTIVE_RUN(enqueueing_tests, runner);
  success &= CUTE_DESCRIPTIVE_RUN(dequeueing_tests, runner);

  return !success;
  }
