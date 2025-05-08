#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <vector>

template<typename AgentGA>
class Population
{
public:
  auto begin() { return _population.begin(); }
  const auto begin() const { return _population.cbegin(); }
  auto end() { return _population.end(); }
  const auto end() const { return _population.cend(); }

  void Initialise(int size);
  void Print();

private:
  std::vector<AgentGA> _population;
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