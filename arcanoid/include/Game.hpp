#include <SFML/Graphics.hpp>
#include "Block.hpp"
#include "Paddle.hpp"
#include "Bonus.hpp"
#include "Ball.hpp"
#include "ResourceManager.hpp"
class Game {
public:
    Game();
    int run();
    void redrawAll();
    void update(float deltaTime);
    void processInput();
    void checkCollisions();

private:
    int score;
    int lives;
    ResourceManager manager;
    sf::Text scoreText;
    sf::Sprite heartSprite;
    sf::RenderWindow window;
    std::vector<std::unique_ptr<Block>> blocks;
    std::vector<std::unique_ptr<Bonus>> activeBonuses;
    Paddle paddle;
    Ball ball;
};