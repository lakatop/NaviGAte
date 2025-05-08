#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <vector>

/// @brief Class representing population used in GA
/// @tparam AgentGA type on individuals
template<typename AgentGA>
class Population
{
public:
  /*
  Iterators for population
  */
  auto begin() { return _population.begin(); }
  const auto begin() const { return _population.cbegin(); }
  auto end() { return _population.end(); }
  const auto end() const { return _population.cend(); }

  /// @brief Initialise population of `size` individuals
  /// @param size
  void Initialise(int size);

  /// @brief Debug print for population
  void Print();

private:
  /// @brief Vector of individuals
  std::vector<AgentGA> _population;
  /// @brief Resulting fitness for each individual
  std::vector<double> _resultFitnesses;
};

template<typename AgentGA>
void
Population<AgentGA>::Initialise(int size)
{
  _population.reserve(size);

  for (int i = 0; i < size; ++i) {
    auto& agent = _population.emplace_back();
    agent.Initialise(10);
  }
}

template<typename AgentGA>
void
Population<AgentGA>::Print()
{
  for (auto& agent : _population) {
    agent.Print();
  }
}

#endif // POPULATION_HPP