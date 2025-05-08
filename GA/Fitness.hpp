#ifndef FITNESS_HPP
#define FITNESS_HPP

#include <vector>

#include "../IAgent.hpp"
#include "../Utils/Utils.hpp"

/// @brief Base interface for fitness classes
/// @tparam Population type of population. Fitness will be calculated on this
/// population's individuals
template<typename Population>
class IFitness
{
public:
  virtual ~IFitness() {}

  /// @brief Calcualte fitness for each individual of `population`.
  virtual void EvaluatePopulation(Population& population) = 0;
};

/// @brief Fitness is calculated based on individual's distance from its
/// destination
/// @tparam Population type of population. Fitness will be calculated on this
/// population's individuals
template<typename Population>
class DestinationDistanceFitness : public IFitness<Population>
{
public:
  ~DestinationDistanceFitness() {}

  /// @brief Calcualte fitness for each individual of `population`.
  virtual void EvaluatePopulation(Population& population)
  {
    for (auto& agent : population) {
      const auto& agentsPath = agent.GetPath();
      const auto agentsEndPosition =
        !agentsPath.empty() ? agentsPath.back() : agent.GetPosition();
      const auto agentDestination = agent.GetDestination();
      _fitnesses.emplace_back(agentDestination.Distance(agentsEndPosition));
    }
  }

  /// @brief Return resulting fitnesses
  const std::vector<double>& GetFitnesses() const { return _fitnesses; }

private:
  std::vector<double> _fitnesses;
};

#endif // FITNESS_HPP