#include "Map.hpp"

Map::Map() {
}

Map::Map(vector<vector<int>>& map, const std::string& name) 
    : map(map)
    , map_width(map[0].size())
    , map_height(map.size())
    , name(name)
{
    r1.setFillColor(c1);
    r2.setFillColor(c2);
    r3.setFillColor(c3);

    map_buffer = new sf::RenderTexture();
    map_buffer->create(map_width * tile_width, map_height * tile_height);

    for (int j = 0; j < map_height; j++) {
        for (int i = 0; i < map_width; i++) {
            switch (map[j][i]) {
            case 0:
                r2.setPosition(sf::Vector2f(i * tile_width, j * tile_height));
                map_buffer->draw(r2);
                break;
            case 1:
                r1.setPosition(sf::Vector2f(i * tile_width, j * tile_height));
                map_buffer->draw(r1);
                break;
            case 2:
                r3.setPosition(sf::Vector2f(i * tile_width, j * tile_height));
                map_buffer->draw(r3);
                break;
            }
        }
    }

    map_buffer->display();
    map_sprite = sf::Sprite(map_buffer->getTexture());
}

Map::Map(const std::string& filename) {
    fs::path map_file = fs::path(filename);
    std::ifstream in(map_file.string());
    if (in.fail()) {
        throw "Failed to open map file: " + filename;
    }

    {
        // Get width and height:
        std::string line1;
        getline(in, line1);
        vector<std::string> v = regexSearch(line1, "([0-9]+), ?([0-9]+)");
        map_width = std::atoi(v[0].c_str());
        map_height = std::atoi(v[1].c_str());
    }

    {
        // Populate map:
        std::string read_in;
        std::string pattern_single_number = "([0-9]+)[,]?";
        std::string pattern;
        for (int i = 0; i < map_width; i++) pattern.append(pattern_single_number);
        for (int j = 0; j < map_height; j++) {
            map.push_back(vector<int>{});
            getline(in, read_in);
            vector<std::string> row = regexSearch(read_in, pattern);

            for (int i = 0; i <= map_width; i++) {
                map[j].push_back(std::atoi(row[i].c_str()));
            }
        }
    }

    sf::Texture* texture = new sf::Texture();
    fs::path texture_file = map_file.replace_extension(".png");
    if (!texture->loadFromFile(texture_file.string())) {
        std::cout << format("Failed to load texture file {}\n", texture_file.string());
        exit(1);
    }
    sf::Sprite sprite = sf::Sprite(*texture);

    map_buffer = new sf::RenderTexture();
    map_buffer->create(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
    map_buffer->draw(sprite);
    map_buffer->display();

    map_sprite = sf::Sprite(map_buffer->getTexture());

    delete texture;
}

Map::~Map() {
    delete map_buffer;
}

vector<std::string> Map::regexSearch(const std::string& input, const std::string& pattern) {
    vector<std::string> result;
    std::regex r{pattern};
    std::smatch s;
    std::regex_match(input, s, r);
    for (int i = 1; i < s.length(); i++) {
        result.push_back(s[i].str());
    }
    return result;
}

sf::Sprite& Map::getSprite() {
    return map_sprite;
}

int Map::getWidth() {
    return map_width;
}

int Map::getHeight() {
    return map_height;
}

int Map::getTileWidth() {
    return tile_width;
}

int Map::getTileHeight() {
    return tile_height;
}

bool Map::collides(sf::FloatRect rect) {
    sf::Vector2f rect_position = sf::Vector2f(rect.left, rect.top);
    float h_width = (float)rect.width / 2, h_height = (float)rect.height / 2;
    // Check each side:
    sf::Vector2f sides[] = {
        sf::Vector2f(rect_position.x - h_width, rect_position.y),
        sf::Vector2f(rect_position.x + h_width, rect_position.y),
        sf::Vector2f(rect_position.x, rect_position.y - h_height),
        sf::Vector2f(rect_position.x, rect_position.y + h_height)
    };
    for (int i = 0; i < 4; i++) {
        sf::Vector2i tile = sf::Vector2i(sides[i].x / tile_width, sides[i].y / tile_width);
        if (tile.x < 0 || tile.x > map_width || tile.y < 0 || tile.y >= map_height
                       || tile_types[map[tile.y][tile.x]])
        {
            return true;
        }
    }
    return false;
}