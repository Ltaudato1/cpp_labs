#pragma once
#include "GameObject.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"

class Bonus : public GameObject {
protected:
    float fallSpeed;
    bool isActive;

public:
    Bonus(const sf::Vector2f& pos, const sf::Vector2f& size);
    virtual ~Bonus() = default;
    
    void update(float deltaTime) override;
    virtual void applyEffect(Paddle& paddle, Ball& ball) = 0;
    
    bool isBonusActive() const { return isActive; }
    void setActive(bool active) { isActive = active; }
}; 