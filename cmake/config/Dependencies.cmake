include("ExternalDependency")

set(${${PROJECT_NAME}_UPPER}_DEPS)

if(${${PROJECT_NAME}_UPPER}_DEPS_VIA STREQUAL "conan")
  if(${${PROJECT_NAME}_UPPER}_ENABLE_TESTS)
    include("ConanPackages")
    install_conan_packages(SYSTEM_HEADERS
      PKGOPTS ${CONAN_OPTIONS}
      )
    list(APPEND ${${PROJECT_NAME}_UPPER}_DEPS
      CONAN_PKG::CUTEX
      )
  endif()
elseif(${${PROJECT_NAME}_UPPER}_DEPS_VIA STREQUAL "git")
  set(${${PROJECT_NAME}_UPPER}_DEPENDENCIES_DIR "${CMAKE_SOURCE_DIR}/external"
    CACHE PATH
    "External depencies source path"
    FORCE
    )

  if(${${PROJECT_NAME}_UPPER}_ENABLE_TESTS)
    set(CUTEX_ENABLE_TESTS OFF)
    external_dependency(CMAKE
      NAME "CUTEX"
      REPO "https://github.com/fmorgner/CUTEX"
      LIBNAME "CUTEX"
      )
  endif()
else()
  message(FATAL_ERROR "Unknown dependency resolution mechanism '${${${PROJECT_NAME}_UPPER}_DEPS_VIA}'")
endif()
