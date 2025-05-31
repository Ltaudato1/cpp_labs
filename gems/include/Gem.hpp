#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Bonus.hpp"

/**
 * @enum GemType
 * @brief Типы гемов
 */
enum class GemType {
    RED,    ///< Красный гем
    BLUE,   ///< Синий гем
    GREEN,  ///< Зеленый гем
    YELLOW, ///< Желтый гем
    PURPLE  ///< Фиолетовый гем
};

/**
 * @enum GemState
 * @brief Состояния гема для анимации
 */
enum class GemState {
    IDLE,        ///< Обычное состояние
    FALLING,     ///< Падение
    DISAPPEARING,///< Исчезновение
    APPEARING    ///< Появление
};

/**
 * @class Gem
 * @brief Класс гема
 * 
 * Класс представляет собой гем на игровом поле.
 * Отвечает за отрисовку, анимацию и бонусы гема.
 */
class Gem {
public:
    /**
     * @brief Конструктор гема
     * @param type Тип гема
     * @param position Позиция на поле
     * @param grid Указатель на игровое поле
     */
    Gem(GemType type, const sf::Vector2i& position, class Grid* grid);
    
    /**
     * @brief Обновляет состояние гема
     * @param deltaTime Время с последнего обновления
     */
    void update(float deltaTime);
    
    /**
     * @brief Отрисовывает гем
     * @param window Окно для отрисовки
     */
    void draw(sf::RenderWindow& window);
    
    /**
     * @brief Получает тип гема
     * @return Тип гема
     */
    GemType getType() const { return type; }
    
    /**
     * @brief Устанавливает тип гема
     * @param newType Новый тип гема
     */
    void setType(GemType newType);
    
    /**
     * @brief Получает позицию гема
     * @return Позиция гема
     */
    sf::Vector2i getPosition() const { return position; }
    
    /**
     * @brief Устанавливает позицию гема
     * @param newPosition Новая позиция
     */
    void setPosition(const sf::Vector2i& newPosition);
    
    /**
     * @brief Проверяет, есть ли у гема бонус
     * @return true если есть бонус, false иначе
     */
    bool hasBonus() const { return bonus != nullptr; }
    
    /**
     * @brief Активирует бонус гема
     */
    void activateBonus();
    
    /**
     * @brief Проверяет, анимируется ли гем
     * @return true если гем анимируется, false иначе
     */
    bool isAnimating() const { return state != GemState::IDLE; }
    
    /**
     * @brief Запускает анимацию падения
     */
    void startFalling();
    
    /**
     * @brief Запускает анимацию исчезновения
     */
    void startDisappearing();
    
    /**
     * @brief Запускает анимацию появления
     */
    void startAppearing();

private:
    /**
     * @brief Обновляет цвет гема
     */
    void updateColor();
    
    /**
     * @brief Инициализирует бонус
     */
    void initializeBonus();

    GemType type;                    ///< Тип гема
    sf::Vector2i position;           ///< Позиция на поле
    sf::RectangleShape shape;        ///< Форма гема
    std::unique_ptr<Bonus> bonus;    ///< Бонус гема
    Grid* grid;                      ///< Указатель на игровое поле
    GemState state;                  ///< Текущее состояние
    float animationTime;             ///< Время анимации
    sf::Vector2f startPosition;      ///< Начальная позиция для анимации
    sf::Vector2f targetPosition;     ///< Целевая позиция для анимации
    float startAlpha;                ///< Начальная прозрачность
    float targetAlpha;               ///< Целевая прозрачность

    static constexpr float FALL_SPEED = 500.0f;      ///< Скорость падения
    static constexpr float ANIMATION_TIME = 0.3f;    ///< Длительность анимации
    static constexpr float BONUS_CHANCE = 0.1f;      ///< Шанс появления бонуса
}; 