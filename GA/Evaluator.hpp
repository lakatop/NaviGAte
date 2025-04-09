#include <functional>

template<typename Population>
class Evaluator
{
public:
  template<typename... Fitnesses>
  void SetFitnesses(Fitnesses&&... fitnesses)
  {
    evaluatePop = [=](Population& population) mutable {
      ((fitnesses.EvaluatePopulation(population)), ...);
    };
  }

  void Evaluate(Population& population) { evaluatePop(population); }

  std::function<void(Population&)> evaluatePop;
  Population _pop;
};