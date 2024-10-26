#include "fixtures_location.h"
#include "gtest/gtest.h"
#include "impeller.h"

TEST(EmptyTest, EmptyTest) {
  ASSERT_EQ(ImpellerGetVersion(), IMPELLER_VERSION);
}
