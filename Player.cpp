#include "Player.hpp"

Player::Player() {
    player_texture.loadFromFile(character_texture_file);
    player_sprite = sf::Sprite(player_texture);
    player_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    player_sprite.setOrigin(sf::Vector2f(player_width/2, player_height/2));
    player_sprite.setPosition(sf::Vector2f(100 + player_width/2, 50 + player_height/2));
}

sf::Vector2f Player::getPosition() {
    return position;
}

void Player::setPosition(const sf::Vector2f& position) {
    this->position = position;
    player_sprite.setPosition(position);
}

sf::Sprite& Player::getSprite() {
    return player_sprite;
}

sf::Vector2f Player::updateMovement(std::unordered_map<sf::Keyboard::Key, int>& keys, double dt, float velocity_offset) {
    // movement_speed = 120, velocity_offset = 0.0, -2.0, -4.0, -6.0, ...
    sf::Vector2f movement = sf::Vector2f(0, 0);
    if (keys[sf::Keyboard::Up]) {
        movement.y -= dt * (movement_speed + velocity_offset);
    } else if (keys[sf::Keyboard::Down]) {
        movement.y += dt * (movement_speed + velocity_offset);
    }
    if (keys[sf::Keyboard::Left]) {
        movement.x -= dt * (movement_speed + velocity_offset);
    } else if (keys[sf::Keyboard::Right]) {
        movement.x += dt * (movement_speed + velocity_offset);
    }
    return movement;
}

void Player::move(sf::Vector2f movement) {
    // Calculate direction:
    if (movement.x != 0) {
        facing_direction = movement.x > 0 ? Direction::Right : Direction::Left;
        animation_frame = ((animation_frame % 4) + 1) + 4 * int(facing_direction);
    } else if (movement.y != 0) {
        facing_direction = movement.y > 0 ? Direction::Down : Direction::Up;
        animation_frame = ((animation_frame % 4) + 1) + 4 * int(facing_direction);
    } else {
        animation_frame = 4 * int(facing_direction);
    }

    position += movement;
    player_sprite.setPosition(position);
}

sf::FloatRect Player::getCollisionBox(sf::Vector2f offset) {
    return sf::FloatRect(position + offset, sf::Vector2f(player_width, player_height));
}