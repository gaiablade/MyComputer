#include <filesystem>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "Player.hpp"

namespace fs = std::filesystem;

void updateInput(std::unordered_map<sf::Keyboard::Key, int>& keys) {
    for (auto& [key, value] : keys) {
        if (sf::Keyboard::isKeyPressed(key)) {
            value++;
        } else {
            value = 0;
        }
    }
}

int main() {
    sf::Vector2i windowSize{1000, 750};
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "MyComputer");
    window.setFramerateLimit(60);

    // Game stuff:
    // Initialize Map:
    std::vector<std::vector<int>> map_data = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        {1, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    // Initialize Player:
    Player player = Player();
    player.setPosition(sf::Vector2f(400, 500));

    // Initialize Map:
    Map map{"Maps/map2.mf"};
    
    // Set view:
    sf::View view;

    // Keys:
    std::unordered_map<sf::Keyboard::Key, int> keys{
        {sf::Keyboard::Up, 0}, {sf::Keyboard::Down, 0}, {sf::Keyboard::Right, 0}, {sf::Keyboard::Left, 0},
    };

    sf::Font font;
    font.loadFromFile("Fonts/VT323-Regular.ttf");

    fs::path current_directory = fs::current_path();

    sf::Text text = sf::Text(current_directory.relative_path().string(), font);
    text.setFillColor(sf::Color::White);

    sf::Clock clock;

    while (window.isOpen()) {
        // Update delta-time
        double dt = clock.getElapsedTime().asSeconds();
        clock.restart();

        // Poll events:
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        updateInput(keys);
        auto movement = player.updateMovement(keys, dt);

        auto movementX = sf::Vector2f(movement.x, 0);
        auto movementY = sf::Vector2f(0, movement.y);

        sf::Vector2f movement_offsets_X[] = {
            sf::Vector2f(0, -1),
            sf::Vector2f(0, -2),
            sf::Vector2f(0, -3),
            sf::Vector2f(0, -4),
            sf::Vector2f(0, 1),
            sf::Vector2f(0, 2),
            sf::Vector2f(0, 3),
            sf::Vector2f(0, 4),
        };

        sf::Vector2f movement_offsets_Y[] = {
            sf::Vector2f(-1, 0),
            sf::Vector2f(1, 0),
        };

        // Check collisions and move:
        {
            float velocity_offset = -1.0;
            while (map.collides(player.getCollisionBox(movementX)) && movementX != sf::Vector2f(0, 0)) {
                movementX = sf::Vector2f(player.updateMovement(keys, dt, velocity_offset).x, 0);
                velocity_offset -= 1.0;
            }
            player.move(movementX);
        }
        {
            float velocity_offset = -1.0;
            while (map.collides(player.getCollisionBox(movementY)) && movementY != sf::Vector2f(0, 0)) {
                movementY = sf::Vector2f(0, player.updateMovement(keys, dt, velocity_offset).y);
                velocity_offset -= 1.0;
            }
            player.move(movementY);
        }
        
        // Update View:
        const float cameraWidth = 600, cameraHeight = cameraWidth / 1.3333333333;
        auto pos = player.getPosition();
        float cameraX = pos.x - cameraWidth/2, cameraY = pos.y - cameraHeight/2;
        if (cameraX + cameraWidth > map.getWidth() * map.getTileWidth()) {
            cameraX = map.getWidth() * map.getTileWidth() - cameraWidth;
        } if (cameraX < 0) {
            cameraX = 0;
        }
        if (cameraY + cameraHeight > map.getHeight() * map.getTileHeight()) {
            cameraY = map.getHeight() * map.getTileHeight() - cameraHeight;
        } if (cameraY < 0) {
            cameraY = 0;
        }

        //view.reset(sf::FloatRect(player.getPosition().x - 600/2, player.getPosition().y - 450/2, 600, 450));
        view.reset(sf::FloatRect(cameraX, cameraY, cameraWidth, cameraHeight));
        window.setView(view);

        // Render:
        window.clear();
        window.draw(map.getSprite());
        window.draw(player.getSprite());

        window.setView(sf::View());
        window.draw(text);

        window.display();
    }
}