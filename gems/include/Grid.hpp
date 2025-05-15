#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Gem.hpp"

class Grid {
public:
    Grid(int width, int height);
    ~Grid() = default;
    
    void draw(sf::RenderWindow& window);
    void swapGems(const sf::Vector2i& pos1, const sf::Vector2i& pos2);
    bool checkMatches();
    void removeMatches();
    void dropGems();
    void fillEmptySpaces();
    bool isAdjacent(const sf::Vector2i& pos1, const sf::Vector2i& pos2) const;
    Gem* getGemAt(const sf::Vector2i& position);
    void removeGem(const sf::Vector2i& position);
    sf::Vector2i getGemPosition(const Gem* gem) const;
    bool isValidPosition(const sf::Vector2i& position) const;
    
    static constexpr int GRID_WIDTH = 8;
    static constexpr int GRID_HEIGHT = 8;

private:
    std::vector<std::vector<std::unique_ptr<Gem>>> gems;
    int width;
    int height;
    
    bool checkHorizontalMatches(int row, int col);
    bool checkVerticalMatches(int row, int col);
    void removeHorizontalMatches(int row, int col);
    void removeVerticalMatches(int row, int col);
}; 