#include "../include/Paddle.hpp"



void Paddle::move(float direction) {
    position.x += direction * moveSpeed;
    shape->setPosition(position);
}

void Paddle::resize(float factor) {
    float newWidth = size.x * factor;
    if (newWidth >= minWidth && newWidth <= maxWidth) {
        size.x = newWidth;
        static_cast<sf::RectangleShape*>(shape)->setSize(size);
    }
}