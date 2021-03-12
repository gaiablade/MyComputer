#include <iostream>
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "Player.hpp"

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
    sf::RenderWindow window(sf::VideoMode(800, 600), "MyComputer");
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
    player.setPosition(sf::Vector2f(350, 100));

    // Initialize Map:
    Map map{"Maps/map1.mf"};
    
    // Set view:
    sf::View view;

    // Keys:
    std::unordered_map<sf::Keyboard::Key, int> keys{
        {sf::Keyboard::Up, 0}, {sf::Keyboard::Down, 0}, {sf::Keyboard::Right, 0}, {sf::Keyboard::Left, 0},
    };

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

        // Check collisions and move:
        {
            if (!map.collides(player.getCollisionBox(sf::Vector2f(movement.x, 0)))) {
                player.move(sf::Vector2f(movement.x, 0));
            }
            if (!map.collides(player.getCollisionBox(sf::Vector2f(0, movement.y)))) {
                player.move(sf::Vector2f(0, movement.y));
            }
        }
        
        // Update View:
        view.reset(sf::FloatRect(player.getPosition().x - 300, player.getPosition().y - 225, 600, 450));
        window.setView(view);

        // Render:
        window.clear();
        window.draw(map.getSprite());
        window.draw(player.getSprite());
        window.display();
    }
}