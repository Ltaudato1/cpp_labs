#include "Grid.hpp"
#include <random>

// Генератор случайных чисел
static std::random_device rd;
static std::mt19937 gen(rd());

/**
 * @brief Конструктор игрового поля
 * @param width Ширина поля
 * @param height Высота поля
 */
Grid::Grid(int width, int height) : width(width), height(height) {
    // Создаем сетку гемов
    gems.resize(height, std::vector<std::unique_ptr<Gem>>(width));
    
    // Заполняем поле случайными гемами
    std::uniform_int_distribution<> typeDist(0, 4);
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            gems[row][col] = std::make_unique<Gem>(
                static_cast<GemType>(typeDist(gen)),
                sf::Vector2i(col, row),
                this
            );
        }
    }
}

/**
 * @brief Отрисовывает игровое поле
 * @param window Окно для отрисовки
 */
void Grid::draw(sf::RenderWindow& window) {
    for (const auto& row : gems) {
        for (const auto& gem : row) {
            if (gem) {
                gem->draw(window);
            }
        }
    }
}

/**
 * @brief Меняет местами два гема
 * @param pos1 Позиция первого гема
 * @param pos2 Позиция второго гема
 */
void Grid::swapGems(const sf::Vector2i& pos1, const sf::Vector2i& pos2) {
    if (!isValidPosition(pos1) || !isValidPosition(pos2)) return;
    
    Gem* gem1 = getGemAt(pos1);
    Gem* gem2 = getGemAt(pos2);
    
    if (!gem1 || !gem2) return;
    
    // Меняем местами гемы в сетке
    std::swap(gems[pos1.y][pos1.x], gems[pos2.y][pos2.x]);
    
    // Обновляем позиции гемов
    gem1->setPosition(pos2);
    gem2->setPosition(pos1);
    
    // Запускаем анимацию падения
    gem1->startFalling();
    gem2->startFalling();
}

/**
 * @brief Проверяет наличие совпадений на поле
 * @return true если найдены совпадения, false иначе
 */
bool Grid::checkMatches() {
    bool hasMatches = false;
    
    // Проверяем горизонтальные совпадения
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width - 2; ++col) {
            if (checkHorizontalMatches(row, col)) {
                hasMatches = true;
            }
        }
    }
    
    // Проверяем вертикальные совпадения
    for (int row = 0; row < height - 2; ++row) {
        for (int col = 0; col < width; ++col) {
            if (checkVerticalMatches(row, col)) {
                hasMatches = true;
            }
        }
    }
    
    return hasMatches;
}

/**
 * @brief Удаляет все найденные совпадения
 */
void Grid::removeMatches() {
    // Удаляем горизонтальные совпадения
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width - 2; ++col) {
            removeHorizontalMatches(row, col);
        }
    }
    
    // Удаляем вертикальные совпадения
    for (int row = 0; row < height - 2; ++row) {
        for (int col = 0; col < width; ++col) {
            removeVerticalMatches(row, col);
        }
    }
}

/**
 * @brief Обрабатывает падение гемов
 */
void Grid::dropGems() {
    for (int col = 0; col < width; ++col) {
        // Начинаем с нижней строки
        for (int row = height - 1; row >= 0; --row) {
            if (!gems[row][col]) {
                // Ищем ближайший гем сверху
                for (int above = row - 1; above >= 0; --above) {
                    if (gems[above][col]) {
                        // Перемещаем гем вниз
                        gems[row][col] = std::move(gems[above][col]);
                        gems[row][col]->setPosition(sf::Vector2i(col, row));
                        gems[row][col]->startFalling();
                        break;
                    }
                }
            }
        }
    }
}

/**
 * @brief Заполняет пустые места новыми гемами
 */
void Grid::fillEmptySpaces() {
    std::uniform_int_distribution<> typeDist(0, 4);
    
    for (int col = 0; col < width; ++col) {
        for (int row = 0; row < height; ++row) {
            if (!gems[row][col]) {
                gems[row][col] = std::make_unique<Gem>(
                    static_cast<GemType>(typeDist(gen)),
                    sf::Vector2i(col, row),
                    this
                );
            }
        }
    }
}

/**
 * @brief Проверяет, являются ли две позиции соседними
 * @param pos1 Первая позиция
 * @param pos2 Вторая позиция
 * @return true если позиции соседние, false иначе
 */
