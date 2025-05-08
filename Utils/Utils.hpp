#ifndef UTILS_HPP
#define UTILS_HPP

#include <random>

namespace Utils {

/// @brief Returns random double in range [0,1)
double
NextRandom()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dist(0, 1);
  return dist(gen);
}
}

#endif // UTILS_HPP