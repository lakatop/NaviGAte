#ifndef I_AGENT_HPP
#define I_AGENT_HPP

#include <utility>

#include "Vector.hpp"

class IAgent
{
public:
    virtual Vector2D GetVelocity() = 0;
    virtual void SetVelocity(Vector2D velocity) = 0;
    virtual double GetMaxSpeed() = 0;
    virtual void SetMaxSpeed(double speed) = 0;
    virtual double GetMaxAcceleration() = 0;
    virtual void SetMaxAcceleration(double acceleration) = 0;
    virtual double GetMaxDeceleration() = 0;
    virtual void SetMaxDeceleration(double deceleration) = 0;
    virtual double GetMaxSteering() = 0;
    virtual void SetMaxSteering(double steering) = 0;
};

#endif // I_AGENT_HPP