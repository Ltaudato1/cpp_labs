#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/GameObject.hpp"
#include "../include/Ball.hpp"
#include "../include/Paddle.hpp"
#include "../include/Block.hpp"
#include "../include/Bonus.hpp"
#include "../include/Game.hpp"
#include <vector>
#include <memory>
#include <string>
#include <cmath>
#include <random>

Game::Game()
: window(
    sf::VideoMode(800, 600),
    "Arkanoid"
)
, paddle(
    sf::Vector2f(350, 550),
    sf::Vector2f(100, 20),
    20.0f,
    false
)
, ball(
    sf::Vector2f(
      paddle.getPosition().x + paddle.getSize().x / 2,
      paddle.getPosition().y - 10
    ),
    10.0f,
    300.0f
) {
    // Игровые параметры
    score = 0;
    lives = 3;

    // Вывод очков
    scoreText.setFont(manager.getFont());
    scoreText.setCharacterSize(24);      
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.0f, 10.0f);     

    // Отрисовка жизней
    heartSprite.setTexture(manager.getHeartTexture());
    heartSprite.setScale(0.05f, 0.05f);

    // Окно
    window.setFramerateLimit(60);

    // Блоки
    const float windowWidth = 800.0f;
    const float blockWidth = 80.0f;
    const float blockHeight = 30.0f;
    const float blockSpacing = 10.0f;
    const int blocksPerRow = 8;
    const int rows = 5;
    
    // Вычисляем начальную позицию для центрирования блоков
    float totalWidth = blocksPerRow * (blockWidth + blockSpacing) - blockSpacing;
    float startX = (windowWidth - totalWidth) / 2;
    
    for (int i = 0; i < blocksPerRow; ++i) {
        for (int j = 0; j < rows; ++j) {
            // Создаем разные типы блоков
            bool isDestructible = (j > 0);
            bool hasBonus = (j > 1 && j < 4);
            float speedMult = (j == 4) ? 2.5f : 1.0f;
            
            blocks.emplace_back(std::make_unique<Block>(
                sf::Vector2f(startX + i * (blockWidth + blockSpacing), 50 + j * (blockHeight + blockSpacing)),
                sf::Vector2f(blockWidth, blockHeight),
                5 - j,
                isDestructible,
                hasBonus,
                speedMult
            ));
        }
    }
}

void Game::redrawAll() {
        window.clear(sf::Color::Black);
        
        // Отрисовка блоков
        for (auto& block : blocks) {
            if (block->isAlive()) {
                block->draw(window);
            }
        }
        
        // Отрисовка бонусов
        for (auto& bonus : activeBonuses) {
            if (bonus->isActive()) {
                bonus->draw(window);
            }
        }
        
        // Отрисовка каретки и мяча
        paddle.draw(window);
        ball.draw(window);

        // Отрисовка очков
        scoreText.setString("score: " + std::to_string(score));
        window.draw(scoreText);

        // Отрисовка жизней
        sf::Vector2f posStart(760.0f, 10.0f);
        for (int i = 0; i < lives; ++i)
        {
            heartSprite.setPosition(
                posStart.x - i * manager.getHeartTextureSize().x * heartSprite.getScale().x,
                posStart.y
            );
            window.draw(heartSprite);
        }
        
        window.display();
}

void Game::update(float deltaTime) {
    paddle.update(deltaTime);
    ball.update(deltaTime);
    if (ball.isBallSticky()) {
        ball.setPosition(sf::Vector2f(
            paddle.getPosition().x + paddle.getSize().x / 2,
            paddle.getPosition().y - ball.getSize().y / 2
        ));
    }

    // Обновление бонусов
    for (auto& bonus : activeBonuses) {
        if (bonus->isActive()) {
            bonus->update(deltaTime);
            
            // Проверка столкновения бонуса с кареткой
            if (bonus->getBounds().intersects(paddle.getBounds())) {
                bonus->applyEffect(paddle, ball);
                bonus->deactivate();
            }
            
            // Удаление бонусов, упавших за пределы экрана
            if (bonus->getPosition().y > 600) {
                bonus->deactivate();
            }
        }
    }
}

void Game::processInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        paddle.move(-1.0f);
        if (paddle.getPosition().x < 0) {
            paddle.setPosition(sf::Vector2f(0, paddle.getPosition().y));
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        paddle.move(1.0f);
        if (paddle.getPosition().x + paddle.getSize().x > 800) {
            paddle.setPosition(sf::Vector2f(800 - paddle.getSize().x, paddle.getPosition().y));
        }
    }

    // Запуск мяча по нажатию пробела
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && ball.isBallSticky()) {
        ball.launch(sf::Vector2f(0.0f, -1.0f));
    }
}

