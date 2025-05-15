#include "Game.hpp"
#include <iostream>
#include <SFML/System/Clock.hpp>

/**
 * @brief Конструктор игры
 * 
 * Создает окно и инициализирует игровое поле.
 */
Game::Game() : window(sf::VideoMode(
        static_cast<unsigned int>(Grid::GRID_WIDTH * Gem::TOTAL_SIZE + Gem::PADDING),
        static_cast<unsigned int>(Grid::GRID_HEIGHT * Gem::TOTAL_SIZE + Gem::PADDING)
    ), "Gems Game"),
    isFirstGemSelected(false), score(0), running(true) {
    // Устанавливаем вид окна
    sf::View view(sf::FloatRect(0, 0, 
        Grid::GRID_WIDTH * Gem::TOTAL_SIZE + Gem::PADDING,
        Grid::GRID_HEIGHT * Gem::TOTAL_SIZE + Gem::PADDING));
    window.setView(view);
    
    grid = std::make_unique<Grid>(Grid::GRID_WIDTH, Grid::GRID_HEIGHT);
}

/**
 * @brief Запускает игровой цикл
 * 
 * Основной цикл игры, обрабатывающий события, обновляющий
 * состояние и отрисовывающий кадр.
 */
void Game::run() {
    sf::Clock clock;
    while (window.isOpen() && running) {
        float deltaTime = clock.restart().asSeconds();
        processEvents();
        update(deltaTime);
        render();
        sf::sleep(sf::milliseconds(16) - sf::milliseconds(deltaTime * 1000));
    }
}

/**
 * @brief Обрабатывает события окна
 * 
 * Обрабатывает события SFML, включая закрытие окна
 * и клики мыши.
 */
void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            running = false;
            window.close();
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                // Получаем размеры окна и вида
                sf::Vector2f windowSize = sf::Vector2f(window.getSize());
                sf::Vector2f viewSize = sf::Vector2f(window.getView().getSize());
                
                // Вычисляем масштаб
                float scaleX = windowSize.x / viewSize.x;
                float scaleY = windowSize.y / viewSize.y;
                
                // Преобразуем координаты мыши с учетом масштаба
                sf::Vector2i mousePos(
                    static_cast<int>(event.mouseButton.x / scaleX),
                    static_cast<int>(event.mouseButton.y / scaleY)
                );
                
                sf::Vector2i gridPos(
                    (mousePos.x - static_cast<int>(Gem::PADDING)) / static_cast<int>(Gem::TOTAL_SIZE),
                    (mousePos.y - static_cast<int>(Gem::PADDING)) / static_cast<int>(Gem::TOTAL_SIZE)
                );
                
                std::cout << "Mouse click at: " << mousePos.x << ", " << mousePos.y 
                         << " -> Grid pos: " << gridPos.x << ", " << gridPos.y << std::endl;
                handleMouseClick(gridPos);
            }
        }
    }
}

/**
 * @brief Обновляет состояние игры
 * @param deltaTime Время с последнего обновления
 * 
 * Обновляет состояние всех гемов и проверяет совпадения.
 */
void Game::update(float deltaTime) {
    for (int x = 0; x < Grid::GRID_WIDTH; ++x) {
        for (int y = 0; y < Grid::GRID_HEIGHT; ++y) {
            if (auto* gem = grid->getGemAt(sf::Vector2i(x, y))) {
                gem->update(deltaTime);
            }
        }
    }

    bool hasAnimations = false;
    for (int x = 0; x < Grid::GRID_WIDTH && !hasAnimations; ++x) {
        for (int y = 0; y < Grid::GRID_HEIGHT && !hasAnimations; ++y) {
            if (auto* gem = grid->getGemAt(sf::Vector2i(x, y))) {
                if (gem->isAnimating()) {
                    hasAnimations = true;
                }
            }
        }
    }

    if (!hasAnimations && grid->checkMatches()) {
        grid->removeMatches();
        grid->dropGems();
        grid->fillEmptySpaces();
    }
}

/**
 * @brief Отрисовывает текущий кадр
 * 
 * Очищает окно и отрисовывает все элементы игры.
 */
void Game::render() {
    window.clear(sf::Color::Black);
    grid->draw(window);
    window.display();
}

/**
 * @brief Обрабатывает клик мыши
 * @param position Позиция клика
 * 
 * Преобразует координаты клика в позицию на поле и
 * обрабатывает выбор и перемещение гемов.
 */
void Game::handleMouseClick(const sf::Vector2i& position) {
    if (!grid->isValidPosition(position)) {
        std::cout << "Invalid position: " << position.x << ", " << position.y << std::endl;
        return;
    }

    bool hasAnimations = false;
    for (int x = 0; x < Grid::GRID_WIDTH && !hasAnimations; ++x) {
        for (int y = 0; y < Grid::GRID_HEIGHT && !hasAnimations; ++y) {
            if (auto* gem = grid->getGemAt(sf::Vector2i(x, y))) {
                if (gem->isAnimating()) {
                    hasAnimations = true;
                }
            }
        }
    }

    if (hasAnimations) return;

    if (!isFirstGemSelected) {
        firstGemPosition = position;
        isFirstGemSelected = true;
        std::cout << "First gem selected at: " << position.x << ", " << position.y << std::endl;
    } else {
        std::cout << "Second gem selected at: " << position.x << ", " << position.y << std::endl;
        if (grid->isAdjacent(firstGemPosition, position)) {
            std::cout << "Gems are adjacent, swapping..." << std::endl;
            grid->swapGems(firstGemPosition, position);
            if (!grid->checkMatches()) {
                std::cout << "No matches found, swapping back..." << std::endl;
                grid->swapGems(firstGemPosition, position);
            }
        } else {
            std::cout << "Gems are not adjacent! Distance: " 
                     << std::abs(firstGemPosition.x - position.x) + std::abs(firstGemPosition.y - position.y)
                     << std::endl;
        }
        isFirstGemSelected = false;
    }
} 