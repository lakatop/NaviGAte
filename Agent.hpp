#ifndef AGENT_HPP
#define AGENT_HPP

#include "IAgent.hpp"

#include <utility>

class Agent : public IAgent
{
public:
    Agent() : _maxSpeed(5.), _maxAcceleration(1.5), _maxDeceleration(1.5) {}

    Vector2D GetVelocity() { return _velocity; }
    void SetVelocity(Vector2D velocity) { _velocity = velocity; }
    double GetMaxSpeed() { return _maxSpeed; }
    void SetMaxSpeed(double speed) { _maxSpeed = speed; }
    double GetMaxAcceleration() { return _maxAcceleration; }
    void SetMaxAcceleration(double acceleration) { _maxAcceleration = acceleration; }
    double GetMaxDeceleration() { return _maxDeceleration; }
    void SetMaxDeceleration(double deceleration) { _maxDeceleration = deceleration; }

    void Initialise();

private:
    Vector2D _velocity;
    double _maxSpeed;
    double _maxAcceleration;
    double _maxDeceleration;
};

void Agent::Initialise()
{
    auto maxAcc = GetMaxAcceleration();
    auto maxDecc = GetMaxDeceleration();
    _velocity = {1, 1};

    int range = maxAcc - (-maxDecc) + 1;
    double change = rand() % range + (-maxDecc);
    _velocity *= change;
}

#endif // AGENT_HPP