#ifndef MUTATION_HPP
#define MUTATION_HPP

#include "../IAgent.hpp"
#include "../Utils/Utils.hpp"

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
            auto maxAcc = agent.GetMaxAcceleration();
            auto maxDecc = agent.GetMaxDeceleration();
            auto &accelerations = agent.GetAccelerations();
            for (int i = 0; i < accelerations.size(); ++i)
            {
                double newAcceleration = (maxAcc + maxDecc) * Utils::NextRandom() - maxDecc;
                accelerations[i] = newAcceleration;
            }
        }
    }

private:
    float _mutationProbability;
};

#endif // MUTATION_HPP