cmake_minimum_required(VERSION 3.22)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/third_party/cmake_toolbox")
include(CMakeToolboxInitialize)

CMakeToolboxInitialize()

SetCAndCXXStandard(11 17)

EnableCCache()

set(IMPELLER_SDK_SHA b7c3af43f90ac9aaf66dbd10b922c25addd9c3db)

cmake_policy(SET CMP0135 NEW)

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

FetchContent_Declare(wasmclang
  URL https://github.com/llvm/llvm-project/releases/download/llvmorg-18.1.8/clang+llvm-18.1.8-arm64-apple-macos11.tar.xz
)
FetchContent_MakeAvailable(wasmclang)

project(ifiddle)

enable_testing()
include(GoogleTest)
include(CTest)

add_subdirectory(third_party/googletest EXCLUDE_FROM_ALL)
add_subdirectory(third_party/jfml EXCLUDE_FROM_ALL)
set(CIVETWEB_ENABLE_CXX TRUE)
set(CIVETWEB_BUILD_TESTING FALSE)
add_subdirectory(third_party/civet EXCLUDE_FROM_ALL)

# Project
add_subdirectory(src)
