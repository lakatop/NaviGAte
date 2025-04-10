#ifndef AGENT_GA_HPP
#define AGENT_GA_HPP

#include "../IAgent.hpp"
#include "../Utils/Utils.hpp"

#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

namespace {
//! Computes vector that starts where v1 ends, have size,
//! and is rotated angle degrees relative to v1 direction
Vector2D
ComputeSubsequentVector(Vector2D& v1, double size, double angle)
{
  double theta1 = std::atan2(v1.y, v1.x);
  double theta2 = theta1 + angle * (M_PI / 180);

  return { .x = std::round(size * std::cos(theta2) * 100) / 100,
           .y = std::round(size * std::sin(theta2) * 100 / 100) };
}
}

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

  void Initialise(int pathLenght);
  void ConstructPath();
  void Print();

  std::vector<Vector2D>& GetPath() { return _path; }
  const std::vector<Vector2D>& GetPath() const { return _path; }
  std::vector<double>& GetAccelerations() { return _accelerations; }
  const std::vector<double>& GetAccelerations() const { return _accelerations; }

private:
  Vector2D _velocity;
  Vector2D _position;
  Vector2D _destination;
  std::vector<Vector2D> _path;
  std::vector<double> _accelerations;
  std::vector<double> _steerings;

  double _maxSpeed;
  double _maxAcceleration;
  double _maxDeceleration;
  double _maxSteering; // in degrees
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