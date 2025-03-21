#include "GA/Mutation.hpp"
#include "AgentGA.hpp"
#include "GA/Population.hpp"
#include "GA/NavigationGA.hpp"

int main()
{
    AgentGA a;
    Population<AgentGA> pop;
    pop.Initialise(2);

    RandomVelocityMutation<Population<AgentGA>> mut;

    NavigateGA nav;
    nav.StartGA(pop, mut, mut);
}
