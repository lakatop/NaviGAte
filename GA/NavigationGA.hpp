#include "AgentGA.hpp"
#include "Population.hpp"

/// @brief Represents one concrete configuration of GA.
/// @tparam Population type of population.
/// @tparam ...Operators operators which this GA uses.
template<typename Population, typename... Operators>
class NavigateGA
{
public:
  NavigateGA() {}

  /// @brief Applies `operators` to `population`
  void StartGA(Population& population, Operators... operators)
  {
    for (int i = 0; i < iterations; i++) {
      ((operators.ModifyPopulation(population)), ...);
    }
  }

  /// @brief Evaluates population - ranks each individual
  /// @tparam Evaluator Class for evaluating
  template<typename Evaluator>
  void EvaluatePopulation(Evaluator& evaluator, Population& population)
  {
    evaluator.Evaluate(population);
  }

private:
  /// @brief Number of iterations of GA
  int iterations = 2;
};