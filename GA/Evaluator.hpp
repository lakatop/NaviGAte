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

  void RankPopulation(std::initializer_list<double> fitnessWeights)
  {
    Ranker ranker(*this);
    ranker.SetFitnessWeights(fitnessWeights);
    resultFitnesses = ranker.RankPopulation();
  }

private:
  std::function<void(Population&)> _evaluatePop;
  std::vector<std::vector<double>> _fitnesses;
  std::vector<double> resultFitnesses;

  class Ranker
  {
  public:
    Ranker(Evaluator<Population>& evaluator)
      : _evaluator(evaluator)
    {
    }

    std::vector<double> RankPopulation()
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
        std::vector<double> normalisedFitnesses(0, fitnessValues.size());
        if (stdDev == 0)
          return normalisedFitnesses;

        // Finally, normalise fitnesses
        for (int i = 0; i < fitnessValues.size(); ++i) {
          normalisedFitnesses[i] = (fitnessValues[i] - mean) / stdDev;
        }

        return normalisedFitnesses;
      };

      // Normalise each fitness calculated
      std::vector<std::vector<double>> normalisedFitnesses{};
      for (const auto& fitnesses : _evaluator._fitnesses) {
        normalisedFitnesses.emplace_back(zScoreNormalize(fitnesses));
      }

      // Apply weighted sum method and get resulting fitnesses
      std::vector<double> resultFitnesses{};
      for (int i = 0; i < normalisedFitnesses[0].size(); ++i) {
        double fitness = 0;
        for (int j = 0; j < normalisedFitnesses.size(); ++j) {
          fitness += normalisedFitnesses[j][i] * _fitnessWeights[j];
        }

        resultFitnesses.push_back(fitness);
      }

      return resultFitnesses;
    }

    void SetFitnessWeights(std::initializer_list<double> fitnessWeights)
    {
      _fitnessWeights = fitnessWeights;
    }

  private:
    std::vector<double> _fitnessWeights;
    Evaluator<Population>& _evaluator;
  };
};