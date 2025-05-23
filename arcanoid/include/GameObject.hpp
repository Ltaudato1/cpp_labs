#pragma once
#include <SFML/Graphics.hpp>

class GameObject {
protected:
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Shape* shape;

public:
    GameObject(const sf::Vector2f& pos, const sf::Vector2f& size);
    virtual ~GameObject();

    // Rule of Five: forbid copy/move
    GameObject(const GameObject&) = delete;
    GameObject& operator=(const GameObject&) = delete;
    GameObject(GameObject&&) = delete;
    GameObject& operator=(GameObject&&) = delete;

    virtual void update(float deltaTime) {}
    virtual void draw(sf::RenderWindow& window);
    
    const sf::Vector2f& getPosition() const;
    const sf::Vector2f& getSize() const;
    
    virtual void setPosition(const sf::Vector2f& pos);
    virtual bool checkCollision(const GameObject& other) const;
    sf::FloatRect getBounds() const { return shape->getGlobalBounds(); }

    void setShape(sf::Shape* newShape);
}; 