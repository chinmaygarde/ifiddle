#include "fixtures_location.h"
#include "gtest/gtest.h"
#include "impeller.hpp"
#include "render_engine.h"

namespace fiddle::testing {

TEST(EmptyTest, EmptyTest) {
  const auto& engine = RenderEngine::Get();
  Paint paint;
  ASSERT_EQ(ImpellerGetVersion(), IMPELLER_VERSION);
}

}  // namespace fiddle::testing
