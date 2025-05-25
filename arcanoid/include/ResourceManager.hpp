#include <SFML/Graphics.hpp>
class ResourceManager {
public:
    ResourceManager() {
        if (!heartTexture.loadFromFile("../resources/heart.png")) {
            throw std::runtime_error("Cannot load font: ../resources/heart.png");
        }

        if (!font.loadFromFile("../resources/font.ttf")) {
            throw std::runtime_error("Cannot load font: ../resources/font.ttf");
        }
    }

    const sf::Font& getFont() { return font; }
    const sf::Texture& getHeartTexture() {  return heartTexture; }
    sf::Vector2u getHeartTextureSize() { return heartTexture.getSize(); }
private:
    sf::Font font;
    sf::Texture heartTexture;
};