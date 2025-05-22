#pragma once
#include "GameObject.hpp"

class Paddle : public GameObject {
private:
    float moveSpeed;
    float minWidth;
    float maxWidth;
    bool isBottom;

public:
    Paddle(const sf::Vector2f& pos, const sf::Vector2f& size, float speed, bool bottom = true);
    
    void update(float deltaTime) override;
    void move(float direction);
    void resize(float factor);
    
    float getMoveSpeed() const { return moveSpeed; }
    void setMoveSpeed(float speed) { moveSpeed = speed; }
    
    bool isBottomPaddle() const { return isBottom; }
    void setBottom(bool bottom) { isBottom = bottom; }
}; 