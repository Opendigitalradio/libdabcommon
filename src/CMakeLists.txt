set(LIB_SOURCES types/transmission_mode.cpp)
add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})

if( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fPIC")
  endif()

