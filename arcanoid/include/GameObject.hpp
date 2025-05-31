#pragma once
#include <SFML/Graphics.hpp>

/**
 * @brief Базовый класс всех игровых объектов
 *
 * Хранит позицию, размер и форму объекта, предоставляет
 * интерфейс для обновления, отрисовки и проверки столкновений.
 */
class GameObject {
public:
    /**
     * @brief Конструктор объекта
     * @param pos Начальная позиция верхнего левого угла
     * @param size Размер объекта (ширина и высота)
     */
    GameObject(const sf::Vector2f& pos, const sf::Vector2f& size);

    /**
     * @brief Виртуальный деструктор
     */
    virtual ~GameObject();

    // Запрещаем копирование и перемещение
    GameObject(const GameObject&) = delete;
    GameObject& operator=(const GameObject&) = delete;
    GameObject(GameObject&&) = delete;
    GameObject& operator=(GameObject&&) = delete;

    /**
     * @brief Обновляет состояние объекта (пустая реализация по умолчанию)
     * @param deltaTime Время с последнего кадра (секунды)
     */
    virtual void update(float deltaTime) {}

    /**
     * @brief Отрисовывает объект на экране
     * @param window Окно SFML для отрисовки
     */
    virtual void draw(sf::RenderWindow& window);

    /**
     * @brief Возвращает текущую позицию объекта
     * @return Вектор позиции верхнего левого угла
     */
    const sf::Vector2f& getPosition() const;

    /**
     * @brief Возвращает текущий размер объекта
     * @return Вектор размера (ширина, высота)
     */
    const sf::Vector2f& getSize() const;

    /**
     * @brief Устанавливает новую позицию объекта
     * @param pos Новая позиция верхнего левого угла
     */
    virtual void setPosition(const sf::Vector2f& pos);

    /**
     * @brief Проверяет столкновение с другим объектом
     * @param other Ссылка на другой игровой объект
     * @return true, если границы пересекаются
     */
    virtual bool checkCollision(const GameObject& other) const;

    /**
     * @brief Получает глобальные границы формы для коллизий
     * @return Прямоугольник границ
     */
    sf::FloatRect getBounds() const { return shape->getGlobalBounds(); }

    /**
     * @brief Задает новую форму (для отрисовки и коллизий)
     * @param newShape Указатель на форму SFML (CircleShape, RectangleShape и т.д.)
     */
    void setShape(sf::Shape* newShape);

protected:
    sf::Vector2f position;    /**< Позиция объекта */
    sf::Vector2f size;        /**< Размер объекта */
    sf::Shape*   shape;       /**< Форма для отрисовки и коллизий */
};