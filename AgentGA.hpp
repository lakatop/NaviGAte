#ifndef AGENT_GA_HPP
#define AGENT_GA_HPP

#include "IAgent.hpp"

#include <utility>
#include <vector>
#include <iostream>

class AgentGA : public IAgent
{
public:
    AgentGA() : _maxSpeed(5.), _maxAcceleration(1.5), _maxDeceleration(1.5) {}

    Vector2D GetVelocity() { return _velocity; }
    void SetVelocity(Vector2D velocity) { _velocity = velocity; }
    double GetMaxSpeed() { return _maxSpeed; }
    void SetMaxSpeed(double speed) { _maxSpeed = speed; }
    double GetMaxAcceleration() { return _maxAcceleration; }
    void SetMaxAcceleration(double acceleration) { _maxAcceleration = acceleration; }
    double GetMaxDeceleration() { return _maxDeceleration; }
    void SetMaxDeceleration(double deceleration) { _maxDeceleration = deceleration; }

    void Initialise(int pathLenght);
    void Print();

    std::vector<Vector2D> &GetPath() { return _path; }
    const std::vector<Vector2D> &GetPath() const { return _path; }

private:
    Vector2D _velocity;
    std::vector<Vector2D> _path;
    double _maxSpeed;
    double _maxAcceleration;
    double _maxDeceleration;
};

void AgentGA::Initialise(int pathLength)
{
    auto maxAcc = GetMaxAcceleration();
    auto maxDecc = GetMaxDeceleration();

    for (int i = 0; i < pathLength; i++)
    {
        _velocity = {1, 1};
        int range = maxAcc - (-maxDecc) + 1;
        double change = rand() % range + (-maxDecc);
        _velocity *= change;
        _path.push_back(_velocity);
    }
}

void AgentGA::Print()
{
    std::cout << "Agent" << std::endl;
    for (auto &segment : _path)
    {
        std::cout << "x: " << segment.x << " y: " << segment.y << std::endl;
    }
}

#endif // AGENT_GA_HPP