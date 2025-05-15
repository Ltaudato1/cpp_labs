#include "Bonus.hpp"
#include "Grid.hpp"
#include <random>

ColorChangeBonus::ColorChangeBonus(GemType originalType) 
    : originalType(originalType) {
    shape.setRadius(10.f);
    shape.setFillColor(sf::Color::Cyan);
}

void ColorChangeBonus::activate(Gem& target, Grid& grid) {
    // Find 2 random non-adjacent gems within 3 cells radius
    std::vector<sf::Vector2i> candidates;
    sf::Vector2i targetPos = grid.getGemPosition(&target);
    
    for (int dx = -3; dx <= 3; ++dx) {
        for (int dy = -3; dy <= 3; ++dy) {
            sf::Vector2i pos(targetPos.x + dx, targetPos.y + dy);
            if (grid.isValidPosition(pos) && !grid.isAdjacent(pos, targetPos)) {
                candidates.push_back(pos);
            }
        }
    }
    
    // Change color of target gem and 2 random non-adjacent gems
    target.setType(originalType);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(candidates.begin(), candidates.end(), gen);
    
    for (int i = 0; i < 2 && i < candidates.size(); ++i) {
        if (Gem* gem = grid.getGemAt(candidates[i])) {
            gem->setType(originalType);
        }
    }
}

void ColorChangeBonus::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);
}

BombBonus::BombBonus() {
    shape.setRadius(10.f);
    shape.setFillColor(sf::Color::Red);
}

void BombBonus::activate(Gem& target, Grid& grid) {
    std::vector<sf::Vector2i> allPositions;
    for (int x = 0; x < Grid::GRID_WIDTH; ++x) {
        for (int y = 0; y < Grid::GRID_HEIGHT; ++y) {
            allPositions.push_back(sf::Vector2i(x, y));
        }
    }
    
    // Destroy 5 random gems
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(allPositions.begin(), allPositions.end(), gen);
    
    for (int i = 0; i < 5 && i < allPositions.size(); ++i) {
        if (Gem* gem = grid.getGemAt(allPositions[i])) {
            grid.removeGem(allPositions[i]);
        }
    }
}

void BombBonus::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);
} 