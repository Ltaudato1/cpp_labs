#pragma once
#include <SFML/Graphics.hpp>
#include <stdexcept>

/**
 * @brief Менеджер ресурсов: шрифтов и текстур
 *
 * Отвечает за загрузку и предоставление общих игровых ресурсов.
 */
class ResourceManager {
public:
    /**
     * @brief Конструктор загружает необходимые файлы из папки resources
     * @throws std::runtime_error если какой-либо ресурс не удалось загрузить
     */
    ResourceManager() {
        if (!heartTexture.loadFromFile("../resources/heart.png")) {
            throw std::runtime_error("Не удалось загрузить текстуру сердца: ../resources/heart.png");
        }
        if (!font.loadFromFile("../resources/font.ttf")) {
            throw std::runtime_error("Не удалось загрузить шрифт: ../resources/font.ttf");
        }
    }

    /**
     * @brief Получить загруженный шрифт
     * @return Константная ссылка на sf::Font
     */
    const sf::Font& getFont() const { return font; }

    /**
     * @brief Получить текстуру иконки жизни
     * @return Константная ссылка на sf::Texture
     */
    const sf::Texture& getHeartTexture() const { return heartTexture; }

    /**
     * @brief Получить размер текстуры сердца
     * @return Размер (ширина, высота) в пикселях
     */
    sf::Vector2u getHeartTextureSize() const { return heartTexture.getSize(); }

private:
    sf::Font    font;             /**< Загруженный шрифт */
    sf::Texture heartTexture;     /**< Текстура для отображения жизней */
};