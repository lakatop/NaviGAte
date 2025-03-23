#ifndef FITNESS_HPP
#define FITNESS_HPP

#include "../IAgent.hpp"
#include "../Utils/Utils.hpp"

template <typename Population>
class IFitness
{
public:
    virtual ~IMutation() {}

    virtual float GetMutationProbability() = 0;

    virtual void ModifyPopulation(Population &population) = 0;
};

#endif // FITNESS_HPP