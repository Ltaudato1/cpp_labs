#pragma once
#include "GameObject.hpp"

class Paddle : public GameObject {
private:
    float moveSpeed;
    float minWidth;
    float maxWidth;
    bool isBottom;
    sf::RectangleShape *shape;

public:
    Paddle(const sf::Vector2f& pos, const sf::Vector2f& size, float speed, bool bottom)
        : GameObject(pos, size)
        , moveSpeed(speed)
        , minWidth(size.x * 0.5f)
        , maxWidth(size.x * 2.0f)
        , isBottom(bottom) {
        
        shape = new sf::RectangleShape(size);
        shape->setFillColor(sf::Color::Green);
    }
    
    void update(float deltaTime) override { shape->setPosition(position); }
    void move(float direction);
    void resize(float factor);
    
    float getMoveSpeed() const { return moveSpeed; }
    void setMoveSpeed(float speed) { moveSpeed = speed; }
    
    bool isBottomPaddle() const { return isBottom; }
    void setBottom(bool bottom) { isBottom = bottom; }

    void draw(sf::RenderWindow& window) override { window.draw(*shape); }

}; 