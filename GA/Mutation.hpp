#ifndef MUTATION_HPP
#define MUTATION_HPP

#include "../IAgent.hpp"

template <typename Population>
class IMutation
{
public:
    virtual ~IMutation() {}

    virtual float GetMutationProbability() = 0;

    virtual void ModifyPopulation(Population &population) = 0;
};

template <typename Population>
class RandomVelocityMutation : public IMutation<Population>
{
public:
    ~RandomVelocityMutation() {};
    float GetMutationProbability() override { return _mutationProbability; }
    void ModifyPopulation(Population &population) override
    {
        for (auto &agent : population)
        {
            auto &agentPath = agent.GetPath();
            auto maxAcc = agent.GetMaxAcceleration();
            auto maxDecc = agent.GetMaxDeceleration();
            for (auto &pathSegment : agentPath)
            {
                int range = maxAcc - (-maxDecc) + 1;
                int change = rand() % range + (-maxDecc);
                pathSegment *= change;
            }
        }

        population.Print();
    }

private:
    float _mutationProbability;
};

#endif // MUTATION_HPP