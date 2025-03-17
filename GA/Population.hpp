#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <vector>

template <typename Agent>
class Population
{
public:
    Agent *begin() { return _population.begin(); }
    const Agent *begin() const { return _population.cbegin(); }
    Agent *end() { return _population.end(); }
    const Agent *end() const { return _population.cend(); }

    void Initialise(int size);

private:
    std::vector<Agent> _population;
};

template <typename Agent>
void Population<Agent>::Initialise(int size)
{
    _population.reserve(size);

    for (int i = 0; i < size; ++i)
    {
        auto &agent = _population.emplace_back();
        agent.Initialise();
    }
}

#endif // POPULATION_HPP