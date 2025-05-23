#pragma once
#include "GameObject.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

class Ball : public GameObject {
public:

    Ball(const sf::Vector2f& position, float radius, float speed)
        : GameObject(position, sf::Vector2f(radius * 2, radius * 2)), radius(radius), speed(speed), sticky(true) { 
            shape = new sf::CircleShape(radius);
            shape->setFillColor(sf::Color::White);
    }

    void update(float deltaTime) override; 

    void draw(sf::RenderWindow& window) override { window.draw(*shape); }

    void launch(const sf::Vector2f& direction);

    void reflect(const sf::Vector2f& normal); 

    bool isBallSticky() const { return sticky; }

    void setSticky(bool value) { sticky = value; }
private:
    float radius;
    float speed;
    bool sticky;
    sf::CircleShape *shape;
    sf::Vector2f velocity;
}; 