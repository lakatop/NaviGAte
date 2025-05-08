#ifndef AGENT_GA_HPP
#define AGENT_GA_HPP

#include "../IAgent.hpp"
#include "../Utils/Utils.hpp"

#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

namespace {
/// @brief Computes vector that starts where `v1` ends, have `size`,
/// and is rotated `angle` degrees relative to `v1` direction
Vector2D
ComputeSubsequentVector(Vector2D& v1, double size, double angle)
{
  double theta1 = std::atan2(v1.y, v1.x);
  double theta2 = theta1 + angle * (M_PI / 180);

  return { .x = std::round(size * std::cos(theta2) * 100) / 100,
           .y = std::round(size * std::sin(theta2) * 100 / 100) };
}
}

/// @brief Class representing genetic algorithm agent. It implements base Agent
/// interface `IAgent`, but also has additional methods so it can be used as
/// individual in GA
class AgentGA : public IAgent
{
public:
  AgentGA()
    : _maxSpeed(5.)
    , _maxAcceleration(1.5)
    , _maxDeceleration(1.5)
    , _maxSteering(30)
  {
  }

  /*
  Basic getters and setters for data members
  */
  Vector2D GetVelocity() const { return _velocity; }
  Vector2D GetVelocity() { return _velocity; }
  void SetVelocity(const Vector2D& velocity) { _velocity = velocity; }
  Vector2D GetPosition() const { return _position; }
  Vector2D GetPosition() { return _position; }
  void SetPosition(const Vector2D& position) { _position = position; }
  Vector2D GetDestination() const { return _destination; }
  Vector2D GetDestination() { return _destination; }
  void SetDestination(const Vector2D& destination)
  {
    _destination = destination;
  }
  double GetMaxSpeed() const { return _maxSpeed; }
  double GetMaxSpeed() { return _maxSpeed; }
  void SetMaxSpeed(const double speed) { _maxSpeed = speed; }
  double GetMaxAcceleration() const { return _maxAcceleration; }
  double GetMaxAcceleration() { return _maxAcceleration; }
  void SetMaxAcceleration(const double acceleration)
  {
    _maxAcceleration = acceleration;
  }
  double GetMaxDeceleration() const { return _maxDeceleration; }
  double GetMaxDeceleration() { return _maxDeceleration; }
  void SetMaxDeceleration(const double deceleration)
  {
    _maxDeceleration = deceleration;
  }
  double GetMaxSteering() const { return _maxSteering; }
  double GetMaxSteering() { return _maxSteering; }
  void SetMaxSteering(const double steering) { _maxSteering = steering; }

  std::vector<Vector2D>& GetPath() { return _path; }
  const std::vector<Vector2D>& GetPath() const { return _path; }
  std::vector<double>& GetAccelerations() { return _accelerations; }
  const std::vector<double>& GetAccelerations() const { return _accelerations; }

  /// @brief Initialise random individual (represented as a path) with
  /// `pathLength` lenght
  void Initialise(int pathLenght);

  /// @brief Construct a path represented as a vector of Vector2Ds from current
  /// accelerations and steerings
  void ConstructPath();

  /// @brief Debug printing of agents path
  void Print();

private:
  /// @brief Agents current velocity
  Vector2D _velocity;
  /// @brief Agents current position
  Vector2D _position;
  /// @brief Agents destination
  Vector2D _destination;
  /// @brief Path on which Agent should move
  std::vector<Vector2D> _path;
  /// @brief List of accelerations applied along the path
  std::vector<double> _accelerations;
  /// @brief List of steering applied along the path
  std::vector<double> _steerings;

  /// @brief Agents limiting speed - agent cannot move faster than this value
  double _maxSpeed;
  /// @brief Agents limiting acceleration - agent cannot accelerate more
  /// (between path segments) than this value
  double _maxAcceleration;
  /// @brief Agents limiting deceleration - agent cannot decelerate more
  /// (between path segments) than this value
  double _maxDeceleration;
  /// @brief Agents limiting steering (in degrees) - agent cannot change
  /// direction more (between path segments) than this value
  double _maxSteering;
};

void
AgentGA::Initialise(int pathLength)
{
  // Create random steerings and accelerations
  for (int i = 0; i < pathLength; i++) {
    double acceleration =
      (_maxAcceleration + _maxDeceleration) * Utils::NextRandom() -
      _maxDeceleration;
    double steering = (_maxSteering * 2 * Utils::NextRandom()) - _maxSteering;
    _accelerations.push_back(acceleration);
    _steerings.push_back(steering);
  }

  ConstructPath();
}

void
AgentGA::ConstructPath()
{
  auto speed = _velocity.Size();
  auto segment = _velocity;
  for (int i = 0; i < _path.size(); ++i) {
    const auto newSpeed = std::clamp(speed + _accelerations[i], 0., _maxSpeed);
    const auto nextSegment =
      ComputeSubsequentVector(segment, newSpeed, _steerings[i]);
    _path.push_back(nextSegment);
    speed = newSpeed;
    segment = nextSegment;
  }
}

void
AgentGA::Print()
{
  std::cout << "Agent" << std::endl;
  for (auto& segment : _path) {
    std::cout << "x: " << segment.x << " y: " << segment.y << std::endl;
  }
}

#endif // AGENT_GA_HPP