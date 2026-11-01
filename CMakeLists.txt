cmake_minimum_required(VERSION 3.20)
project(nyaan_unit_tests LANGUAGES CXX)

include(CTest)
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
