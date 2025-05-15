#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Grid.hpp"

class Game {
public:
    Game();
    ~Game() = default;
    
    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();
    void handleMouseClick(const sf::Vector2i& position);

    sf::RenderWindow window;
    std::unique_ptr<Grid> grid;
    
    bool isFirstGemSelected;
    sf::Vector2i firstGemPosition;
    int score;
    bool running = true;
}; 