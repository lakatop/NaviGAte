#include "Fitness.hpp"
#include <functional>

/// @brief Class responsible for evaluation of population, based on provided
/// fitnesses.
/// @tparam Population the type of population
template<typename Population>
class Evaluator
{
public:
  /// @brief Set various fitness methods that will be called when evaluating
  /// population
  /// @tparam ...Fitnesses type of fitness class
  /// @param ...fitnesses fitness class objects, on which `EvaluatePopulation`
  /// method will be called
  template<typename... Fitnesses>
  void SetFitnesses(Fitnesses&&... fitnesses)
  {
    _evaluatePop = [=](Population& population) mutable {
      ((fitnesses.EvaluatePopulation(population)), ...);
      ((_fitnesses.push_back(fitnesses.GetFitnesses())), ...);
    };
  }

  /// @brief Start evaluation on `population`.
  void Evaluate(Population& population) { _evaluatePop(population); }

  /// @brief After population is evaluated, we need to assign rank to each
  /// individual. As each individual may have multiple fitnesses, this method
  /// uses `Ranker` class for assigning single ranking for each of them.
  /// @param fitnessWeights Initialiser list representing weight of each fitness
  /// (later used in Weighted sum method)
  void RankPopulation(std::initializer_list<double> fitnessWeights)
  {
    Ranker ranker(*this);
    ranker.SetFitnessWeights(fitnessWeights);
    resultFitnesses = ranker.RankPopulation();
  }

private:
  /// @brief Stores each fitness member that should be used on population. Calls
  /// them sequentially on population and stores the result for each fitness in
  /// `_fitnesses`
  std::function<void(Population&)> _evaluatePop;
  /// @brief Result of each fitness method that evaluated the population
  std::vector<std::vector<double>> _fitnesses;
  /// @brief Ranked fitnesses for each individual
  std::vector<double> resultFitnesses;

  /// @brief Class responsible for ranking each individual based on its
  /// fitnesses.
  class Ranker
  {
  public:
    Ranker(Evaluator<Population>& evaluator)
      : _evaluator(evaluator)
    {
    }

    /// @brief Each individual may have multiple fitnesses. Uses Z-score
    /// normalisation and Weighted Sum method for calculation of single rank for
    /// each individual.
    /// @return Ranking of individuals.
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

    /// @brief Set fitness weights used in Weighted Sum method.
    /// @param fitnessWeights Weights of fitnesses
    void SetFitnessWeights(std::initializer_list<double> fitnessWeights)
    {
      _fitnessWeights = fitnessWeights;
    }

  private:
    /// @brief Weights of fitnesses
    std::vector<double> _fitnessWeights;
    /// @brief Reference to base class holding results of fitnesses
    Evaluator<Population>& _evaluator;
  };
};