cmake_minimum_required(VERSION 3.20)
project(nyaan_unit_tests LANGUAGES CXX)

option(NYAAN_ENABLE_SANITIZERS "Run unit tests with AddressSanitizer and UBSan" OFF)

include(CTest)
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
