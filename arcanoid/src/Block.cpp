#include "../include/Block.hpp"
#include "../include/Bonus.hpp"

Block::Block(const sf::Vector2f& pos, const sf::Vector2f& size, int initialHealth, bool isDestructible, bool bonus, float speedMultiplier)
        : GameObject(pos, size)
        , health(initialHealth)
        , destructible(isDestructible)
        , hasBonus(bonus)
        , speedMult(speedMultiplier) {
        
    shape = new sf::RectangleShape(size);
    shape->setPosition(pos);
    
    
    std::random_device rd;
    rng.seed(rd());
}

void Block::draw(sf::RenderWindow& window) {
    if (isAlive()) {
        if (!destructible) {
            shape->setFillColor(sf::Color::Red);
        } else {
            switch(health) {
                case 1:
                    shape->setFillColor(sf::Color::Green);
                    break;
                case 2:
                    shape->setFillColor(sf::Color::Cyan);
                    break;
                case 3:
                    shape->setFillColor(sf::Color::Blue);
                    break;
                case 4:
                    shape->setFillColor(sf::Color::Yellow);
                    break;
                default:
                    break;
            }
        }

        window.draw(*shape);
    }
}

Bonus* Block::createBonus() {
        if (!hasBonus) return nullptr;

        std::uniform_int_distribution<int> dist(0, 6);
        int bonusType = dist(rng);
        
        switch (bonusType) {
            case 0:
                return new PaddleSizeBonus(position, true);
            case 1:
                return new PaddleSizeBonus(position, false);
            case 2:
                return new BallSpeedBonus(position, true);
            case 3:
                return new BallSpeedBonus(position, false);
            case 4:
                return new StickyBallBonus(position);
            case 5:
                return new BottomPaddleBonus(position);
            case 6:
                return new RandomTrajectoryBonus(position);
            default:
                return nullptr;
        }
}