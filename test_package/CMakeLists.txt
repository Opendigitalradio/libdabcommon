project(PackageTest CXX)
cmake_minimum_required(VERSION 2.8.12)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(package_test package_test.cpp)
target_link_libraries(package_test ${CONAN_LIBS})
