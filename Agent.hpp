#ifndef AGENT_HPP
#define AGENT_HPP

#include "IAgent.hpp"

#include <utility>

class Agent : public IAgent
{
public:
    Vector2D GetVelocity() { return _velocity; }
    void SetVelocity(Vector2D velocity) { _velocity = velocity; }
    double GetMaxSpeed() { return _maxSpeed; }
    void SetMaxSpeed(double speed) { _maxSpeed = speed; }
    double GetMaxAcceleration() { return _maxAcceleration; }
    void SetMaxAcceleration(double acceleration) { _maxAcceleration = acceleration; }
    double GetMaxDeceleration() { return _maxDeceleration; }
    void SetMaxDeceleration(double deceleration) { _maxDeceleration = deceleration; }

private:
    Vector2D _velocity;
    double _maxSpeed;
    double _maxAcceleration;
    double _maxDeceleration;
};

#endif // AGENT_HPP