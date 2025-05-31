#include "../include/GameObject.hpp"

GameObject::GameObject(const sf::Vector2f& pos, const sf::Vector2f& size)
    : position(pos), size(size) {
    shape = new sf::RectangleShape(size);
    shape->setPosition(position);
}

GameObject::~GameObject() {
    delete shape;
}

void GameObject::draw(sf::RenderWindow& window) {
    window.draw(*shape);
}

void GameObject::setPosition(const sf::Vector2f& pos) {
    position = pos;
    shape->setPosition(position);
}

const sf::Vector2f& GameObject::getPosition() const {
    return position;
}

const sf::Vector2f& GameObject::getSize() const {
    return size;
}

bool GameObject::checkCollision(const GameObject& other) const {
    return shape->getGlobalBounds().intersects(other.shape->getGlobalBounds());
}

void GameObject::setShape(sf::Shape* newShape) {
    delete shape;
    shape = newShape;
    shape->setPosition(position);
} 