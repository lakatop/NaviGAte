#include "GA/Mutation.hpp"
#include "GA/AgentGA.hpp"
#include "GA/Population.hpp"
#include "GA/NavigationGA.hpp"

int main()
{
    AgentGA a;
    a.SetVelocity({0, 1});
    a.Initialise(10);
    // Population<AgentGA> pop;
    // pop.Initialise(2);

    // RandomVelocityMutation<Population<AgentGA>> mut;

    // NavigateGA nav;
    // nav.StartGA(pop, mut, mut);
}
