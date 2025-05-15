#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Bonus.hpp"

enum class GemType {
    RED,
    BLUE,
    GREEN,
    YELLOW,
    PURPLE,
    ORANGE
};

enum class GemState {
    IDLE,
    FALLING,
    DISAPPEARING,
    APPEARING
};

class Gem : public sf::Drawable {
public:
    Gem(GemType type, const sf::Vector2f& position);
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setPosition(const sf::Vector2f& position);
    void setType(GemType type);
    GemType getType() const;
    bool hasBonus() const;
    void setBonus(std::unique_ptr<Bonus> bonus);
    void activateBonus(Gem& target, Grid& grid);
    sf::Vector2f getPosition() const { return shape.getPosition(); }
    
    void update(float deltaTime);
    void startFalling(const sf::Vector2f& targetPosition);
    void startDisappearing();
    void startAppearing();
    bool isAnimating() const { return state != GemState::IDLE; }
    
    static constexpr float SIZE = 40.f;
    static constexpr float PADDING = 5.f;
    static constexpr float TOTAL_SIZE = SIZE + PADDING;
    static constexpr float BONUS_CHANCE = 0.1f;
    static constexpr float FALL_SPEED = 500.f;  // пикселей в секунду
    static constexpr float DISAPPEAR_TIME = 0.3f;  // секунды
    static constexpr float APPEAR_TIME = 0.3f;  // секунды

private:
    GemType type;
    std::unique_ptr<Bonus> bonus;
    sf::RectangleShape shape;
    
    GemState state = GemState::IDLE;
    sf::Vector2f targetPosition;
    float animationTime = 0.f;
    float startAlpha = 255.f;
    
    void updateColor();
    void initializeBonus();
}; 