void Game::checkCollisions() {
        sf::Vector2f prevBallPos = ball.getPrevPosition();
        sf::Vector2f ballPos = ball.getPosition();
        float ballRadius = ball.getRadius();

        // Проверка коллизий мяча с блоками
        for (auto& block : blocks) {
            if (block->isAlive()) {
                sf::FloatRect blockBounds = block->getBounds();
                sf::FloatRect ballBounds = ball.getBounds();
                
                if (ballBounds.intersects(blockBounds)) {
                    // Вычисляем направление движения мяча
                    sf::Vector2f movement = ballPos - prevBallPos;
                    if (movement.x == 0 && movement.y == 0) continue; // Мяч не двигался
                    
                    // Нормализуем вектор движения
                    float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
                    movement.x /= length;
                    movement.y /= length;
                    
                    // Определяем, с какой стороны произошло столкновение
                    float ballCenterX = ballPos.x;
                    float ballCenterY = ballPos.y;
                    float blockCenterX = block->getPosition().x + block->getSize().x / 2;
                    float blockCenterY = block->getPosition().y + block->getSize().y / 2;
                    
                    float dx = ballCenterX - blockCenterX;
                    float dy = ballCenterY - blockCenterY;
                    
                    // Определяем, какая сторона блока ближе к мячу
                    if (std::abs(dx / block->getSize().x) > std::abs(dy / block->getSize().y)) {
                        movement.x = -movement.x;
                        if (dx > 0) {
                            ball.setPosition(sf::Vector2f(
                                blockBounds.left + blockBounds.width + ballRadius + 1,
                                ballPos.y
                            ));
                        } else {
                            ball.setPosition(sf::Vector2f(
                                blockBounds.left - ballRadius - 1,
                                ballPos.y
                            ));
                        }
                    } else {
                        movement.y = -movement.y;
                        if (dy > 0) {
                            ball.setPosition(sf::Vector2f(
                                ballPos.x,
                                blockBounds.top + blockBounds.height + ballRadius + 1
                            ));
                        } else {
                            ball.setPosition(sf::Vector2f(
                                ballPos.x,
                                blockBounds.top - ballRadius - 1
                            ));
                        }
                    }
                    
                    ball.reflect(movement * block->getSpeedMultiplier());
                    
                    if (block->onHit()) {
                        score++;
                    }
                    
                    if (!block->isAlive() && block->hasBonusBlock()) {
                        activeBonuses.push_back(std::unique_ptr<Bonus>(block->createBonus()));
                    }
                    
                    break;
                }
            }
        }

        // Проверка границ экрана для мяча
        if (ballPos.x - ballRadius < 0) {
            ball.reflect(sf::Vector2f(1, 0));
            ball.setPosition(sf::Vector2f(ballRadius, ballPos.y));
        }
        else if (ballPos.x + ballRadius > 800) {
            ball.reflect(sf::Vector2f(-1, 0));
            ball.setPosition(sf::Vector2f(800 - ballRadius, ballPos.y));
        }

        if (ballPos.y - ballRadius < 0) {
            ball.reflect(sf::Vector2f(0, 1));
            ball.setPosition(sf::Vector2f(ballPos.x, ballRadius));
        }

        // Проверка столкновения с кареткой
        sf::FloatRect paddleBounds = paddle.getBounds();
        sf::FloatRect ballBounds = ball.getBounds();
        
        if (ballBounds.intersects(paddleBounds)) {
            // Вычисляем точку столкновения относительно центра каретки
            float paddleCenterX = paddle.getPosition().x + paddle.getSize().x / 2;
            float hitPoint = (ballPos.x - paddleCenterX) / (paddle.getSize().x / 2);
            
            float angle = hitPoint * 60.0f * 3.14159f / 180.0f;
            
            sf::Vector2f reflection(std::sin(angle), -std::cos(angle));
            
            ball.reflect(reflection);
            
            ball.setPosition(sf::Vector2f(
                ballPos.x,
                paddle.getPosition().y - ballRadius - 1
            ));
        }

        // Проверка проигрыша (мяч упал ниже каретки)
        if (ballPos.y + ballRadius > 600) {
            if (paddle.isBottomPaddle()) {
                ball.reflect(sf::Vector2f(0, -1));
                paddle.setBottom(false);
            } else {
                lives--;
                if (lives <= 0) {
                    // Игра окончена
                    window.close();
                } else {
                    // Возвращаем мяч на каретку
                    ball.setSticky(true);
                    ball.setPosition(sf::Vector2f(
                        paddle.getPosition().x + paddle.getSize().x / 2,
                        paddle.getPosition().y - 10
                    ));
                }
            }
        }
}

int Game::run() {
    float ballSpeedMultiplier = 1.0f;
    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        processInput();

        update(deltaTime);
        
        checkCollisions();

        redrawAll();
        
    }

    return 0;
}