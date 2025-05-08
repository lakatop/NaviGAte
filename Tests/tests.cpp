#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../Utils/Utils.hpp"

TEST_CASE("Test Utility - NextRandom")
{
  for (int i = 0; i < 100; ++i) {
    const double random = Utils::NextRandom();
    const bool inBounds = random >= 0 && random < 1;
    CHECK(inBounds == true);
  }
}