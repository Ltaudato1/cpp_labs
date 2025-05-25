#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"

class Bonus : public GameObject {
protected:
    float fallSpeed;
    bool active;
    sf::CircleShape* shape;

public:
    Bonus(const sf::Vector2f& pos)
        : GameObject(pos, sf::Vector2f(20, 20))
        , fallSpeed(200.0f)
        , active(true) {
        
        shape = new sf::CircleShape(20);
        shape->setPosition(pos);
    }

    virtual void update(float deltaTime) override {
        if (active) {
            position.y += fallSpeed * deltaTime;
            shape->setPosition(position);
        }
    }

    virtual void draw(sf::RenderWindow& window) override {
        if (active) {
            window.draw(*shape);
        }
    }

    virtual void applyEffect(Paddle& paddle, Ball& ball) = 0;

    bool isActive() const { return active; }
    void deactivate() { active = false; }

    sf::FloatRect getBounds() const {
        return shape->getGlobalBounds();
    }

    virtual ~Bonus() {
        delete shape;
    }
};

class PaddleSizeBonus : public Bonus {
public:
    PaddleSizeBonus(const sf::Vector2f& pos, bool increase)
        : Bonus(pos) {
        shape->setFillColor(increase ? sf::Color::Green : sf::Color::Red);
        sizeMultiplier = increase ? 1.2f : 0.8f;
    }

    void applyEffect(Paddle& paddle, Ball& ball) override {
        paddle.resize(sizeMultiplier);
    }

private:
    float sizeMultiplier;
};

class BallSpeedBonus : public Bonus {
public:
    BallSpeedBonus(const sf::Vector2f& pos, bool increase)
        : Bonus(pos) {
        shape->setFillColor(increase ? sf::Color::Yellow : sf::Color::Blue);
        speedMultiplier = increase ? 1.2f : 0.8f;
    }

    void applyEffect(Paddle& paddle, Ball& ball) override {
        ball.setSpeed(ball.getSpeed() * speedMultiplier);
    }

private:
    float speedMultiplier;
};

class StickyBallBonus : public Bonus {
public:
    StickyBallBonus(const sf::Vector2f& pos)
        : Bonus(pos) {
        shape->setFillColor(sf::Color::Magenta);
    }

    void applyEffect(Paddle& paddle, Ball& ball) override {
        ball.setSticky(true);
    }
};

class BottomPaddleBonus : public Bonus {
public:
    BottomPaddleBonus(const sf::Vector2f& pos)
        : Bonus(pos) {
        shape->setFillColor(sf::Color::Cyan);
    }

    void applyEffect(Paddle& paddle, Ball& ball) override {
        paddle.setBottom(true);
    }
};

class RandomTrajectoryBonus : public Bonus {
public:
    RandomTrajectoryBonus(const sf::Vector2f& pos)
        : Bonus(pos) {
        shape->setFillColor(sf::Color::White);
    }

    void applyEffect(Paddle& paddle, Ball& ball) override {
        float angle = (rand() % 360) * 3.14159f / 180.0f;
        ball.reflect(sf::Vector2f(std::cos(angle), std::sin(angle)));
    }
}; 