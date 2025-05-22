#pragma once
#include "GameObject.hpp"

class Ball : public GameObject {
private:
    sf::Vector2f velocity;
    float speed;
    bool isSticky;
    bool isActive;

public:
    Ball(const sf::Vector2f& pos, float radius, float initialSpeed);
    
    void update(float deltaTime) override;
    void launch(const sf::Vector2f& direction);
    void reflect(const sf::Vector2f& normal);
    void setSticky(bool sticky) { isSticky = sticky; }
    void setActive(bool active) { isActive = active; }
    
    const sf::Vector2f& getVelocity() const { return velocity; }
    float getSpeed() const { return speed; }
    bool isBallSticky() const { return isSticky; }
    bool isBallActive() const { return isActive; }
    
    void setSpeed(float newSpeed) { speed = newSpeed; }
    void setVelocity(const sf::Vector2f& newVelocity) { velocity = newVelocity; }
}; 