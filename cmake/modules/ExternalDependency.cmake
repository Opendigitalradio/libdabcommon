include(CMakeParseArguments)

macro(EXTERNAL_DEPENDENCY)
  set(OPTS   CMAKE)
  set(SVARGS NAME LIBNAME REPO)
  set(MVARGS INCLUDE_DIRECTORIES DEPENDENCIES)

  cmake_parse_arguments(DEP
    "${OPTS}"
    "${SVARGS}"
    "${MVARGS}"
    ${ARGN}
    )

  if(NOT GIT_FOUND)
    find_package(Git REQUIRED)
  endif()

  file(MAKE_DIRECTORY ${${${PROJECT_NAME}_UPPER}_DEPENDENCIES_DIR})
  if(NOT EXISTS ${${${PROJECT_NAME}_UPPER}_DEPENDENCIES_DIR}/${DEP_NAME})
    message(STATUS "ExternalDependency: Cloning ${DEP_NAME}")
    execute_process(COMMAND ${GIT_EXECUTABLE}
      clone ${DEP_REPO} ${DEP_NAME}
      WORKING_DIRECTORY ${${${PROJECT_NAME}_UPPER}_DEPENDENCIES_DIR}
      OUTPUT_FILE "${CMAKE_BINARY_DIR}/${DEP_NAME}_git_stdout.log"
      ERROR_FILE "${CMAKE_BINARY_DIR}/${DEP_NAME}_git_stderr.log"
      )
  endif()

  if(DEP_CMAKE)
    add_subdirectory(${${${PROJECT_NAME}_UPPER}_DEPENDENCIES_DIR}/${DEP_NAME})
  else()
    add_library(${DEP_LIBNAME} INTERFACE)
    target_include_directories(${DEP_LIBNAME} SYSTEM INTERFACE
      $<BUILD_INTERFACE:${DEP_INCLUDE_DIRECTORIES}>
      )
    target_link_libraries(${DEP_LIBNAME} INTERFACE
      ${DEP_DEPENDENCIES}
      )
    install(TARGETS ${DEP_LIBNAME}
      EXPORT ${PROJECT_NAME}
      )
  endif()

  list(APPEND ${${PROJECT_NAME}_UPPER}_DEPS
    ${DEP_LIBNAME}
    )
endmacro()
