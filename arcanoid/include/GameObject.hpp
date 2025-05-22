#pragma once
#include <SFML/Graphics.hpp>

class GameObject {
protected:
    sf::Vector2f position;
    sf::Vector2f size;
    sf::RectangleShape shape;

public:
    GameObject(const sf::Vector2f& pos, const sf::Vector2f& size);
    virtual ~GameObject() = default;

    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window);
    
    const sf::Vector2f& getPosition() const { return position; }
    const sf::Vector2f& getSize() const { return size; }
    
    void setPosition(const sf::Vector2f& pos);
    bool checkCollision(const GameObject& other) const;
}; 