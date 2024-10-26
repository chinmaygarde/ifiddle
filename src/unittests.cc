#include "fixtures_location.h"
#include "gtest/gtest.h"
#include "impeller.hpp"
#include "render_engine.h"
#include "wasmtime.hh"

namespace fiddle::testing {

TEST(EmptyTest, CanCreateWasmEngine) {
  wasmtime::Engine engine;
}

}  // namespace fiddle::testing
