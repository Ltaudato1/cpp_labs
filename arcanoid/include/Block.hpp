#pragma once
#include "GameObject.hpp"

class Block : public GameObject {
protected:
    int health;
    bool isDestructible;
    bool hasBonus;
    float speedMultiplier;

public:
    Block(const sf::Vector2f& pos, const sf::Vector2f& size, 
          int health = 1, bool destructible = true, 
          bool bonus = false, float speedMult = 1.0f);
    
    virtual ~Block() = default;
    
    virtual void update(float deltaTime) override;
    virtual void onHit();
    
    bool isAlive() const { return health > 0; }
    bool isBonusBlock() const { return hasBonus; }
    float getSpeedMultiplier() const { return speedMultiplier; }
    
    void setHealth(int newHealth) { health = newHealth; }
    void setDestructible(bool destructible) { isDestructible = destructible; }
    void setBonus(bool bonus) { hasBonus = bonus; }
    void setSpeedMultiplier(float mult) { speedMultiplier = mult; }
}; 