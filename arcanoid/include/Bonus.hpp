#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"

/**
 * @brief Абстрактный бонус, падающий вниз после разрушения блока
 */
class Bonus : public GameObject {
public:
    /**
     * @brief Конструктор базового бонуса
     * @param pos Начальная позиция верхнего левого угла бонуса
     */
    Bonus(const sf::Vector2f& pos)
        : GameObject(pos, sf::Vector2f(20.f, 20.f)),
          fallSpeed(200.f), active(true)
    {
        shape = new sf::CircleShape(20.f);
        shape->setPosition(pos);
    }

    /**
     * @brief Обновляет положение бонуса
     * @param deltaTime Время с последнего кадра в секундах
     */
    void update(float deltaTime) override {
        if (!active) return;
        position.y += fallSpeed * deltaTime;
        shape->setPosition(position);
    }

    /**
     * @brief Рисует бонус, если он активен
     * @param window Окно для отрисовки
     */
    void draw(sf::RenderWindow& window) override {
        if (active) window.draw(*shape);
    }

    /**
     * @brief Применяет эффект бонуса к ракетке или мячу
     * @param paddle Ссылка на объект ракетки
     * @param ball Ссылка на объект мяча
     */
    virtual void applyEffect(Paddle& paddle, Ball& ball) = 0;

    /**
     * @brief Проверяет, активен ли бонус
     * @return true, если бонус еще не был подобран или деактивирован
     */
    bool isActive() const { return active; }

    /**
     * @brief Деактивирует бонус после применения
     */
    void deactivate() { active = false; }

    /**
     * @brief Получает границы бонуса для коллизии
     * @return Прямоугольник границ
     */
    sf::FloatRect getBounds() const { return shape->getGlobalBounds(); }

    /**
     * @brief Виртуальный деструктор
     */
    virtual ~Bonus() { delete shape; }

protected:
    float fallSpeed;            /**< Скорость падения бонуса */
    bool active;                /**< Флаг активности бонуса */
    sf::CircleShape* shape;     /**< Графическое представление бонуса */
};

/**
 * @brief Бонус изменения размера ракетки
 */
class PaddleSizeBonus : public Bonus {
public:
    /**
     * @brief Конструктор бонуса размера ракетки
     * @param pos Позиция бонуса
     * @param increase true — увеличить размер, false — уменьшить
     */
    PaddleSizeBonus(const sf::Vector2f& pos, bool increase)
        : Bonus(pos), sizeMultiplier(increase ? 1.2f : 0.8f)
    {
        shape->setFillColor(increase ? sf::Color::Green : sf::Color::Red);
    }

    /**
     * @brief Применяет изменение размера к ракетке
     * @param paddle Ссылка на объект ракетки
     * @param ball Игнорируется
     */
    void applyEffect(Paddle& paddle, Ball& ball) override {
        paddle.resize(sizeMultiplier);
    }

private:
    float sizeMultiplier;       /**< Множитель размера ракетки */
};

/**
 * @brief Бонус изменения скорости мяча
 */
class BallSpeedBonus : public Bonus {
public:
    /**
     * @brief Конструктор бонуса скорости мяча
     * @param pos Позиция бонуса
     * @param increase true — увеличить скорость, false — уменьшить
     */
    BallSpeedBonus(const sf::Vector2f& pos, bool increase)
        : Bonus(pos), speedMultiplier(increase ? 1.2f : 0.8f)
    {
        shape->setFillColor(increase ? sf::Color::Yellow : sf::Color::Blue);
    }

    /**
     * @brief Применяет изменение скорости мяча
     * @param paddle Игнорируется
     * @param ball Ссылка на объект мяча
     */
    void applyEffect(Paddle& paddle, Ball& ball) override {
        ball.setSpeed(ball.getSpeed() * speedMultiplier);
    }

private:
    float speedMultiplier;      /**< Множитель скорости мяча */
};

/**
 * @brief Бонус прилипания мяча к ракетке
 */
class StickyBallBonus : public Bonus {
public:
    /**
     * @brief Конструктор бонуса прилипания
     * @param pos Позиция бонуса
     */
    StickyBallBonus(const sf::Vector2f& pos) : Bonus(pos) {
        shape->setFillColor(sf::Color::Magenta);
    }

    /**
     * @brief Активирует прилипание мяча
     * @param paddle Игнорируется
     * @param ball Ссылка на объект мяча
     */
    void applyEffect(Paddle& paddle, Ball& ball) override {
        ball.setSticky(true);
    }
};

/**
 * @brief Бонус установки нижней ракетки
 */
class BottomPaddleBonus : public Bonus {
public:
    /**
     * @brief Конструктор бонуса нижней ракетки
     * @param pos Позиция бонуса
     */
    BottomPaddleBonus(const sf::Vector2f& pos) : Bonus(pos) {
        shape->setFillColor(sf::Color::Cyan);
    }

    /**
     * @brief Включает нижнюю ракетку
     * @param paddle Ссылка на объект ракетки
     * @param ball Игнорируется
     */
    void applyEffect(Paddle& paddle, Ball& ball) override {
        paddle.setBottom(true);
    }
};

/**
 * @brief Бонус случайной траектории мяча
 */
class RandomTrajectoryBonus : public Bonus {
public:
    /**
     * @brief Конструктор бонуса случайной траектории
     * @param pos Позиция бонуса
     */
    RandomTrajectoryBonus(const sf::Vector2f& pos) : Bonus(pos) {
        shape->setFillColor(sf::Color::White);
    }

    /**
     * @brief Устанавливает случайное направление мяча
     * @param paddle Игнорируется
     * @param ball Ссылка на объект мяча
     */
    void applyEffect(Paddle& paddle, Ball& ball) override {
        float angle = static_cast<float>(rand() % 360) * 3.14159f / 180.f;
        ball.reflect({std::cos(angle), std::sin(angle)});
    }
};
