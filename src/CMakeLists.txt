add_library(impeller SHARED IMPORTED)
set_target_properties(impeller
  PROPERTIES
  IMPORTED_LOCATION ${impeller_sdk_SOURCE_DIR}/lib/libimpeller.dylib
)
target_include_directories(impeller INTERFACE ${impeller_sdk_SOURCE_DIR}/include)
list(APPEND CMAKE_INSTALL_RPATH ${impeller_sdk_SOURCE_DIR}/lib)
list(APPEND CMAKE_BUILD_RPATH ${impeller_sdk_SOURCE_DIR}/lib)

add_library(wasmtime_c SHARED IMPORTED)
set_target_properties(wasmtime_c
  PROPERTIES
  IMPORTED_LOCATION ${wasmtime_sdk_SOURCE_DIR}/lib/libwasmtime.dylib
)
target_include_directories(wasmtime_c INTERFACE ${wasmtime_sdk_SOURCE_DIR}/include)
list(APPEND CMAKE_INSTALL_RPATH ${wasmtime_sdk_SOURCE_DIR}/lib)
list(APPEND CMAKE_BUILD_RPATH ${wasmtime_sdk_SOURCE_DIR}/lib)


# Library
add_library(ifiddle
  project.h
  project.cc
)

target_link_libraries(ifiddle
  PUBLIC
    jfml
    impeller
    wasmtime_c
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
