cmake_minimum_required(VERSION 3.1)
project("DABCommon"
  LANGUAGES CXX
  VERSION 1.0.1)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")
set(CXX_VERSION "c++11")

include("CompilerSetup")
include("ConanPackages")

find_package(Threads REQUIRED)

string(TOUPPER ${PROJECT_NAME} ${PROJECT_NAME}_UPPER)
string(TOLOWER ${PROJECT_NAME} ${PROJECT_NAME}_LOWER)

option(${${PROJECT_NAME}_UPPER}_ENABLE_TESTS
  "Build and run the ${PROJECT_NAME} unit tests."
  OFF
)

add_subdirectory("include")

if(${${PROJECT_NAME}_UPPER}_ENABLE_TESTS AND NOT BUILD_DOCUMENTATION_ONLY)
  include("CUTE")
  add_subdirectory(test)
endif()
