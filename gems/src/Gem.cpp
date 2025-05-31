#include "Gem.hpp"
#include "Grid.hpp"
#include <random>

// Генератор случайных чисел
static std::random_device rd;
static std::mt19937 gen(rd());

/**
 * @brief Конструктор гема
 * @param type Тип гема
 * @param position Позиция на поле
 * @param grid Указатель на игровое поле
 */
Gem::Gem(GemType type, const sf::Vector2i& position, Grid* grid)
    : type(type), position(position), grid(grid), state(GemState::APPEARING) {
    shape.setSize(sf::Vector2f(SIZE, SIZE));
    updateColor();
    startAppearing();
    initializeBonus();
}

/**
 * @brief Обновляет состояние гема
 * @param deltaTime Время с последнего обновления
 */
void Gem::update(float deltaTime) {
    switch (state) {
        case GemState::FALLING: {
            animationTime += deltaTime;
            float progress = std::min(animationTime / ANIMATION_TIME, 1.0f);
            
            // Обновляем позицию
            sf::Vector2f currentPos = startPosition + (targetPosition - startPosition) * progress;
            shape.setPosition(currentPos);
            
            if (progress >= 1.0f) {
                state = GemState::IDLE;
            }
            break;
        }
        case GemState::DISAPPEARING: {
            animationTime += deltaTime;
            float progress = std::min(animationTime / ANIMATION_TIME, 1.0f);
            
            // Обновляем прозрачность
            float currentAlpha = startAlpha + (targetAlpha - startAlpha) * progress;
            sf::Color color = shape.getFillColor();
            color.a = static_cast<sf::Uint8>(currentAlpha);
            shape.setFillColor(color);
            
            if (progress >= 1.0f) {
                state = GemState::IDLE;
            }
            break;
        }
        case GemState::APPEARING: {
            animationTime += deltaTime;
            float progress = std::min(animationTime / ANIMATION_TIME, 1.0f);
            
            // Обновляем прозрачность
            float currentAlpha = startAlpha + (targetAlpha - startAlpha) * progress;
            sf::Color color = shape.getFillColor();
            color.a = static_cast<sf::Uint8>(currentAlpha);
            shape.setFillColor(color);
            
            if (progress >= 1.0f) {
                state = GemState::IDLE;
            }
            break;
        }
        default:
            break;
    }
}

/**
 * @brief Отрисовывает гем
 * @param window Окно для отрисовки
 */
void Gem::draw(sf::RenderWindow& window) {
    window.draw(shape);
    
    if (bonus) {
        sf::Vector2f bonusPos = shape.getPosition();
        bonusPos.x += SIZE / 2;
        bonusPos.y += SIZE / 2;
        bonus->draw(window, bonusPos);
    }
}

/**
 * @brief Устанавливает тип гема
 * @param newType Новый тип гема
 */
void Gem::setType(GemType newType) {
    type = newType;
    updateColor();
}

/**
 * @brief Устанавливает позицию гема
 * @param newPosition Новая позиция
 */
void Gem::setPosition(const sf::Vector2i& newPosition) {
    position = newPosition;
    shape.setPosition(
        position.x * (SIZE + PADDING) + PADDING,
        position.y * (SIZE + PADDING) + PADDING
    );
}

/**
 * @brief Активирует бонус гема
 */
void Gem::activateBonus() {
    if (bonus) {
        // Выбираем случайную позицию в радиусе 3
        std::uniform_int_distribution<> dist(-3, 3);
        int offsetX, offsetY;
        do {
            offsetX = dist(gen);
            offsetY = dist(gen);
        } while (offsetX == 0 && offsetY == 0);
        
        sf::Vector2i targetPos = position;
        targetPos.x += offsetX;
        targetPos.y += offsetY;
        
        if (grid->isValidPosition(targetPos)) {
            if (auto* targetGem = grid->getGemAt(targetPos)) {
                bonus->activate(*targetGem);
            }
        }
    }
}

/**
 * @brief Запускает анимацию падения
 */
void Gem::startFalling() {
    state = GemState::FALLING;
    animationTime = 0.0f;
    startPosition = shape.getPosition();
    targetPosition = sf::Vector2f(
        position.x * (SIZE + PADDING) + PADDING,
        position.y * (SIZE + PADDING) + PADDING
    );
}

/**
 * @brief Запускает анимацию исчезновения
 */
void Gem::startDisappearing() {
    state = GemState::DISAPPEARING;
    animationTime = 0.0f;
    startAlpha = 255.0f;
    targetAlpha = 0.0f;
}

/**
 * @brief Запускает анимацию появления
 */
void Gem::startAppearing() {
    state = GemState::APPEARING;
    animationTime = 0.0f;
    startAlpha = 0.0f;
    targetAlpha = 255.0f;
}

/**
 * @brief Обновляет цвет гема
 */
void Gem::updateColor() {
    sf::Color color;
    switch (type) {
        case GemType::RED:
            color = sf::Color::Red;
            break;
        case GemType::BLUE:
            color = sf::Color::Blue;
            break;
        case GemType::GREEN:
            color = sf::Color::Green;
            break;
        case GemType::YELLOW:
            color = sf::Color::Yellow;
            break;
        case GemType::PURPLE:
            color = sf::Color(128, 0, 128);  // Purple
            break;
    }
    shape.setFillColor(color);
}

/**
 * @brief Инициализирует бонус
 */
void Gem::initializeBonus() {
    std::uniform_real_distribution<> dist(0.0, 1.0);
    if (dist(gen) < BONUS_CHANCE) {
        std::uniform_int_distribution<> bonusDist(0, 1);
        if (bonusDist(gen) == 0) {
            bonus = std::make_unique<ColorChangeBonus>(grid);
        } else {
            bonus = std::make_unique<BombBonus>(grid);
        }
    }
} 