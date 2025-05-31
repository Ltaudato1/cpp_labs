#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

enum class GemType;
class Gem;
class Grid;

/**
 * @class Bonus
 * @brief Базовый класс для бонусов
 * 
 * Абстрактный класс, определяющий интерфейс для всех типов бонусов.
 * Каждый бонус должен реализовать методы активации и отрисовки.
 */
class Bonus {
public:
    /**
     * @brief Конструктор бонуса
     * @param grid Указатель на игровое поле
     */
    Bonus(Grid* grid) : grid(grid) {}
    
    /**
     * @brief Виртуальный деструктор
     */
    virtual ~Bonus() = default;
    
    /**
     * @brief Активирует бонус
     * @param target Гем, на котором активируется бонус
     */
    virtual void activate(Gem& target) = 0;
    
    /**
     * @brief Отрисовывает бонус
     * @param window Окно для отрисовки
     * @param position Позиция для отрисовки
     */
    virtual void draw(sf::RenderWindow& window, const sf::Vector2f& position) = 0;
    
    /**
     * @brief Получает форму бонуса
     * @return Форма бонуса
     */
    virtual const sf::Shape& getShape() const = 0;

protected:
    Grid* grid;  ///< Указатель на игровое поле
};

/**
 * @class ColorChangeBonus
 * @brief Бонус изменения цвета
 * 
 * Бонус, который меняет цвет целевого гема и двух случайных
 * не соседних гемов в радиусе 3 от него.
 */
class ColorChangeBonus : public Bonus {
public:
    /**
     * @brief Конструктор бонуса изменения цвета
     * @param grid Указатель на игровое поле
     */
    ColorChangeBonus(Grid* grid);
    
    /**
     * @brief Активирует бонус изменения цвета
     * @param target Гем, на котором активируется бонус
     */
    void activate(Gem& target) override;
    
    /**
     * @brief Отрисовывает бонус изменения цвета
     * @param window Окно для отрисовки
     * @param position Позиция для отрисовки
     */
    void draw(sf::RenderWindow& window, const sf::Vector2f& position) override;
    
    /**
     * @brief Получает форму бонуса
     * @return Форма бонуса
     */
    const sf::Shape& getShape() const override { return shape; }

private:
    sf::CircleShape shape;  ///< Форма бонуса
};

/**
 * @class BombBonus
 * @brief Бонус-бомба
 * 
 * Бонус, который удаляет 5 случайных гемов с поля.
 */
class BombBonus : public Bonus {
public:
    /**
     * @brief Конструктор бонуса-бомбы
     * @param grid Указатель на игровое поле
     */
    BombBonus(Grid* grid);
    
    /**
     * @brief Активирует бонус-бомбу
     * @param target Гем, на котором активируется бонус
     */
    void activate(Gem& target) override;
    
    /**
     * @brief Отрисовывает бонус-бомбу
     * @param window Окно для отрисовки
     * @param position Позиция для отрисовки
     */
    void draw(sf::RenderWindow& window, const sf::Vector2f& position) override;
    
    /**
     * @brief Получает форму бонуса
     * @return Форма бонуса
     */
    const sf::Shape& getShape() const override { return shape; }

private:
    sf::RectangleShape shape;  ///< Форма бонуса
}; 