#include "Bonus.hpp"
#include "Grid.hpp"
#include <random>
#include <algorithm>

// Генератор случайных чисел
static std::random_device rd;
static std::mt19937 gen(rd());

/**
 * @brief Конструктор бонуса изменения цвета
 * @param grid Указатель на игровое поле
 */
ColorChangeBonus::ColorChangeBonus(Grid* grid) : Bonus(grid) {
    shape.setRadius(10.f);
    shape.setFillColor(sf::Color::Cyan);
    shape.setOrigin(10.f, 10.f);
}

/**
 * @brief Активирует бонус изменения цвета
 * @param target Гем, на котором активируется бонус
 */
void ColorChangeBonus::activate(Gem& target) {
    // Получаем позицию целевого гема
    sf::Vector2i targetPos = grid->getGemPosition(&target);
    
    // Собираем все возможные позиции в радиусе 3
    std::vector<sf::Vector2i> possiblePositions;
    for (int dx = -3; dx <= 3; ++dx) {
        for (int dy = -3; dy <= 3; ++dy) {
            sf::Vector2i pos(targetPos.x + dx, targetPos.y + dy);
            if (grid->isValidPosition(pos)) {
                possiblePositions.push_back(pos);
            }
        }
    }
    
    // Перемешиваем позиции
    std::shuffle(possiblePositions.begin(), possiblePositions.end(), gen);
    
    // Выбираем два случайных не соседних гема
    int count = 0;
    for (const auto& pos : possiblePositions) {
        if (pos == targetPos) continue;
        
        // Проверяем, что гем не соседний с уже выбранными
        bool isAdjacent = false;
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue;
                sf::Vector2i checkPos(pos.x + dx, pos.y + dy);
                if (checkPos == targetPos) {
                    isAdjacent = true;
                    break;
                }
            }
        }
        
        if (!isAdjacent) {
            if (auto* gem = grid->getGemAt(pos)) {
                // Меняем цвет гема на случайный
                std::uniform_int_distribution<> typeDist(0, 4);
                gem->setType(static_cast<GemType>(typeDist(gen)));
                count++;
                if (count >= 2) break;
            }
        }
    }
    
    // Меняем цвет целевого гема
    std::uniform_int_distribution<> typeDist(0, 4);
    target.setType(static_cast<GemType>(typeDist(gen)));
}

/**
 * @brief Отрисовывает бонус изменения цвета
 * @param window Окно для отрисовки
 * @param position Позиция для отрисовки
 */
void ColorChangeBonus::draw(sf::RenderWindow& window, const sf::Vector2f& position) {
    shape.setPosition(position);
    window.draw(shape);
}

/**
 * @brief Конструктор бонуса-бомбы
 * @param grid Указатель на игровое поле
 */
BombBonus::BombBonus(Grid* grid) : Bonus(grid) {
    shape.setSize(sf::Vector2f(20.f, 20.f));
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(10.f, 10.f);
}

/**
 * @brief Активирует бонус-бомбу
 * @param target Гем, на котором активируется бонус
 */
void BombBonus::activate(Gem& target) {
    // Собираем все гемы на поле
    std::vector<Gem*> allGems;
    for (int row = 0; row < Grid::GRID_HEIGHT; ++row) {
        for (int col = 0; col < Grid::GRID_WIDTH; ++col) {
            if (auto* gem = grid->getGemAt({col, row})) {
                allGems.push_back(gem);
            }
        }
    }
    
    // Перемешиваем гемы
    std::shuffle(allGems.begin(), allGems.end(), gen);
    
    // Удаляем 5 случайных гемов
    int count = 0;
    for (auto* gem : allGems) {
        if (gem != &target) {  // Не удаляем целевой гем
            grid->removeGem(grid->getGemPosition(gem));
            count++;
            if (count >= 5) break;
        }
    }
}

/**
 * @brief Отрисовывает бонус-бомбу
 * @param window Окно для отрисовки
 * @param position Позиция для отрисовки
 */
void BombBonus::draw(sf::RenderWindow& window, const sf::Vector2f& position) {
    shape.setPosition(position);
    window.draw(shape);
} 