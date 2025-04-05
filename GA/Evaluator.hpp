#include <functional>

template<typename Population>
class Evaluator
{
public:
  Evaluator(Population pop) { _pop = pop; }

  template<typename... Fitnesses>
  void EvaluatorFit(Fitnesses&&... fitnesses)
  {
    evaluatePop = [=]() mutable {
      ((fitnesses.EvaluatePopulation(_pop)), ...);
    };
  }

  void Evaluate(Population& population) { evaluatePop(); }

  std::function<void()> evaluatePop;
  Population _pop;
};