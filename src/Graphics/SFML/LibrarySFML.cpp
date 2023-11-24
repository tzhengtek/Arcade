/*
** EPITECH PROJECT, 2023
** Library.cpp
** File description:
** Library
*/

#include <iostream>
#include <filesystem>
#include "ConfigParser.hpp"
#include "LibrarySFML.hpp"

int libraryType = 1;
char const *libraryName = NAME;

arcade::LibrarySFML::LibrarySFML()
{
    _window.create(sf::VideoMode(WIDTH, HEIGHT), "Window", sf::Style::Titlebar | sf::Style::Close);
    if (!_font.loadFromFile("./assets/fonts/ARCADECLASSIC.TTF"))
        throw Error::InitSDLError("Couldn't open ./assets/fonts/ARCADECLASSIC.TTF");
    _window.setFramerateLimit(60);
}

arcade::LibrarySFML::~LibrarySFML()
{
    _window.close();
}

arcade::Event arcade::LibrarySFML::getEvent(arcade::Game &game)
{
    (void) game;
    sf::Event event;

    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            return arcade::Event::QUIT;
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Up)
                return arcade::Event::UP;
            if (event.key.code == sf::Keyboard::Down)
                return arcade::Event::DOWN;
            if (event.key.code == sf::Keyboard::Right)
                return arcade::Event::RIGHT;
            if (event.key.code == sf::Keyboard::Left)
                return arcade::Event::LEFT;
            if (event.key.code == sf::Keyboard::M)
                return arcade::Event::NEXT_GAME;
            if (event.key.code == sf::Keyboard::P)
                return arcade::Event::NEXT_GRAPHIC;
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            game.mouse_pos = {sf::Mouse::getPosition(_window).x, sf::Mouse::getPosition(_window).y};
            return arcade::Event::MOUSE_CLICK;
        }
    }
    return arcade::Event::NOTHING;
}

void arcade::LibrarySFML::displayText(const std::string &text, sf::Color color, std::pair<float, float> pos)
{
    sf::Text blockText;
    blockText.setFont(_font);
    blockText.setPosition({pos.first, pos.second});
    blockText.setString(text);
    blockText.setCharacterSize(FONT);
    blockText.setFillColor(color);
    _window.draw(blockText);
}

void arcade::LibrarySFML::renderElement(const struct Game &gameEntity)
{
    sf::RectangleShape rect;
    std::pair<int, int> size = {WIDTH / _mapSize.first, WIDTH / _mapSize.first};
    std::string scoreStr = "Score:" + std::to_string(gameEntity.score);

    if (size.second * gameEntity.map.size() > WIDTH)
        size = {WIDTH / _mapSize.second, WIDTH / _mapSize.second};
    _window.clear(sf::Color::Black);

    for (std::size_t i = 0; i < gameEntity.map.size(); i++)
    {
        if (gameEntity.map[i].display &&
                            _rects.find(gameEntity.map[i].id) != _rects.end())
        {
            rect = _rects[gameEntity.map[i].id];
            rect.setPosition(gameEntity.map[i].pos.first * size.first,
                            gameEntity.map[i].pos.second * size.second);
            rect.setSize(sf::Vector2f(size.first, size.second));
            _window.draw(rect);
        }
    }
    for (std::size_t i = 0; i < gameEntity.entity.size(); i++)
    {
        float posX = gameEntity.entity[i].pos.first * size.first;
        float posY = gameEntity.entity[i].pos.second * size.second;
        if (gameEntity.entity[i].type.substr(0, 5) == "text_")
        {
            displayText(gameEntity.entity[i].type.substr(5), sf::Color::White, {posX * _mapSize.first, posY * _mapSize.second});
            _window.draw(rect);
            continue;
        }
        if (gameEntity.entity[i].display && _rects.find(gameEntity.entity[i].id) != _rects.end())
        {
            rect = _rects[gameEntity.entity[i].id];
            rect.setSize(sf::Vector2f(size.first, size.second));
            rect.setPosition(posX, posY);
            _window.draw(rect);
        }
    }
    if (gameEntity.score != static_cast<std::size_t>(-1))
    {
        std::string name = "Player:" + gameEntity.name;
        displayText(scoreStr, sf::Color::White, {20, WIDTH});
        displayText(name, sf::Color::White, {WIDTH - (name.length() * FONT), WIDTH});
    }
    _window.display();
}

void arcade::LibrarySFML::setMapSize(std::pair<int, int> mapSize)
{
    _mapSize = mapSize;
}

void arcade::LibrarySFML::setAssetPath(const std::string &path)
{
    ConfigParser parser;
    std::string filepath;
    std::vector<std::map<std::string, std::string>> parsedConfig;
    bool foundConfig = false;
    bool foundPng = false;
    sf::RectangleShape rect;
    sf::IntRect textRect;
    int index = 0;

    if (path == "./assets/Menu")
        return;

    try
    {
        for(std::filesystem::directory_entry const &dirEntry : std::filesystem::directory_iterator(path))
        {
            if (!dirEntry.is_directory() && dirEntry.path().filename().string().find("Textures") != std::string::npos)
            {
                parsedConfig = parser.loadTexturesFromConfig(dirEntry.path());
                foundConfig = true;
            }
            if (!dirEntry.is_directory() && dirEntry.path().filename().string().find(".png") != std::string::npos)
            {
                _texture.loadFromFile(dirEntry.path());
                foundPng = true;
            }
        }
        if (!foundConfig)
            throw Error::BadConfigFileError("Unable to open or find the config file in \"" + path + "\"");
        if (!foundPng)
            throw Error::BadConfigFileError("Unable to open or find the png file in \"" + path + "\"");
    }
    catch(std::filesystem::filesystem_error &e)
    {
        throw Error::BadConfigFileError("Unable to open or find \"" + path + "\"");
    }
    rect.setTexture(&_texture);
    for (size_t i = 0; i < parsedConfig.size(); i++)
    {
        index = stoi(parsedConfig[i]["id"]);
        rect.setTextureRect(sf::IntRect(stoi(parsedConfig[i]["pos_x"]),
                                        stoi(parsedConfig[i]["pos_y"]),
                                        stoi(parsedConfig[i]["width"]),
                                        stoi(parsedConfig[i]["height"])));
        _rects[index] = rect;
    }
}

extern "C"
{
    arcade::LibrarySFML *entryPoint()
    {
        return new arcade::LibrarySFML;
    }
}
