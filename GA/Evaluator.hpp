#include "Fitness.hpp"
#include <functional>

template<typename Population>
class Evaluator
{
public:
  template<typename... Fitnesses>
  void SetFitnesses(Fitnesses&&... fitnesses)
  {
    _evaluatePop = [=](Population& population) mutable {
      ((fitnesses.EvaluatePopulation(population)), ...);
      ((_fitnesses.push_back(fitnesses.GetFitnesses())), ...);
    };
  }

  void Evaluate(Population& population) { _evaluatePop(population); }

  template<typename... T>
  void RankPopulation(Population& population, T&&... fitnessWeights)
  {
    Ranker ranker(this);
    ranker.SetFitnessWeights(std::forward(fitnessWeights...));
    ranker.RankPopulation(population);
  }

private:
  std::function<void(Population&)> _evaluatePop;
  std::vector<std::vector<double>> _fitnesses;

  class Ranker
  {
  public:
    Ranker(Evaluator<Population>& evaluator)
      : _evaluator(evaluator)
    {
    }

    void RankPopulation(Population& population)
    {
      auto zScoreNormalize = [](const auto& fitnessValues) {
        // Calculate things needed for z-score normalisation
        double mean =
          std::accumulate(fitnessValues.begin(), fitnessValues.end(), 0);
        mean = mean / fitnessValues.size();

        double squaredSum{ 0 };
        for (const auto fitValue : fitnessValues)
          squaredSum += ((mean - fitValue) * (mean - fitValue));

        double variance{ squaredSum / fitnessValues.size() };

        double stdDev{ std::sqrt(variance) };
        auto normalisedFitnesses = std::vector(0, fitnessValues.size());
        if (stdDev == 0)
          return normalisedFitnesses;

        // Finally, normalise fitnesses
        for (int i = 0; i < fitnessValues.size(); ++i) {
          normalisedFitnesses[i] = (fitnessValues[i] - mean) / stdDev;
        }

        return normalisedFitnesses;
      };
    }

    template<typename... T>
    void SetFitnessWeights(T&&... fitnessWeights)
    {
      ((_fitnessWeights.emplace(fitnessWeights)), ...);
    }

  private:
    std::vector<double> _fitnessWeights;
    Evaluator<Population>& _evaluator;
  };
};