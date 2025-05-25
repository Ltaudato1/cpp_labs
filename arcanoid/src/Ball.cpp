#include "../include/Ball.hpp"

void Ball::update(float deltaTime) {
    if (!sticky) {
        prevPosition = position;
        position += velocity * deltaTime;
        shape->setPosition(position);
    }
}

void Ball::launch(const sf::Vector2f& direction) {
    sticky = false;
    velocity = direction * speed;
}

void Ball::reflect(const sf::Vector2f& normal) {
    float length = std::sqrt(normal.x * normal.x + normal.y * normal.y);
    if (length > 0) {
        float nx = normal.x / length;
        float ny = normal.y / length;
        
        float dot = velocity.x * nx + velocity.y * ny;
        
        velocity.x = velocity.x - 2 * dot * nx;
        velocity.y = velocity.y - 2 * dot * ny;
        
        float currentSpeed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        if (currentSpeed > 0) {
            velocity.x = (velocity.x / currentSpeed) * speed;
            velocity.y = (velocity.y / currentSpeed) * speed;
        }
    }
} 