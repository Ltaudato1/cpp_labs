#include "../include/Ball.hpp"

void Ball::update(float deltaTime) {
    if (!sticky) {
        float currentSpeed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        if (currentSpeed > 0) {
            velocity.x = (velocity.x / currentSpeed) * speed;
            velocity.y = (velocity.y / currentSpeed) * speed;
        }
        
        position += velocity * deltaTime;
        shape->setPosition(position);
    }
}

void Ball::launch(const sf::Vector2f& direction) {
    sticky = false;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0) {
        velocity = direction * (speed / length);
    }
}

void Ball::reflect(const sf::Vector2f& normal) {
    float length = std::sqrt(normal.x * normal.x + normal.y * normal.y);
    if (length > 0) {
        float dot = velocity.x * normal.x + velocity.y * normal.y;
        velocity.x = velocity.x - 2 * dot * normal.x;
        velocity.y = velocity.y - 2 * dot * normal.y;
        
        float currentSpeed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        if (currentSpeed > 0) {
            velocity.x = (velocity.x / currentSpeed) * speed;
            velocity.y = (velocity.y / currentSpeed) * speed;
        }
    }
} 