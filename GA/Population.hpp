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

private:
    std::vector<Agent> _population;
};

#endif // POPULATION_HPP