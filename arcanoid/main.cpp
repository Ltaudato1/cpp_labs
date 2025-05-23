#include <SFML/Graphics.hpp>
#include "include/GameObject.hpp"
#include "include/Ball.hpp"
#include "include/Paddle.hpp"
#include "include/Block.hpp"
#include <vector>
#include <memory>
#include <cmath>

int main() {
    // Создаем окно
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arkanoid");
    window.setFramerateLimit(60);

    // Создаем каретку
    Paddle paddle(sf::Vector2f(350, 550), sf::Vector2f(100, 20), 20.0f, true);
    
    // Создаем мяч
    Ball ball(sf::Vector2f(400, 530), 10.0f, 150.0f);
    
    // Создаем блоки
    std::vector<std::unique_ptr<Block>> blocks;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 5; ++j) {
            blocks.emplace_back(std::make_unique<Block>(
                sf::Vector2f(50 + i * 90, 50 + j * 40),
                sf::Vector2f(80, 30),
                1, // health
                true, // destructible
                false, // bonus
                1.0f // speedMult
            ));
        }
    }

    // Игровой цикл
    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        // Обработка событий
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Управление кареткой
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            paddle.move(-1.0f);
            // Проверка левой границы
            if (paddle.getPosition().x < 0) {
                paddle.setPosition(sf::Vector2f(0, paddle.getPosition().y));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            paddle.move(1.0f);
            // Проверка правой границы
            if (paddle.getPosition().x + paddle.getSize().x > 800) {
                paddle.setPosition(sf::Vector2f(800 - paddle.getSize().x, paddle.getPosition().y));
            }
        }

        // Запуск мяча по нажатию пробела
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && ball.isBallSticky()) {
            ball.launch(sf::Vector2f(0.5f, -1.0f));
        }

        // Обновление
        paddle.update(deltaTime);
        if (ball.isBallSticky()) {
            ball.setPosition(sf::Vector2f(
                paddle.getPosition().x + paddle.getSize().x / 2,
                paddle.getPosition().y - 10
            ));
        }

        // Сохраняем предыдущую позицию мяча для проверки столкновений
        sf::Vector2f prevBallPos = ball.getPosition();
        ball.update(deltaTime);
        sf::Vector2f ballPos = ball.getPosition();
        float ballRadius = 10.0f;

        // Проверка столкновения с кареткой
        if (!ball.isBallSticky()) {
            sf::FloatRect paddleBounds = paddle.getBounds();
            sf::FloatRect ballBounds = ball.getBounds();
            
            // Проверяем столкновение с учетом предыдущей позиции
            if (ballBounds.intersects(paddleBounds)) {
                // Вычисляем точку удара относительно центра каретки
                float hitPoint = (ballPos.x - paddle.getPosition().x) / paddle.getSize().x;
                hitPoint = std::max(0.0f, std::min(1.0f, hitPoint)); // Ограничиваем значения от 0 до 1
                
                // Вычисляем угол отражения (от -60 до 60 градусов)
                float angle = (hitPoint - 0.5f) * 120.0f;
                float radians = angle * 3.14159f / 180.0f;
                
                // Создаем вектор отражения
                sf::Vector2f reflectDir(std::sin(radians), -std::cos(radians));
                
                // Нормализуем вектор отражения
                float length = std::sqrt(reflectDir.x * reflectDir.x + reflectDir.y * reflectDir.y);
                reflectDir.x /= length;
                reflectDir.y /= length;
                
                ball.reflect(reflectDir);
                
                // Корректируем позицию мяча, чтобы он не застрял в каретке
                ball.setPosition(sf::Vector2f(
                    ballPos.x,
                    paddle.getPosition().y - ballRadius - 1
                ));
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

        // Проверка проигрыша (мяч упал ниже каретки)
        if (ballPos.y + ballRadius > 600) {
            ball.setSticky(true);
            ball.setPosition(sf::Vector2f(
                paddle.getPosition().x + paddle.getSize().x / 2,
                paddle.getPosition().y - 10
            ));
        }

        // Проверка коллизий мяча с блоками
        for (auto& block : blocks) {
            if (block->isAlive()) {
                sf::FloatRect blockBounds = block->getBounds();
                sf::FloatRect ballBounds = ball.getBounds();
                if (ballBounds.intersects(blockBounds)) {
                    block->onHit();
                    
                    // Определяем, с какой стороны произошло столкновение
                    float ballCenterX = ballPos.x;
                    float ballCenterY = ballPos.y;
                    float blockCenterX = block->getPosition().x + block->getSize().x / 2;
                    float blockCenterY = block->getPosition().y + block->getSize().y / 2;
                    
                    float dx = ballCenterX - blockCenterX;
                    float dy = ballCenterY - blockCenterY;
                    
                    // Определяем, какая сторона блока ближе к мячу
                    if (std::abs(dx / block->getSize().x) > std::abs(dy / block->getSize().y)) {
                        // Горизонтальное отражение
                        ball.reflect(sf::Vector2f(dx > 0 ? 1 : -1, 0));
                    } else {
                        // Вертикальное отражение
                        ball.reflect(sf::Vector2f(0, dy > 0 ? 1 : -1));
                    }
                    
                    // Корректируем позицию мяча, чтобы он не застрял в блоке
                    if (std::abs(dx / block->getSize().x) > std::abs(dy / block->getSize().y)) {
                        ball.setPosition(sf::Vector2f(
                            dx > 0 ? blockBounds.left + blockBounds.width + ballRadius + 1 : blockBounds.left - ballRadius - 1,
                            ballPos.y
                        ));
                    } else {
                        ball.setPosition(sf::Vector2f(
                            ballPos.x,
                            dy > 0 ? blockBounds.top + blockBounds.height + ballRadius + 1 : blockBounds.top - ballRadius - 1
                        ));
                    }
                }
            }
        }

        window.clear(sf::Color::Black);
        paddle.draw(window);
        ball.draw(window);
        for (auto& block : blocks) {
            if (block->isAlive()) {
                block->draw(window);
            }
        }
        window.display();
    }

    return 0;
} 