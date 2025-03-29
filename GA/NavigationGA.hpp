#include "Population.hpp"
#include "AgentGA.hpp"

template <typename Population, typename... Operators>
class NavigateGA
{
public:
    NavigateGA() {}

    void StartGA(Population &population, Operators... operators);

    template <typename Evaluator,
              typename std::enable_if_t<std::is_same_v<Evaluator, Evaluator<Operators...>>> void EvaluatePopulation(Evaluator<Operators...> &evaluator);
    int iterations = 5;
};

template <typename Population, typename... Operators>
void NavigateGA<Population, Operators...>::StartGA(Population &population, Operators... operators)
{
    for (int i = 0; i < 2; i++)
    {
        ((operators.ModifyPopulation(population)), ...);
    }
}

// template <typename Evaluator>
// void NavigateGA::EvaluatePopulation(Evaluator &evaluator)
// {
//     evaluator
// }