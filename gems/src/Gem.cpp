#include "Gem.hpp"
#include <random>

Gem::Gem(GemType type, const sf::Vector2f& position) 
    : type(type) {
    shape.setSize(sf::Vector2f(SIZE, SIZE));
    shape.setPosition(position);
    updateColor();
    initializeBonus();
    startAppearing();  // Начинаем с анимации появления
}

void Gem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);
    if (bonus) {
        bonus->draw(target, states);
    }
}

void Gem::setPosition(const sf::Vector2f& newPosition) {
    shape.setPosition(newPosition);
}

void Gem::setType(GemType newType) {
    type = newType;
    updateColor();
}

GemType Gem::getType() const {
    return type;
}

bool Gem::hasBonus() const {
    return bonus != nullptr;
}

void Gem::setBonus(std::unique_ptr<Bonus> newBonus) {
    bonus = std::move(newBonus);
}

void Gem::activateBonus(Gem& target, Grid& grid) {
    if (bonus) {
        bonus->activate(target, grid);
    }
}

void Gem::update(float deltaTime) {
    switch (state) {
        case GemState::FALLING: {
            sf::Vector2f currentPos = shape.getPosition();
            sf::Vector2f direction = targetPosition - currentPos;
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            
            if (distance < FALL_SPEED * deltaTime) {
                shape.setPosition(targetPosition);
                state = GemState::IDLE;
            } else {
                direction /= distance;  // Нормализуем вектор
                shape.move(direction * FALL_SPEED * deltaTime);
            }
            break;
        }
        case GemState::DISAPPEARING: {
            animationTime += deltaTime;
            float progress = animationTime / DISAPPEAR_TIME;
            if (progress >= 1.f) {
                state = GemState::IDLE;
                sf::Color color = shape.getFillColor();
                color.a = 0;
                shape.setFillColor(color);
            } else {
                sf::Color color = shape.getFillColor();
                color.a = static_cast<sf::Uint8>(startAlpha * (1.f - progress));
                shape.setFillColor(color);
            }
            break;
        }
        case GemState::APPEARING: {
            animationTime += deltaTime;
            float progress = animationTime / APPEAR_TIME;
            if (progress >= 1.f) {
                state = GemState::IDLE;
                sf::Color color = shape.getFillColor();
                color.a = 255;
                shape.setFillColor(color);
            } else {
                sf::Color color = shape.getFillColor();
                color.a = static_cast<sf::Uint8>(255 * progress);
                shape.setFillColor(color);
            }
            break;
        }
        default:
            break;
    }
}

void Gem::startFalling(const sf::Vector2f& targetPos) {
    state = GemState::FALLING;
    targetPosition = targetPos;
}

void Gem::startDisappearing() {
    state = GemState::DISAPPEARING;
    animationTime = 0.f;
    startAlpha = shape.getFillColor().a;
}

void Gem::startAppearing() {
    state = GemState::APPEARING;
    animationTime = 0.f;
    sf::Color color = shape.getFillColor();
    color.a = 0;
    shape.setFillColor(color);
}

void Gem::updateColor() {
    switch (type) {
        case GemType::RED:
            shape.setFillColor(sf::Color(255, 0, 0, 255));
            break;
        case GemType::BLUE:
            shape.setFillColor(sf::Color(0, 0, 255, 255));
            break;
        case GemType::GREEN:
            shape.setFillColor(sf::Color(0, 255, 0, 255));
            break;
        case GemType::YELLOW:
            shape.setFillColor(sf::Color(255, 255, 0, 255));
            break;
        case GemType::PURPLE:
            shape.setFillColor(sf::Color(128, 0, 128, 255));
            break;
        case GemType::ORANGE:
            shape.setFillColor(sf::Color(255, 165, 0, 255));
            break;
    }
}

void Gem::initializeBonus() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    
    if (dis(gen) < BONUS_CHANCE) {
        if (dis(gen) < 0.5) {
            bonus = std::make_unique<ColorChangeBonus>(type);
        } else {
            bonus = std::make_unique<BombBonus>();
        }
    }
} 