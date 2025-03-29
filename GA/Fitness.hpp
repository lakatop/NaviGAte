#ifndef FITNESS_HPP
#define FITNESS_HPP

#include "../IAgent.hpp"
#include "../Utils/Utils.hpp"

template <typename Population>
class IFitness
{
public:
    virtual ~IFitness() {}

    virtual void ModifyPopulation(Population &population) = 0;
};

template <typename Population>
class DestinationDistanceFitness : public IFitness<Population>
{
    ~DestinationDistanceFitness() {}

    virtual void ModifyPopulation(Population &population)
    {
        for (auto &agent : population)
        {
            const auto &agentsPath = agent.GetPath();
            const auto agentsEndPosition = !agentsPath.emtpy() ? agentsPath.back() : agent.GetPostion();
        }
    }
};

#endif // FITNESS_HPP