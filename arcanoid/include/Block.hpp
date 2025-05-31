#pragma once
#include "GameObject.hpp"
#include "Bonus.hpp"
#include <random>
#include <SFML/Graphics.hpp>

/**
 * @brief Класс блока в игре Arkanoid
 * 
 * Представляет прямоугольный блок, который может быть
 * разрушаемым или неразрушаемым, может содержать бонус.
 */
class Block : public GameObject {
public:
    /**
     * @brief Конструктор блока
     * @param pos Позиция верхнего левого угла блока
     * @param size Размер блока (ширина и высота)
     * @param initialHealth Начальное число жизней (прочности)
     * @param isDestructible Флаг, указывающий, разрушаемый ли блок
     * @param bonus Флаг наличия бонуса при разрушении
     * @param speedMultiplier Множитель скорости мяча при отражении
     */
    Block(const sf::Vector2f& pos,
          const sf::Vector2f& size,
          int initialHealth,
          bool isDestructible,
          bool bonus,
          float speedMultiplier);

    /**
     * @brief Уменьшает прочность блока при попадании
     * @return true, если блок был разрушаемым (прочность уменьшена)
     */
    bool onHit() {
        if (destructible) {
            --health;
            return true;
        }
        return false;
    }

    /**
     * @brief Проверяет, остался ли блок "живым"
     * @return true, если блок неразрушаемый или здоровье > 0
     */
    bool isAlive() const {
        return !destructible || health > 0;
    }

    /**
     * @brief Проверяет, содержит ли блок бонус
     * @return true, если при разрушении должен падать бонус
     */
    bool hasBonusBlock() const {
        return hasBonus;
    }

    /**
     * @brief Возвращает множитель скорости мяча при отражении от блока
     * @return Множитель скорости
     */
    float getSpeedMultiplier() const {
        return speedMult;
    }

    /**
     * @brief Возвращает текущее здоровье блока
     * @return Количество очков прочности
     */
    int getHealth() const {
        return health;
    }

    /**
     * @brief Создает объект бонуса при разрушении блока
     * @return Указатель на новый объект Bonus
     */
    Bonus* createBonus();

    /**
     * @brief Рисует блок на заданном окне
     * @param window Окно SFML для отрисовки
     */
    void draw(sf::RenderWindow& window) override;

    /**
     * @brief Возвращает глобальные границы блока для коллизии
     * @return Прямоугольник границ
     */
    sf::FloatRect getBounds() const {
        return shape->getGlobalBounds();
    }

    /**
     * @brief Деструктор освобождает форму блока
     */
    ~Block() {
        delete shape;
    }

private:
    int health;                 /**< Прочность блока */
    bool destructible;          /**< Флаг разрушаемости */
    bool hasBonus;              /**< Флаг наличия бонуса */
    float speedMult;            /**< Множитель скорости мяча */
    sf::RectangleShape* shape;  /**< Графическое представление блока */
    std::mt19937 rng;           /**< Генератор случайных чисел для бонусов */
};
