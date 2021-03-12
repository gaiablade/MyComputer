#pragma once

#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <unordered_map>
#include <vector>
#include <fmt/core.h>
#include <SFML/Graphics.hpp>

namespace fs = std::filesystem;
using std::vector;
using fmt::format;

class Map {
public:
    Map();

    Map(vector<vector<int>>& map, const std::string& name = "");

    Map(const std::string& filename);

    Map(const Map&) = default;

    Map& operator=(const Map&) = default;

    ~Map();

    static vector<std::string> regexSearch(const std::string& input, const std::string& pattern);

    sf::Sprite& getSprite();

    int getWidth();

    int getHeight();

    int getTileWidth();

    int getTileHeight();

    bool collides(sf::FloatRect rect);

private:
    vector<vector<int>> map;
    int map_width, map_height;
    int tile_width = 50, tile_height = 50;
    sf::Color c1 = sf::Color(0x000000FF);
    sf::Color c2 = sf::Color(0x00FF00FF);
    sf::Color c3 = sf::Color(0x948248FF);
    sf::RectangleShape r1 = sf::RectangleShape(sf::Vector2f(tile_width, tile_height));
    sf::RectangleShape r2 = sf::RectangleShape(sf::Vector2f(tile_width, tile_height));
    sf::RectangleShape r3 = sf::RectangleShape(sf::Vector2f(tile_width, tile_height));
    sf::RenderTexture* map_buffer{};
    sf::Sprite map_sprite{};
    std::string name;
    std::unordered_map<int, bool> tile_types{
        {1, false}, {2, true}, {3, false}, {4, true}
    };
};
