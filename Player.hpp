#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>

class Player {
public:
    Player();

    sf::Vector2f getPosition();

    void setPosition(const sf::Vector2f& position);

    sf::RectangleShape& getSprite();

    [[nodiscard]] sf::Vector2f updateMovement(std::unordered_map<sf::Keyboard::Key, int>& keys, double dt);

    void move(sf::Vector2f movement);

    sf::FloatRect getCollisionBox(sf::Vector2f offset = sf::Vector2f(0, 0));
private:
    float player_width = 25, player_height = 25;
    float movement_speed = 120;
    sf::RectangleShape player_sprite = sf::RectangleShape(sf::Vector2f(player_width, player_height));
    sf::Vector2f position;
};