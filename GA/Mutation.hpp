#ifndef MUTATION_HPP
#define MUTATION_HPP

#include "../IAgent.hpp"
#include "../Utils/Utils.hpp"

/// @brief Base interface for mutation classes
/// @tparam Population type of population. Mutation will be applied on this
/// population's individuals
template<typename Population>
class IMutation
{
public:
  virtual ~IMutation() {}

  /// @brief Returns probability by which this mutation happens on individual
  virtual float GetMutationProbability() = 0;

  /// @brief Apply mutation on `population`
  virtual void ModifyPopulation(Population& population) = 0;
};

/// @brief Mutation is randomly changing individuals speed
/// @tparam Population type of population
template<typename Population>
class RandomVelocityMutation : public IMutation<Population>
{
public:
  ~RandomVelocityMutation() {};

  /// @brief Returns probability by which this mutation happens on individual
  float GetMutationProbability() override { return _mutationProbability; }

  /// @brief Apply mutation on `population`
  void ModifyPopulation(Population& population) override
  {
    for (auto& agent : population) {
      auto maxAcc = agent.GetMaxAcceleration();
      auto maxDecc = agent.GetMaxDeceleration();
      auto& accelerations = agent.GetAccelerations();
      for (int i = 0; i < accelerations.size(); ++i) {
        if (Utils::NextRandom() > _mutationProbability)
          continue;

        double newAcceleration =
          (maxAcc + maxDecc) * Utils::NextRandom() - maxDecc;
        accelerations[i] = newAcceleration;
      }
    }
  }

private:
  float _mutationProbability;
};

#endif // MUTATION_HPP