
# add_custom_command(
#       OUTPUT ${CMAKE_BINARY_DIR}/lcov/index.html
#       COMMAND ${LCOV} -q -z -d .
#       COMMAND ${LCOV} -q --no-external -c -b "${CMAKE_SOURCE_DIR}" -d . -o before.lcov -i
#       COMMAND ${CTEST} --force-new-ctest-process
#       COMMAND ${LCOV} -q --no-external -c -b "${CMAKE_SOURCE_DIR}" -d . -o after.lcov
#       COMMAND ${LCOV} -q -a before.lcov -a after.lcov --output-file final.lcov
#       COMMAND ${LCOV} -q -r final.lcov "'${CMAKE_SOURCE_DIR}/test/*'" -o final.lcov
#       COMMAND ${GENHTML} final.lcov -o lcov --demangle-cpp --sort -p "${CMAKE_BINARY_DIR}" -t benchmark
#       DEPENDS filter_test benchmark_test options_test basic_test fixture_test cxx03_test complexity_test
#       WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#       COMMENT "Running LCOV"
#     )

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/example.wasm
  COMMAND ${wasmclang_SOURCE_DIR}/bin/clang --target=wasm32 --no-standard-libraries -Wl,--export-all -Wl,--no-entry -o ${CMAKE_CURRENT_BINARY_DIR}/example.wasm ${CMAKE_CURRENT_SOURCE_DIR}/example.c
  DEPENDS example.c
  COMMENT "Compiling Example C"
)
add_custom_target(wasm_example DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/example.wasm)


# Impeller
add_library(impeller SHARED IMPORTED)
set_target_properties(impeller
  PROPERTIES
  IMPORTED_LOCATION ${impeller_sdk_SOURCE_DIR}/lib/libimpeller.dylib
)
target_include_directories(impeller INTERFACE ${impeller_sdk_SOURCE_DIR}/include)
list(APPEND CMAKE_INSTALL_RPATH ${impeller_sdk_SOURCE_DIR}/lib)
list(APPEND CMAKE_BUILD_RPATH ${impeller_sdk_SOURCE_DIR}/lib)

# Wasmtime
add_library(wasmtime_c SHARED IMPORTED)
set_target_properties(wasmtime_c
  PROPERTIES
  IMPORTED_LOCATION ${wasmtime_sdk_SOURCE_DIR}/lib/libwasmtime.dylib
)
target_include_directories(wasmtime_c INTERFACE ${wasmtime_sdk_SOURCE_DIR}/include)
list(APPEND CMAKE_INSTALL_RPATH ${wasmtime_sdk_SOURCE_DIR}/lib)
list(APPEND CMAKE_BUILD_RPATH ${wasmtime_sdk_SOURCE_DIR}/lib)

# iFiddle
add_library(ifiddle
  compilation_engine.cc
  compilation_engine.h
  execution_engine.cc
  execution_engine.h
  project.cc
  project.h
  render_engine.cc
  render_engine.h
  server_engine.cc
  server_engine.h
)

target_link_libraries(ifiddle
  PUBLIC
    jfml
    impeller
    wasmtime_c
)

target_include_directories(ifiddle
  PUBLIC
    ../third_party/wasmtime-cpp/include
)

target_compile_definitions(ifiddle PUBLIC -DIMPELLER_HPP_NAMESPACE=fiddle)

# Configure Fixtures Location
get_filename_component(TEST_ASSETS_LOCATION ../assets ABSOLUTE)
configure_file(fixtures_location.h.in fixtures_location.h @ONLY)

# Unittests
add_executable(ifiddle_tests
  unittests.cc
)

add_dependencies(ifiddle_tests wasm_example)

target_link_libraries(ifiddle_tests
  ifiddle
  gtest_main
)
target_include_directories(ifiddle_tests
  PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR} # For Fixtures
)

gtest_discover_tests(ifiddle_tests)
