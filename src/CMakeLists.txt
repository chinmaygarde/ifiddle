# Library
add_library(ifiddle
  project.h
  project.cc
)

target_link_libraries(ifiddle
  PUBLIC
    jfml
)

# Configure Fixtures Location
get_filename_component(TEST_ASSETS_LOCATION ../assets ABSOLUTE)
configure_file(fixtures_location.h.in fixtures_location.h @ONLY)

# Unittests
add_executable(ifiddle_tests
  unittests.cc
)
target_link_libraries(ifiddle_tests
  ifiddle
  gtest_main
)
target_include_directories(ifiddle_tests
  PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
)
gtest_discover_tests(ifiddle_tests)

# Benchmarks
add_executable(ifiddle_benchmarks
  benchmarks.cc
)
target_link_libraries(ifiddle_benchmarks
  ifiddle
  benchmark::benchmark
)
target_include_directories(ifiddle_benchmarks
  PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
)
