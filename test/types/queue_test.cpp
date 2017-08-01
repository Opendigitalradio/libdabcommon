#include "queue_suites/enqueueing_suite.h"
#include "queue_suites/dequeueing_suite.h"

#include <cute/cute_runner.h>
#include <cute/cute_suite.h>
#include <cute/xml_listener.h>
#include <cute/ide_listener.h>
#include <cutex/descriptive_suite.h>

#include <vector>

int main(int argc, char * * argv)
  {
  auto xmlFile = cute::xml_file_opener{argc, argv};
  auto listener = cute::xml_listener<cute::ide_listener<>>{xmlFile.out};

  auto success = true;
  auto runner = cute::makeRunner(listener, argc, argv);

  using namespace dab::test::type::queue;

  success &= cute::extensions::runSelfDescriptive<enqueueing_tests>(runner);
  success &= cute::extensions::runSelfDescriptive<dequeueing_tests>(runner);

  return !success;
  }
