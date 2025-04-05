#ifndef FITNESS_HPP
#define FITNESS_HPP

#include <vector>

#include "../IAgent.hpp"
#include "../Utils/Utils.hpp"

template<typename Population>
class IFitness
{
public:
  virtual ~IFitness() {}

  virtual void EvaluatePopulation(Population& population) = 0;
};

template<typename Population>
class DestinationDistanceFitness : public IFitness<Population>
{
public:
  ~DestinationDistanceFitness() {}

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

  const std::vector<double>& GetFitnesses() const { return _fitnesses; }

private:
  std::vector<double> _fitnesses;
};

#endif // FITNESS_HPP