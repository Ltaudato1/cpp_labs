#pragma once
#include "GameObject.hpp"

class Block : public GameObject {
protected:
    int health;
    bool isDestructible;
    bool hasBonus;
    float speedMultiplier;
    sf::RectangleShape *shape;

public:
    Block(const sf::Vector2f& pos, const sf::Vector2f& size,
             int health, bool destructible, bool hasBonus, float speedMultiplier)
    : GameObject(pos, size)
    , health(health)
    , isDestructible(destructible)
    , hasBonus(hasBonus)
    , speedMultiplier(speedMultiplier) {
    
    shape = new sf::RectangleShape(size);
    shape->setFillColor(sf::Color::Red);
}
    
    virtual ~Block() = default;
    
    virtual void update(float deltaTime) override { shape->setPosition(position); }

    void draw(sf::RenderWindow& window) override { window.draw(*shape); }
    
    bool isAlive() const { return health > 0; }
    bool isBonusBlock() const { return hasBonus; }
    float getSpeedMultiplier() const { return speedMultiplier; }
    int getHealth() const { return health; }
    
    void setHealth(int newHealth) { health = newHealth; }
    void setDestructible(bool destructible) { isDestructible = destructible; }
    void setBonus(bool bonus) { hasBonus = bonus; }
    void setSpeedMultiplier(float mult) { speedMultiplier = mult; }
    void setHasBonus(bool value) { hasBonus = value; }

    void onHit() {
        if (isDestructible) {
            health--;
        }
    }
}; 