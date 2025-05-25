#pragma once
#include "GameObject.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

class Ball : public GameObject {
public:
    Ball(const sf::Vector2f& position, float radius, float speed)
        : GameObject(position, sf::Vector2f(radius * 2, radius * 2)), radius(radius), speed(speed), sticky(true), prevPosition(position) { 
            shape = new sf::CircleShape(radius);
            shape->setFillColor(sf::Color::White);
            shape->setPosition(position);
    }

    void update(float deltaTime) override; 

    void draw(sf::RenderWindow& window) override { window.draw(*shape); }

    void launch(const sf::Vector2f& direction);

    void reflect(const sf::Vector2f& normal); 

    bool isBallSticky() const { return sticky; }

    void setSticky(bool value) { sticky = value; }

    void setPosition(const sf::Vector2f& pos) override {
        position = pos;
        shape->setPosition(pos);
    }

    sf::FloatRect getBounds() const {
        return sf::FloatRect(
            position.x - radius,
            position.y - radius,
            radius * 2,
            radius * 2
        );
    }

    float getSpeed() const { return speed; }
    void setSpeed(float speed) { this->speed = speed; }

    float getRadius() { return radius; }

    const sf::Vector2f& getPrevPosition() { return prevPosition; }

private:
    float radius;
    float speed;
    bool sticky;
    sf::CircleShape *shape;
    sf::Vector2f velocity;
    sf::Vector2f prevPosition;
}; 