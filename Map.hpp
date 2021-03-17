#pragma once

#include <exception>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <fmt/core.h>
#include <SFML/Graphics.hpp>

#include "RegexSearch.hpp"
#include "TileAttributes.hpp"

namespace fs = std::filesystem;
using std::vector;
using fmt::format;

class Map {
public:
    Map();

    Map(vector<vector<vector<int>>>& map, const std::string& name = "");

    Map(const std::string& filename);

    Map(const Map&) = default;

    Map& operator=(const Map&) = default;

    ~Map();

    sf::Sprite& getSprite();

    int getWidth();

    int getHeight();

    int getTileWidth();

    int getTileHeight();

    bool collides(sf::FloatRect rect);

private:
    vector<vector<vector<int>>> layers;
    int map_width, map_height;
    int tile_width = 32, tile_height = 32;
    sf::Color c1 = sf::Color(0x000000FF);
    sf::Color c2 = sf::Color(0x00FF00FF);
    sf::Color c3 = sf::Color(0x948248FF);
    sf::RectangleShape r1 = sf::RectangleShape(sf::Vector2f(tile_width, tile_height));
    sf::RectangleShape r2 = sf::RectangleShape(sf::Vector2f(tile_width, tile_height));
    sf::RectangleShape r3 = sf::RectangleShape(sf::Vector2f(tile_width, tile_height));
    sf::RenderTexture* map_buffer{};
    sf::Sprite map_sprite{};
    std::string name;
    std::unordered_map<int, TileAttributes> tile_types{
        {0, {.solid = false}},
        {1, {.solid = false}},
        {2, {.solid = true}},
        {3, {.solid = true}},
        {4, {.solid = true}},
        {5, {.solid = false}},
        {6, {.solid = true}},
        {7, {.solid = true}},
        {8, {.solid = false}},
        {16, {.solid = false}}
    };
};
