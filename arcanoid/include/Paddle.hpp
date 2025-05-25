#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "Ball.hpp"

/**
 * @brief Класс ракетки игрока в Arkanoid
 *
 * Отвечает за перемещение по горизонтали, изменение размера,
 * а также опциональное отображение дополнительной нижней ракетки.
 */
class Paddle : public GameObject {
public:
    /**
     * @brief Конструктор ракетки
     * @param pos Начальная позиция верхнего левого угла
     * @param size Начальный размер ракетки (ширина, высота)
     * @param speed Скорость перемещения в пикселях/сек
     * @param bottom Флаг отображения второй (нижней) ракетки
     */
    Paddle(const sf::Vector2f& pos,
           const sf::Vector2f& size,
           float speed,
           bool bottom);

    /**
     * @brief Обновляет графическое положение ракетки
     * @param deltaTime Интервал времени с последнего кадра (секунды)
     */
    void update(float deltaTime) override;

    /**
     * @brief Перемещает ракетку по горизонтали
     * @param direction Направление: -1 для влево, +1 для вправо
     */
    void move(float direction);

    /**
     * @brief Отрисовывает ракетку(и нижнюю, если активирована)
     * @param window Окно SFML для отрисовки
     */
    void draw(sf::RenderWindow& window) override;

    /**
     * @brief Устанавливает новую позицию ракетки
     * @param pos Позиция верхнего левого угла
     */
    void setPosition(const sf::Vector2f& pos) override;

    /**
     * @brief Меняет размер ракетки
     * @param factor Множитель размера (1.0 - без изменений)
     */
    void resize(float factor);

    /**
     * @brief Получает скорость перемещения ракетки
     * @return Скорость в пикселях/сек
     */
    float getMoveSpeed() const;

    /**
     * @brief Устанавливает скорость перемещения ракетки
     * @param speed Новая скорость в пикселях/сек
     */
    void setMoveSpeed(float speed);

    /**
     * @brief Проверяет, активна ли нижняя ракетка
     * @return true, если нижняя ракетка отображается
     */
    bool isBottomPaddle() const;

    /**
     * @brief Включает или выключает нижнюю ракетку
     * @param bottom true — включить нижнюю ракетку
     */
    void setBottom(bool bottom);

    /**
     * @brief Возвращает область ракетки для коллизий
     * @return Прямоугольник границ
     */
    sf::FloatRect getBounds() const;

private:
    float moveSpeed;                /**< Скорость движения */
    float minWidth;                 /**< Минимальная ширина ракетки */
    float maxWidth;                 /**< Максимальная ширина ракетки */
    bool  isBottom;                 /**< Флаг отображения нижней ракетки */
    sf::RectangleShape* shape;      /**< Форма основной ракетки */
    sf::RectangleShape* bottomShape;/**< Форма нижней ракетки */
};