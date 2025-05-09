#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

/*
  Utility tests
*/
#include "../Utils/Utils.hpp"

TEST_SUITE_BEGIN("Utility");

TEST_CASE("NextRandom")
{
  for (int i = 0; i < 100; ++i) {
    const double random = Utils::NextRandom();
    const bool inBounds = random >= 0 && random < 1;
    CHECK(inBounds == true);
  }
}

TEST_SUITE_END();

/*
  Agent tests
*/
#include "../GA/AgentGA.hpp"

TEST_SUITE_BEGIN("AgentGA");

TEST_CASE("Initialisation sizes")
{
  AgentGA agent;
  const int pathSize = 5;
  agent.Initialise(pathSize);
  CHECK_MESSAGE(agent.GetAccelerations().size() == pathSize,
                "Accelerations have size of ",
                pathSize);

  CHECK_MESSAGE(agent.GetSteerings().size() == pathSize,
                "Steerings have size of ",
                pathSize);

  CHECK_MESSAGE(
    agent.GetPath().size() == pathSize, "Path have size of ", pathSize);
}

TEST_CASE("Initialisation values")
{
  AgentGA agent;
  const int pathSize = 10;
  const auto maxAcc = agent.GetMaxAcceleration();
  const auto maxDec = agent.GetMaxDeceleration();
  const auto maxSteerAngle = agent.GetMaxSteering();

  agent.Initialise(pathSize);

  // Acceleration values
  const auto& accelerations = agent.GetAccelerations();
  for (int i = 1; i < accelerations.size(); ++i) {
    const auto inBounds =
      accelerations[i] >= -maxDec && accelerations[i] <= maxAcc;
    CHECK(inBounds == true);
  }

  // Steering values
  const auto& steerings = agent.GetSteerings();
  for (int i = 0; i < steerings.size(); ++i) {
    const auto inBounds =
      steerings[i] >= -maxSteerAngle && steerings[i] <= maxSteerAngle;
    CHECK(inBounds == true);
  }
}

TEST_SUITE_END();