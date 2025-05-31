#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Gem.hpp"

/**
 * @class Grid
 * @brief Класс игрового поля, управляющий сеткой гемов
 * 
 * Класс отвечает за хранение и управление гемами на игровом поле,
 * проверку совпадений, удаление гемов и заполнение пустых мест.
 */
class Grid {
public:
    /**
     * @brief Конструктор игрового поля
     * @param width Ширина поля
     * @param height Высота поля
     * 
     * Создает сетку заданного размера и заполняет ее гемами.
     */
    Grid(int width, int height);
    
    /**
     * @brief Деструктор игрового поля
     */
    ~Grid() = default;
    
    /**
     * @brief Отрисовывает игровое поле
     * @param window Окно для отрисовки
     */
    void draw(sf::RenderWindow& window);
    
    /**
     * @brief Меняет местами два гема
     * @param pos1 Позиция первого гема
     * @param pos2 Позиция второго гема
     * 
     * Меняет местами гемы и запускает анимацию их перемещения.
     */
    void swapGems(const sf::Vector2i& pos1, const sf::Vector2i& pos2);
    
    /**
     * @brief Проверяет наличие совпадений на поле
     * @return true если найдены совпадения, false иначе
     */
    bool checkMatches();
    
    /**
     * @brief Удаляет все найденные совпадения
     * 
     * Удаляет гемы, образующие совпадения, и запускает
     * анимацию их исчезновения.
     */
    void removeMatches();
    
    /**
     * @brief Обрабатывает падение гемов
     * 
     * Перемещает гемы вниз для заполнения пустых мест
     * и запускает анимацию их падения.
     */
    void dropGems();
    
    /**
     * @brief Заполняет пустые места новыми гемами
     * 
     * Создает новые гемы в пустых местах и запускает
     * анимацию их появления.
     */
    void fillEmptySpaces();
    
    /**
     * @brief Проверяет, являются ли две позиции соседними
     * @param pos1 Первая позиция
     * @param pos2 Вторая позиция
     * @return true если позиции соседние, false иначе
     */
    bool isAdjacent(const sf::Vector2i& pos1, const sf::Vector2i& pos2) const;
    
    /**
     * @brief Получает гем по позиции
     * @param position Позиция гема
     * @return Указатель на гем или nullptr, если позиция пуста
     */
    Gem* getGemAt(const sf::Vector2i& position);
    
    /**
     * @brief Удаляет гем с заданной позиции
     * @param position Позиция гема
     */
    void removeGem(const sf::Vector2i& position);
    
    /**
     * @brief Получает позицию гема
     * @param gem Указатель на гем
     * @return Позиция гема или (-1, -1), если гем не найден
     */
    sf::Vector2i getGemPosition(const Gem* gem) const;
    
    /**
     * @brief Проверяет валидность позиции
     * @param position Проверяемая позиция
     * @return true если позиция валидна, false иначе
     */
    bool isValidPosition(const sf::Vector2i& position) const;
    
    static constexpr int GRID_WIDTH = 8;   ///< Ширина игрового поля
    static constexpr int GRID_HEIGHT = 8;  ///< Высота игрового поля

private:
    /**
     * @brief Проверяет горизонтальные совпадения
     * @param row Строка для проверки
     * @param col Начальная колонка
     * @return true если найдено совпадение, false иначе
     */
    bool checkHorizontalMatches(int row, int col);
    
    /**
     * @brief Проверяет вертикальные совпадения
     * @param row Начальная строка
     * @param col Колонка для проверки
     * @return true если найдено совпадение, false иначе
     */
    bool checkVerticalMatches(int row, int col);
    
    /**
     * @brief Удаляет горизонтальные совпадения
     * @param row Строка для проверки
     * @param col Начальная колонка
     */
    void removeHorizontalMatches(int row, int col);
    
    /**
     * @brief Удаляет вертикальные совпадения
     * @param row Начальная строка
     * @param col Колонка для проверки
     */
    void removeVerticalMatches(int row, int col);

    std::vector<std::vector<std::unique_ptr<Gem>>> gems;  ///< Сетка гемов
    int width;   ///< Ширина поля
    int height;  ///< Высота поля
}; 