#ifndef I_AGENT_HPP
#define I_AGENT_HPP

#include <utility>

#include "Vector.hpp"

class IAgent
{
public:
  virtual ~IAgent() {}
  virtual Vector2D GetVelocity() = 0;
  virtual void SetVelocity(const Vector2D& velocity) = 0;
  virtual double GetMaxSpeed() = 0;
  virtual void SetMaxSpeed(const double speed) = 0;
  virtual double GetMaxAcceleration() = 0;
  virtual void SetMaxAcceleration(const double acceleration) = 0;
  virtual double GetMaxDeceleration() = 0;
  virtual void SetMaxDeceleration(const double deceleration) = 0;
  virtual double GetMaxSteering() = 0;
  virtual void SetMaxSteering(const double steering) = 0;
};

#endif // I_AGENT_HPP