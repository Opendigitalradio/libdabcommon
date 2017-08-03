cmake_minimum_required(VERSION 3.1)
project("DABCommon"
  LANGUAGES CXX
  VERSION 1.0.1)

string(TOUPPER ${PROJECT_NAME} ${PROJECT_NAME}_UPPER)
string(TOLOWER ${PROJECT_NAME} ${PROJECT_NAME}_LOWER)

option(${${PROJECT_NAME}_UPPER}_ENABLE_TESTS
  "Build and run the ${PROJECT_NAME} unit tests."
  OFF
  )

option(${${PROJECT_NAME}_UPPER}_SKIP_CONAN
  "Skip installing the dependencies for ${PROJECT_NAME} through conan."
  OFF
  )

if(${${${PROJECT_NAME}_UPPER}_ENABLE_TESTS})
  set(CONAN_OPTIONS libdabcommon:test=True)
endif()

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")
set(CXX_VERSION "c++11")

include("CompilerSetup")

if(NOT ${${PROJECT_NAME}_UPPER}_SKIP_CONAN)
  include("ConanPackages")
  install_conan_packages(SYSTEM_HEADERS
    PKGOPTS ${CONAN_OPTIONS}
    )
endif()

find_package(Threads REQUIRED)

add_subdirectory("include")

if(${${PROJECT_NAME}_UPPER}_ENABLE_TESTS AND NOT BUILD_DOCUMENTATION_ONLY)
  include("CUTE")
  add_subdirectory("test")
endif()

install(EXPORT ${PROJECT_NAME}
  DESTINATION "share/${${PROJECT_NAME}_LOWER}/cmake"
  )

export(EXPORT ${PROJECT_NAME})
