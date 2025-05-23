#pragma once
#include "GameObject.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"

class Bonus : public GameObject {
protected:
    float fallSpeed;
    bool isActive;
    sf::RectangleShape *shape;

public:
    Bonus(const sf::Vector2f& pos, const sf::Vector2f& size)
        : GameObject(pos, size), fallSpeed(200.0f), isActive(true) {
        shape = new sf::RectangleShape(size);
        shape->setFillColor(sf::Color::Yellow);
        shape->setPosition(pos);
    }

    virtual ~Bonus() = default;
    
    void update(float deltaTime) override;
    virtual void applyEffect(Paddle& paddle, Ball& ball) = 0;
    
    bool isBonusActive() const { return isActive; }
    void setActive(bool active) { isActive = active; }

    void draw(sf::RenderWindow& window) { window.draw(*shape); } 
}; 