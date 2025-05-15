#include "Game.hpp"
#include <iostream>
#include <SFML/System/Clock.hpp>

Game::Game() : window(sf::VideoMode(
        static_cast<unsigned int>(Grid::GRID_WIDTH * Gem::TOTAL_SIZE + Gem::PADDING),
        static_cast<unsigned int>(Grid::GRID_HEIGHT * Gem::TOTAL_SIZE + Gem::PADDING)
    ), "Gems Game"),
    isFirstGemSelected(false), score(0), running(true) {
    grid = std::make_unique<Grid>(Grid::GRID_WIDTH, Grid::GRID_HEIGHT);
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen() && running) {
        float deltaTime = clock.restart().asSeconds();
        processEvents();
        update(deltaTime);
        render();
        // Cap to ~60 FPS
        sf::sleep(sf::milliseconds(16) - sf::milliseconds(deltaTime * 1000));
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            running = false;
            window.close();
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
                // Учитываем отступы при вычислении позиции в сетке
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

void Game::update(float deltaTime) {
    // Обновляем анимации всех гемов
    for (int x = 0; x < Grid::GRID_WIDTH; ++x) {
        for (int y = 0; y < Grid::GRID_HEIGHT; ++y) {
            if (auto* gem = grid->getGemAt(sf::Vector2i(x, y))) {
                gem->update(deltaTime);
            }
        }
    }

    // Проверяем совпадения только если нет активных анимаций
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

void Game::render() {
    window.clear(sf::Color::Black);
    grid->draw(window);
    window.display();
}

void Game::handleMouseClick(const sf::Vector2i& position) {
    if (!grid->isValidPosition(position)) {
        std::cout << "Invalid position: " << position.x << ", " << position.y << std::endl;
        return;
    }

    // Проверяем, нет ли активных анимаций
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

    if (hasAnimations) return;  // Игнорируем клики во время анимаций

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