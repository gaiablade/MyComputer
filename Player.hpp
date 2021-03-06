#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <fmt/core.h>

#include "Sword.hpp"

using fmt::format;

enum class Direction {
    Down = 0, Right, Up, Left
};

class Player {
public:
    Player();

    sf::Vector2f getPosition();

    void setPosition(const sf::Vector2f& position);

    sf::Sprite& getSprite();

    [[nodiscard]] sf::Vector2f updateMovement(std::unordered_map<sf::Keyboard::Key, int>& keys, double dt, float velocity_offset = 0);

    void move(sf::Vector2f movement);

    sf::FloatRect getCollisionBox(sf::Vector2f offset = sf::Vector2f(0, 0));
private:
    float player_width = 31.5, player_height = 31.5;
    float movement_speed = 120;
    sf::Texture player_texture;
    sf::Sprite player_sprite;
    sf::Vector2f position;
    Direction facing_direction = Direction::Down;
    //const std::string character_texture_file = "Images/character1-Sheet.png";
    const std::string character_texture_file = "Images/Sprite-0003.png";
    int animation_frame = 0;
};