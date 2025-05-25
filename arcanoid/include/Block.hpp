#pragma once
#include "GameObject.hpp"
#include "Bonus.hpp"
#include <random>

class Block : public GameObject {
private:
    int health;
    bool destructible;
    bool hasBonus;
    float speedMult;
    sf::RectangleShape* shape;
    std::mt19937 rng;

public:
    Block(const sf::Vector2f& pos, const sf::Vector2f& size, int initialHealth, bool isDestructible, bool bonus, float speedMultiplier);

    bool onHit() {
        if (destructible) {
            health--;
            return 1;
        } else {
            return 0;
        }
    }

    bool isAlive() const {
        return !destructible || health > 0;
    }

    bool hasBonusBlock() const {
        return hasBonus;
    }

    float getSpeedMultiplier() const {
        return speedMult;
    }

    int getHealth() const {
        return health;
    }

    Bonus* createBonus(); 

    void draw(sf::RenderWindow& window) override;

    sf::FloatRect getBounds() const {
        return shape->getGlobalBounds();
    }

    ~Block() {
        delete shape;
    }
}; 