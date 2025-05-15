#include "Grid.hpp"
#include <random>

Grid::Grid(int width, int height) : width(width), height(height) {
    gems.resize(width);
    for (int x = 0; x < width; ++x) {
        gems[x].resize(height);
    }
    fillEmptySpaces();
}

void Grid::draw(sf::RenderWindow& window) {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (gems[x][y]) {
                window.draw(*gems[x][y]);
            }
        }
    }
}

void Grid::swapGems(const sf::Vector2i& pos1, const sf::Vector2i& pos2) {
    if (!isValidPosition(pos1) || !isValidPosition(pos2)) return;
    std::swap(gems[pos1.x][pos1.y], gems[pos2.x][pos2.y]);
    
    // Обновляем позиции после обмена
    if (gems[pos1.x][pos1.y]) {
        sf::Vector2f newPos(
            pos1.x * Gem::TOTAL_SIZE + Gem::PADDING,
            pos1.y * Gem::TOTAL_SIZE + Gem::PADDING
        );
        gems[pos1.x][pos1.y]->startFalling(newPos);
    }
    if (gems[pos2.x][pos2.y]) {
        sf::Vector2f newPos(
            pos2.x * Gem::TOTAL_SIZE + Gem::PADDING,
            pos2.y * Gem::TOTAL_SIZE + Gem::PADDING
        );
        gems[pos2.x][pos2.y]->startFalling(newPos);
    }
}

bool Grid::checkMatches() {
    bool foundMatches = false;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (checkHorizontalMatches(y, x) || checkVerticalMatches(y, x)) {
                foundMatches = true;
            }
        }
    }
    return foundMatches;
}

void Grid::removeMatches() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            removeHorizontalMatches(y, x);
            removeVerticalMatches(y, x);
        }
    }
}

void Grid::dropGems() {
    for (int x = 0; x < width; ++x) {
        for (int y = height - 1; y >= 0; --y) {
            if (!gems[x][y]) {
                // Find the first non-empty gem above
                int sourceY = y - 1;
                while (sourceY >= 0 && !gems[x][sourceY]) {
                    --sourceY;
                }
                
                if (sourceY >= 0) {
                    // Move the gem down
                    gems[x][y] = std::move(gems[x][sourceY]);
                    if (gems[x][y]) {
                        sf::Vector2f newPos(
                            x * Gem::TOTAL_SIZE + Gem::PADDING,
                            y * Gem::TOTAL_SIZE + Gem::PADDING
                        );
                        gems[x][y]->startFalling(newPos);
                    }
                }
            }
        }
    }
}

bool Grid::isAdjacent(const sf::Vector2i& pos1, const sf::Vector2i& pos2) const {
    if (!isValidPosition(pos1) || !isValidPosition(pos2)) return false;
    
    // Проверяем, что гемы находятся на расстоянии 1 клетки друг от друга
    int dx = std::abs(pos1.x - pos2.x);
    int dy = std::abs(pos1.y - pos2.y);
    
    // Гемы соседние, если они находятся на расстоянии 1 по горизонтали или вертикали
    return (dx == 1 && dy == 0) || (dx == 0 && dy == 1);
}

Gem* Grid::getGemAt(const sf::Vector2i& position) {
    if (!isValidPosition(position)) return nullptr;
    return gems[position.x][position.y].get();
}

void Grid::removeGem(const sf::Vector2i& position) {
    if (isValidPosition(position)) {
        gems[position.x][position.y].reset();
    }
}

sf::Vector2i Grid::getGemPosition(const Gem* gem) const {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (gems[x][y].get() == gem) {
                return sf::Vector2i(x, y);
            }
        }
    }
    return sf::Vector2i(-1, -1);
}

bool Grid::isValidPosition(const sf::Vector2i& position) const {
    return position.x >= 0 && position.x < width &&
           position.y >= 0 && position.y < height;
}

void Grid::fillEmptySpaces() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, static_cast<int>(GemType::ORANGE));

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (!gems[x][y]) {
                sf::Vector2f pos(
                    x * Gem::TOTAL_SIZE + Gem::PADDING,
                    y * Gem::TOTAL_SIZE + Gem::PADDING
                );
                gems[x][y] = std::make_unique<Gem>(static_cast<GemType>(dis(gen)), pos);
            }
        }
    }
}

bool Grid::checkHorizontalMatches(int row, int col) {
    if (col + 2 >= width) return false;
    
    Gem* gem1 = gems[col][row].get();
    Gem* gem2 = gems[col + 1][row].get();
    Gem* gem3 = gems[col + 2][row].get();
    
    return gem1 && gem2 && gem3 &&
           gem1->getType() == gem2->getType() &&
           gem2->getType() == gem3->getType();
}

bool Grid::checkVerticalMatches(int row, int col) {
    if (row + 2 >= height) return false;
    
    Gem* gem1 = gems[col][row].get();
    Gem* gem2 = gems[col][row + 1].get();
    Gem* gem3 = gems[col][row + 2].get();
    
    return gem1 && gem2 && gem3 &&
           gem1->getType() == gem2->getType() &&
           gem2->getType() == gem3->getType();
}

void Grid::removeHorizontalMatches(int row, int col) {
    if (checkHorizontalMatches(row, col)) {
        for (int i = 0; i < 3; ++i) {
            if (gems[col + i][row]) {
                if (gems[col + i][row]->hasBonus()) {
                    gems[col + i][row]->activateBonus(*gems[col + i][row], *this);
                }
                gems[col + i][row]->startDisappearing();
                gems[col + i][row].reset();
            }
        }
    }
}

void Grid::removeVerticalMatches(int row, int col) {
    if (checkVerticalMatches(row, col)) {
        for (int i = 0; i < 3; ++i) {
            if (gems[col][row + i]) {
                if (gems[col][row + i]->hasBonus()) {
                    gems[col][row + i]->activateBonus(*gems[col][row + i], *this);
                }
                gems[col][row + i]->startDisappearing();
                gems[col][row + i].reset();
            }
        }
    }
} 