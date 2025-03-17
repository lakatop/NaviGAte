#ifndef MUTATION_HPP
#define MUTATION_HPP

#include "../IAgent.hpp"

template <typename Population>
class IMutation
{
public:
    virtual ~IMutation() = 0;

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
        for (auto &&agent : population)
        {
            auto maxAcc = agent.GetMaxAcceleration();
            auto maxDecc = agent.GetMaxDeceleration();
            Vector2D currentVelocity = agent.GetVelocity();

            int range = maxAcc - (-maxDecc) + 1;
            int change = rand() % range + (-maxDecc);
            currentVelocity *= change;
        }
    }

private:
    float _mutationProbability;
};

#endif // MUTATION_HPP