#include "GA/Mutation.hpp"
#include "GA/AgentGA.hpp"
#include "GA/Population.hpp"
#include "GA/NavigationGA.hpp"

int main()
{
    AgentGA a;
    a.SetVelocity({0, 1});
    a.Initialise(10);
    Population<AgentGA> pop;
    pop.Initialise(2);

    using popu = Population<AgentGA>;
    using mutt = RandomVelocityMutation<popu>;

    mutt mut;

    NavigateGA<popu, mutt, mutt> nav;
    nav.StartGA(pop, mut, mut);
}
