#pragma once
#include "GameObject.hpp"

class Paddle : public GameObject {
private:
    float moveSpeed;
    float minWidth;
    float maxWidth;
    bool isBottom;
    sf::RectangleShape *shape;
    sf::RectangleShape *bottomShape;
public:
    Paddle(const sf::Vector2f& pos, const sf::Vector2f& size, float speed, bool bottom);
    
    void update(float deltaTime) override { 
        shape->setPosition(position);
    }

    void move(float direction) {
        position.x += direction * moveSpeed;
        shape->setPosition(position);
    }

    
    float getMoveSpeed() const { return moveSpeed; }
    void setMoveSpeed(float speed) { moveSpeed = speed; }
    
    bool isBottomPaddle() const { return isBottom; }
    void setBottom(bool bottom) { isBottom = bottom; }

    void draw(sf::RenderWindow& window) override { 
        window.draw(*shape);
        if (isBottom) {
            window.draw(*bottomShape);
        }
    }


    void setPosition(const sf::Vector2f& pos) override {
        position = pos;
        shape->setPosition(pos);
    }

    sf::FloatRect getBounds() const {
        return shape->getGlobalBounds();
    }

    void resize(float factor);
}; 