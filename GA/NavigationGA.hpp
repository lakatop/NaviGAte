#include "AgentGA.hpp"
#include "Population.hpp"

template<typename Population, typename... Operators>
class NavigateGA
{
public:
  NavigateGA() {}

  void StartGA(Population& population, Operators... operators)
  {
    for (int i = 0; i < iterations; i++) {
      ((operators.ModifyPopulation(population)), ...);
    }
  }

  template<typename Evaluator>
  void EvaluatePopulation(Evaluator& evaluator, Population& population)
  {
    evaluator.Evaluate(population);
  }

private:
  int iterations = 2;
};