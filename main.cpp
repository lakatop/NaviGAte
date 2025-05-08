#include "GA/AgentGA.hpp"
#include "GA/Evaluator.hpp"
#include "GA/Fitness.hpp"
#include "GA/Mutation.hpp"
#include "GA/NavigationGA.hpp"
#include "GA/Population.hpp"

int
main()
{
  AgentGA a;
  a.SetVelocity({ 0, 1 });
  a.Initialise(10);
  Population<AgentGA> pop;
  pop.Initialise(2);

  //   using popu = Population<AgentGA>;
  //   using mutt = RandomVelocityMutation<popu>;
  //   DestinationDistanceFitness<popu> fit;
  //   using ffit = DestinationDistanceFitness<popu>;
  Evaluator<Population<AgentGA>> eva;
  DestinationDistanceFitness<Population<AgentGA>> fit;
  eva.SetFitnesses(fit);
  eva.Evaluate(pop);
  eva.RankPopulation({ 1, 2, 3 });
  //   fit.EvaluatePopulation(pop);

  //   mutt mut;

  //   NavigateGA<popu, mutt, mutt> nav;
  //   nav.StartGA(pop, mut, mut);
}
