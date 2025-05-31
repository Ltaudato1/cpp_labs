#include "../include/Paddle.hpp"

Paddle::Paddle(const sf::Vector2f& pos, const sf::Vector2f& size, float speed, bool bottom)
        : GameObject(pos, size)
        , moveSpeed(speed)
        , minWidth(size.x * 0.5f)
        , maxWidth(size.x * 2.0f)
        , isBottom(bottom) {
        
    shape = new sf::RectangleShape(size);
    bottomShape = new sf::RectangleShape(sf::Vector2f(800, 10));
    shape->setFillColor(sf::Color::Green);
    shape->setPosition(pos);
    bottomShape->setFillColor(sf::Color::White);
    bottomShape->setPosition(0, 590);
}

void Paddle::resize(float factor) {
        float newWidth = size.x * factor;
        if (newWidth >= minWidth && newWidth <= maxWidth) {
            size.x = newWidth;
            shape->setSize(size);
        }
}