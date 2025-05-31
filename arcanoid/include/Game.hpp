#pragma once
#include <SFML/Graphics.hpp>
#include "Block.hpp"
#include "Paddle.hpp"
#include "Bonus.hpp"
#include "Ball.hpp"
#include "ResourceManager.hpp"
#include <memory>
#include <vector>

/**
 * @brief Основной класс игры Arkanoid
 * 
 * Управляет игровым циклом: обработка ввода,
 * обновление логики, проверка коллизий и отрисовка.
 */
class Game {
public:
    /**
     * @brief Конструктор игры
     * 
     * Инициализирует окно, загружает ресурсы и создает начальные объекты.
     */
    Game();

    /**
     * @brief Запускает основной игровой цикл
     * 
     * Циклически вызывает методы ввода, обновления и отрисовки,
     * пока окно не будет закрыто.
     * @return Код завершения (0 при нормальном выходе)
     */
    int run();

    /**
     * @brief Обрабатывает ввод пользователя
     * 
     * Считывает события SFML и реагирует на нажатия клавиш.
     */
    void processInput();

    /**
     * @brief Обновляет состояние игровых объектов
     * 
     * @param deltaTime Интервал времени с последнего кадра (в секундах)
     */
    void update(float deltaTime);

    /**
     * @brief Проверяет и обрабатывает столкновения
     * 
     * Отвечает за логику столкновений мяча с блоками, стенами и ракеткой,
     * а также за проверку потери жизни.
     */
    void checkCollisions();

    /**
     * @brief Перерисовывает все элементы сцены
     * 
     * Очищает окно, рисует блоки, бонусы, ракетку, мяч и UI, затем выводит на экран.
     */
    void redrawAll();

private:
    int score;    /**< Текущие очки игрока */
    int lives;    /**< Оставшееся количество жизней */

    ResourceManager manager;                          /**< Менеджер ресурсов */
    sf::Text         scoreText;                       /**< Текст для отображения счета */
    sf::Sprite       heartSprite;                     /**< Иконка для отображения жизней */

    sf::RenderWindow window;                          /**< Окно приложения */
    std::vector<std::unique_ptr<Block>>    blocks;     /**< Коллекция блоков */
    std::vector<std::unique_ptr<Bonus>>    activeBonuses; /**< Активные бонусы на экране */

    Paddle paddle;   /**< Игровая ракетка */
    Ball   ball;     /**< Игровой мяч */
};