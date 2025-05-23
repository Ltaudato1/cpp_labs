#include "../include/Bonus.hpp"

void Bonus::update(float deltaTime) {
    if (isActive) {
        position.y += fallSpeed * deltaTime;
        shape->setPosition(position);
    }
}