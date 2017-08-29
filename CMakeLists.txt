cmake_minimum_required(VERSION 3.1.2)
project("DABCommon"
  LANGUAGES CXX
  VERSION 1.0.1)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/config/Base.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/config/Options.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/config/Dependencies.cmake")

find_package(Threads REQUIRED)

add_subdirectory("include")

if(${${PROJECT_NAME}_UPPER}_ENABLE_TESTS)
  include("CUTE")
  include_directories(SYSTEM
    ${CUTEX_INCLUDE_DIRECTORIES}
    )
  add_subdirectory("test")
endif()
