include("ExternalDependency")

set(${${PROJECT_NAME}_UPPER}_DEPS)

if(EXTERNAL_DEPS_VIA STREQUAL "conan")
  if(${${PROJECT_NAME}_UPPER}_ENABLE_TESTS)
    include("ConanPackages")
    if(${${${PROJECT_NAME}_UPPER}_ENABLE_TESTS})
      list(APPEND CONAN_OPTIONS ${CONAN_OPTIONS} libdabcommon:test=True)
    endif()
    install_conan_packages(SYSTEM_HEADERS
      PKGOPTS ${CONAN_OPTIONS}
      )
    list(APPEND ${${PROJECT_NAME}_UPPER}_DEPS
      CONAN_PKG::CUTEX
      )
  endif()
elseif(EXTERNAL_DEPS_VIA STREQUAL "git")
  if(${${PROJECT_NAME}_UPPER}_ENABLE_TESTS)
    set(CUTEX_ENABLE_TESTS OFF)
    external_dependency(CMAKE
      NAME "CUTEX"
      REPO "https://github.com/fmorgner/CUTEX"
      )
  endif()
else()
  message(FATAL_ERROR "Unknown dependency resolution mechanism 'EXTERNAL_DEPS_VIA}'")
endif()