bool Grid::isAdjacent(const sf::Vector2i& pos1, const sf::Vector2i& pos2) const {
    if (!isValidPosition(pos1) || !isValidPosition(pos2)) return false;
    
    int dx = std::abs(pos1.x - pos2.x);
    int dy = std::abs(pos1.y - pos2.y);
    
    return (dx == 1 && dy == 0) || (dx == 0 && dy == 1);
}

/**
 * @brief Получает гем по позиции
 * @param position Позиция гема
 * @return Указатель на гем или nullptr, если позиция пуста
 */
Gem* Grid::getGemAt(const sf::Vector2i& position) {
    if (!isValidPosition(position)) return nullptr;
    return gems[position.y][position.x].get();
}

/**
 * @brief Удаляет гем с заданной позиции
 * @param position Позиция гема
 */
void Grid::removeGem(const sf::Vector2i& position) {
    if (!isValidPosition(position)) return;
    
    if (auto* gem = getGemAt(position)) {
        gem->startDisappearing();
        gems[position.y][position.x].reset();
    }
}

/**
 * @brief Получает позицию гема
 * @param gem Указатель на гем
 * @return Позиция гема или (-1, -1), если гем не найден
 */
sf::Vector2i Grid::getGemPosition(const Gem* gem) const {
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            if (gems[row][col].get() == gem) {
                return sf::Vector2i(col, row);
            }
        }
    }
    return sf::Vector2i(-1, -1);
}

/**
 * @brief Проверяет валидность позиции
 * @param position Проверяемая позиция
 * @return true если позиция валидна, false иначе
 */
bool Grid::isValidPosition(const sf::Vector2i& position) const {
    return position.x >= 0 && position.x < width &&
           position.y >= 0 && position.y < height;
}

/**
 * @brief Проверяет горизонтальные совпадения
 * @param row Строка для проверки
 * @param col Начальная колонка
 * @return true если найдено совпадение, false иначе
 */
bool Grid::checkHorizontalMatches(int row, int col) {
    if (!isValidPosition(sf::Vector2i(col, row)) ||
        !isValidPosition(sf::Vector2i(col + 2, row))) {
        return false;
    }
    
    Gem* gem1 = getGemAt(sf::Vector2i(col, row));
    Gem* gem2 = getGemAt(sf::Vector2i(col + 1, row));
    Gem* gem3 = getGemAt(sf::Vector2i(col + 2, row));
    
    if (!gem1 || !gem2 || !gem3) return false;
    
    return gem1->getType() == gem2->getType() &&
           gem2->getType() == gem3->getType();
}

/**
 * @brief Проверяет вертикальные совпадения
 * @param row Начальная строка
 * @param col Колонка для проверки
 * @return true если найдено совпадение, false иначе
 */
bool Grid::checkVerticalMatches(int row, int col) {
    if (!isValidPosition(sf::Vector2i(col, row)) ||
        !isValidPosition(sf::Vector2i(col, row + 2))) {
        return false;
    }
    
    Gem* gem1 = getGemAt(sf::Vector2i(col, row));
    Gem* gem2 = getGemAt(sf::Vector2i(col, row + 1));
    Gem* gem3 = getGemAt(sf::Vector2i(col, row + 2));
    
    if (!gem1 || !gem2 || !gem3) return false;
    
    return gem1->getType() == gem2->getType() &&
           gem2->getType() == gem3->getType();
}

/**
 * @brief Удаляет горизонтальные совпадения
 * @param row Строка для проверки
 * @param col Начальная колонка
 */
void Grid::removeHorizontalMatches(int row, int col) {
    if (!checkHorizontalMatches(row, col)) return;
    
    // Удаляем все совпадающие гемы в строке
    int currentCol = col;
    GemType matchType = getGemAt(sf::Vector2i(col, row))->getType();
    
    while (currentCol < width) {
        Gem* gem = getGemAt(sf::Vector2i(currentCol, row));
        if (!gem || gem->getType() != matchType) break;
        
        removeGem(sf::Vector2i(currentCol, row));
        currentCol++;
    }
}

/**
 * @brief Удаляет вертикальные совпадения
 * @param row Начальная строка
 * @param col Колонка для проверки
 */
void Grid::removeVerticalMatches(int row, int col) {
    if (!checkVerticalMatches(row, col)) return;
    
    // Удаляем все совпадающие гемы в колонке
    int currentRow = row;
    GemType matchType = getGemAt(sf::Vector2i(col, row))->getType();
    
    while (currentRow < height) {
        Gem* gem = getGemAt(sf::Vector2i(col, currentRow));
        if (!gem || gem->getType() != matchType) break;
        
        removeGem(sf::Vector2i(col, currentRow));
        currentRow++;
    }
} 