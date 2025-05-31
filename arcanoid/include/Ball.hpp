#pragma once
#include "GameObject.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

/**
 * @brief Класс мяча для игры Arkanoid
 * 
 * Представляет игровой объект — мяч, который отражается от стен,
 * ракетки и блоков, обладает скоростью, радиусом и состоянием "прилипшего".
 */
class Ball : public GameObject {
public:
    /**
     * @brief Конструктор мяча
     * @param position Начальная позиция центра мяча
     * @param radius Радиус мяча в пикселях
     * @param speed Начальная скорость мяча
     */
    Ball(const sf::Vector2f& position, float radius, float speed)
        : GameObject(position, sf::Vector2f(radius * 2, radius * 2)),
          radius(radius), speed(speed), sticky(true), prevPosition(position)
    {
        shape = new sf::CircleShape(radius);
        shape->setFillColor(sf::Color::White);
        shape->setPosition(position);
    }

    /**
     * @brief Обновляет состояние мяча
     * @param deltaTime Время, прошедшее с последнего кадра (секунды)
     */
    void update(float deltaTime) override;

    /**
     * @brief Рисует мяч на экране
     * @param window Окно SFML для отрисовки
     */
    void draw(sf::RenderWindow& window) override {
        window.draw(*shape);
    }

    /**
     * @brief Запускает мяч в заданном направлении
     * @param direction Нормализованный вектор направления
     */
    void launch(const sf::Vector2f& direction);

    /**
     * @brief Отражает вектор скорости мяча относительно нормали
     * @param normal Нормализованный вектор нормали поверхности столкновения
     */
    void reflect(const sf::Vector2f& normal);

    /**
     * @brief Проверяет, "прилип" ли мяч к ракетке
     * @return true, если мяч ещё не запущен
     */
    bool isBallSticky() const { return sticky; }

    /**
     * @brief Устанавливает состояние "прилипания" мяча
     * @param value true — мяч "прилипает" к ракетке
     */
    void setSticky(bool value) { sticky = value; }

    /**
     * @brief Устанавливает новую позицию мяча
     * @param pos Новая позиция центра мяча
     */
    void setPosition(const sf::Vector2f& pos) override {
        position = pos;
        shape->setPosition(pos);
    }

    /**
     * @brief Получает границы мяча для проверки коллизий
     * @return Прямоугольник, описывающий область мяча
     */
    sf::FloatRect getBounds() const {
        return sf::FloatRect(
            position.x - radius,
            position.y - radius,
            radius * 2,
            radius * 2
        );
    }

    /**
     * @brief Возвращает текущую скорость мяча
     * @return Скорость в пикселях в секунду
     */
    float getSpeed() const { return speed; }

    /**
     * @brief Устанавливает скорость мяча
     * @param speed Новая скорость в пикселях в секунду
     */
    void setSpeed(float speed) { this->speed = speed; }

    /**
     * @brief Возвращает радиус мяча
     * @return Радиус в пикселях
     */
    float getRadius() const { return radius; }

    /**
     * @brief Возвращает предыдущую позицию центра мяча
     * @return Вектор предыдущей позиции
     */
    const sf::Vector2f& getPrevPosition() const { return prevPosition; }

private:
    float radius;                  /**< Радиус мяча */
    float speed;                   /**< Скорость мяча */
    bool sticky;                   /**< Флаг "прилипания" */
    sf::CircleShape* shape;        /**< Графическое представление мяча */
    sf::Vector2f velocity;         /**< Текущий вектор скорости */
    sf::Vector2f prevPosition;     /**< Позиция мяча в предыдущем кадре */
};
