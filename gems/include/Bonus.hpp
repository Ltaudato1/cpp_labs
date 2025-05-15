#pragma once

#include <SFML/Graphics.hpp>

// Forward declarations
enum class GemType;
class Gem;
class Grid;

class Bonus : public sf::Drawable {
public:
    virtual ~Bonus() = default;
    virtual void activate(Gem& target, Grid& grid) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
};

class ColorChangeBonus : public Bonus {
public:
    ColorChangeBonus(GemType originalType);
    void activate(Gem& target, Grid& grid) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    GemType originalType;
    sf::CircleShape shape;
};

class BombBonus : public Bonus {
public:
    BombBonus();
    void activate(Gem& target, Grid& grid) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::CircleShape shape;
}; 