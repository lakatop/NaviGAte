#include "Population.hpp"
#include "AgentGA.hpp"

class NavigateGA
{
public:
    NavigateGA() {}

    template <typename Population, typename... Operators>
    void StartGA(Population &population, Operators... operators);
    int iterations = 5;
};

template <typename Population, typename... Operators>
void NavigateGA::StartGA(Population &population, Operators... operators)
{
    for (int i = 0; i < 2; i++)
    {
        ((operators.ModifyPopulation(population)), ...);
    }
}