#include "fixtures_location.h"
#include "flutter/fml/mapping.h"
#include "gtest/gtest.h"
#include "impeller.hpp"
#include "render_engine.h"
#include "wasmtime.hh"

namespace fiddle::testing {

TEST(EmptyTest, CanCreateWasmEngine) {
  auto wasm_blob =
      fml::FileMapping::CreateReadOnly(TEST_BUILD_LOCATION "/example.wasm");
  ASSERT_TRUE(wasm_blob);
  wasmtime::Engine engine;
  wasmtime::Span<uint8_t> wasm_span(
      const_cast<uint8_t*>(wasm_blob->GetMapping()), wasm_blob->GetSize());
  auto module = wasmtime::Module::compile(engine, wasm_span);
  ASSERT_TRUE(!!module);
  wasmtime::Store store(engine);

  wasmtime::Store::Context context(store);
  wasmtime::WasiConfig wasi_config;
  wasi_config.inherit_stderr();
  wasi_config.inherit_stdout();
  wasi_config.inherit_stderr();
  auto wasi_config_result = context.set_wasi(std::move(wasi_config));
  ASSERT_TRUE(!!wasi_config_result);
  std::vector<wasmtime::Extern> imports;
  auto instance = wasmtime::Instance::create(context, module.ok(), imports);
  if (!instance) {
    FML_LOG(IMPORTANT) << instance.err().message();
  }
  ASSERT_TRUE(!!instance);
}

}  // namespace fiddle::testing
