#include "Player.hpp"

Player::Player() {
    player_sprite.setOrigin(sf::Vector2f(player_width/2, player_height/2));
    player_sprite.setPosition(sf::Vector2f(100 + player_width/2, 50 + player_height/2));
    player_sprite.setFillColor(sf::Color(0x0000FFFF));
}

sf::Vector2f Player::getPosition() {
    return position;
}

void Player::setPosition(const sf::Vector2f& position) {
    this->position = position;
    player_sprite.setPosition(position);
}

sf::RectangleShape& Player::getSprite() {
    return player_sprite;
}

sf::Vector2f Player::updateMovement(std::unordered_map<sf::Keyboard::Key, int>& keys, double dt) {
    sf::Vector2f movement = sf::Vector2f(0, 0);
    if (keys[sf::Keyboard::Up]) {
        movement.y -= dt * movement_speed;
    } else if (keys[sf::Keyboard::Down]) {
        movement.y += dt * movement_speed;
    }
    if (keys[sf::Keyboard::Left]) {
        movement.x -= dt * movement_speed;
    } else if (keys[sf::Keyboard::Right]) {
        movement.x += dt * movement_speed;
    }
    return movement;
}

void Player::move(sf::Vector2f movement) {
    position += movement;
    player_sprite.setPosition(position);
}

sf::FloatRect Player::getCollisionBox(sf::Vector2f offset) {
    return sf::FloatRect(position.x + offset.x, position.y + offset.y, player_width, player_height);
}