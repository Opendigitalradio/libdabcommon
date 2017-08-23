set(${${PROJECT_NAME}_UPPER}_DEPS_VIA "git"
  CACHE STRING
  "The dependency resolution mechanism to use for ${PROJECT_NAME}"
  )

set_property(CACHE ${${PROJECT_NAME}_UPPER}_DEPS_VIA
  PROPERTY
  STRINGS
  "git"
  "conan"
  )

if(DABDATA_DEPS_VIA)
  set(${${PROJECT_NAME}_UPPER}_DEPS_VIA ${DABDATA_DEPS_VIA}
    CACHE STRING
    "The dependency resolution mechanism to use"
    FORCE
    )
endif()

option(${${PROJECT_NAME}_UPPER}_ENABLE_TESTS
  "Build and run the ${PROJECT_NAME} unit tests."
  OFF
  )

if(${${${PROJECT_NAME}_UPPER}_ENABLE_TESTS})
  if(${${${PROJECT_NAME}_UPPER}_DEPS_VIA} STREQUAL "conan")
    list(APPEND CONAN_OPTIONS ${CONAN_OPTIONS} libdabcommon:test=True)
  endif()
endif()
