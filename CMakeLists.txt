cmake_minimum_required(VERSION 3.22)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/third_party/cmake_toolbox")
include(CMakeToolboxInitialize)

CMakeToolboxInitialize()

SetCAndCXXStandard(11 20)

EnableCCache()

set(IMPELLER_SDK_SHA b7c3af43f90ac9aaf66dbd10b922c25addd9c3db)

include(FetchContent)
FetchContent_Declare(
  impeller_sdk
  URL https://storage.googleapis.com/flutter_infra_release/flutter/${IMPELLER_SDK_SHA}/darwin-arm64/impeller_sdk.zip
)
FetchContent_MakeAvailable(impeller_sdk)

execute_process(COMMAND install_name_tool -id "@rpath/libimpeller.dylib" libimpeller.dylib
                WORKING_DIRECTORY ${impeller_sdk_SOURCE_DIR}/lib)

FetchContent_Declare(wasmtime_sdk
  URL https://github.com/bytecodealliance/wasmtime/releases/download/v26.0.0/wasmtime-v26.0.0-aarch64-macos-c-api.tar.xz
)
FetchContent_MakeAvailable(wasmtime_sdk)

project(ifiddle)

# set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

enable_testing()
include(GoogleTest)
include(CTest)

# Google Test
add_subdirectory(third_party/googletest EXCLUDE_FROM_ALL)

# Google Benchmark
set(GOOGLETEST_PATH "third_party/googletest")
set(BENCHMARK_ENABLE_TESTING FALSE)
add_subdirectory(third_party/googlebenchmark EXCLUDE_FROM_ALL)

add_subdirectory(third_party/jfml EXCLUDE_FROM_ALL)

set(CIVETWEB_ENABLE_CXX TRUE)
set(CIVETWEB_BUILD_TESTING FALSE)
add_subdirectory(third_party/civet EXCLUDE_FROM_ALL)

# Project
add_subdirectory(src)
