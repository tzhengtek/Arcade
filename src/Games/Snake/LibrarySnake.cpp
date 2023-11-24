/*
** EPITECH PROJECT, 2023
** Library.cpp
** File description:
** Library
*/

#include <iostream>
#include <algorithm>
#include "LibrarySnake.hpp"

int libraryType = 0;
char const *libraryName = NAME;

arcade::LibrarySnake::LibrarySnake()
{
    initGameEntity();
    initGame();
}

arcade::LibrarySnake::~LibrarySnake()
{
}

void arcade::LibrarySnake::getNamePlayer()
{
    std::ifstream file(".save");

    if (file.is_open())
        file >> _gameInfo.name;
}

struct arcade::Entity arcade::LibrarySnake::createEntity
                (std::pair<double, double> direction, std::size_t x, std::size_t y, int id, const std::string &type)
{
    struct Entity entity;

    entity.id = id;
    entity.direction = direction;
    entity.display = true;
    entity.pos = {x, y};
    entity.speed = 1;
    entity.type = type;
    return entity;
}

void arcade::LibrarySnake::initGameEntity()
{
    ConfigParser configParser;
    std::vector<arcade::Entity> parsedConfig;
    bool file_found = false;
    std::string new_path = "./assets/Snake";
    try {
        for(std::filesystem::directory_entry const &dir_entry : std::filesystem::directory_iterator(new_path)) {
            if (dir_entry.is_directory() == false) {
                _entities = configParser.loadEntitiesFromConfig(dir_entry.path());
                file_found = true;
            }
        }
        if (!file_found)
            throw Error::BadConfigFileError("Unable to open or find Snake config file in \"" + new_path + "\"");
    } catch(std::filesystem::filesystem_error &e) {
        throw Error::BadConfigFileError("Unable to open or find \"" + new_path + "\"");
    }
}

void arcade::LibrarySnake::initGame()
{
    resetGame();
    std::size_t sizeMap = 30;
    std::size_t startX = rand() % sizeMap;
    std::size_t startY = rand() % (sizeMap - 8) + 5;

    _sizeMapX = sizeMap;
    _sizeMapY = sizeMap;
    _direction = arcade::Event::RIGHT;
    _lastEvent = _direction;
    _axisDirectionX = true;
    _axisDirectionY = !_axisDirectionX;
    _size = 5;
    _lastTime = 0;
    _countFruit = 0;
    _enlargeBody = false;
    _fruitPos = {rand() % sizeMap, rand() % sizeMap};
    _gameInfo.score = 0;
    _gameInfo.entity.push_back(createEntity({1, 0}, startX, startY - 1, 4, "Snake"));
    for (std::size_t i = 1; i < _size; i++)
        _gameInfo.entity.push_back(createEntity({1, 0}, startX, startY - 1, 14, "Snake"));
    _gameInfo.map.push_back(createEntity({0, 0}, _fruitPos.first, _fruitPos.second, 16, "Fruit"));
    getNamePlayer();
}

void arcade::LibrarySnake::resetGame()
{
    _gameInfo.entity.clear();
    _gameInfo.map.clear();
}

bool arcade::LibrarySnake::changeDirection
(arcade::Event event, arcade::Event lateralDir1, arcade::Event lateralDir2, bool check)
{
    if (_axisDirectionX == check && (event == lateralDir1 || event == lateralDir2))
    {
        _direction = event;
        _axisDirectionY = _axisDirectionX;
        _axisDirectionX = !check;
        return true;
    }
    return false;
}

void arcade::LibrarySnake::checkTouchBorderMap()
{
    if (_gameInfo.entity[0].pos.first == -1 ||
                                        _gameInfo.entity[0].pos.second == -1)
        (_gameInfo.entity[0].pos.first == -1) ?
            _gameInfo.entity[0].pos.first = _sizeMapX - 1 :
            _gameInfo.entity[0].pos.second = _sizeMapX - 1;
    if (_gameInfo.entity[0].pos.first == _sizeMapX ||
                                _gameInfo.entity[0].pos.second == _sizeMapY)
        (_gameInfo.entity[0].pos.first == _sizeMapX) ?
            _gameInfo.entity[0].pos.first = 0 :
            _gameInfo.entity[0].pos.second = 0;
}

bool checkTouchBody(std::pair<double, double> nextPos,
                            std::vector<struct arcade::Entity> playerPos)
{
    for (std::size_t i = 1; i < playerPos.size(); i++)
    {
        if (playerPos[i].pos == nextPos)
            return true;
    }
    return false;
}

bool arcade::LibrarySnake::moveSnake()
{
    struct Entity nextPos = _gameInfo.entity[0];

    if (_direction == arcade::Event::RIGHT)
    {
        nextPos.pos.first++;
        nextPos.direction = {1, 0};
        nextPos.id = 4;
    }
    if (_direction == arcade::Event::LEFT)
    {
        nextPos.pos.first--;
        nextPos.direction = {-1, 0};
        nextPos.id = 2;
    }
    if (_direction == arcade::Event::DOWN)
    {
        nextPos.pos.second++;
        nextPos.direction = {0, 1};
        nextPos.id = 3;
    }
    if (_direction == arcade::Event::UP)
    {
        nextPos.pos.second--;
        nextPos.direction = {0, -1};
        nextPos.id = 1;
    }
    if (checkTouchBody(nextPos.pos, _gameInfo.entity))
        return false;
    for (std::size_t i = _gameInfo.entity.size() - 1; i > 0; i--)
    {
        int saveId = _gameInfo.entity[i].id;
        _gameInfo.entity[i] = _gameInfo.entity[i - 1];
        if (i == 1)
            _gameInfo.entity[i].id = saveId;
    }
    _gameInfo.entity[0] = nextPos;
    return true;
}

bool arcade::LibrarySnake::isSamePos()
{
    for (std::size_t i = 0; i < _gameInfo.entity.size(); i++)
    {
        if (_gameInfo.entity[i].pos == _fruitPos)
            return true;
    }
    return false;
}

void arcade::LibrarySnake::checkEatFruit()
{
    if (_gameInfo.entity[0].pos == _fruitPos)
    {
        _enlargeBody = true;
        _enlargePos = _gameInfo.entity[_gameInfo.entity.size() - 1].pos;
        _fruitPos = {rand() % _sizeMapX, rand() % _sizeMapX};
        _gameInfo.score++;
        while (isSamePos())
            _fruitPos = {rand() % _sizeMapX, rand() % _sizeMapX};
        _gameInfo.map[0] = createEntity({0, 0}, _fruitPos.first, _fruitPos.second, 16, "Fruit");
    }
}

void arcade::LibrarySnake::enlargeBodySnake()
{
    if (_enlargeBody)
    {
        if (_gameInfo.entity[_gameInfo.entity.size() - 1].pos != _enlargePos)
        {
            _gameInfo.entity.push_back(
                createEntity(_gameInfo.entity[_gameInfo.entity.size() - 1].direction,
                _enlargePos.first, _enlargePos.second,
                _gameInfo.entity[_gameInfo.entity.size() - 1].id, "Snake"));
            _enlargeBody = false;
        }
    }
}

bool comparePair(std::pair<double, double> pair1, std::pair<double, double> pair2)
{
    return pair1.first == pair2.first && pair1.second == pair2.second;
}

void arcade::LibrarySnake::checkRotateBody
(std::pair<double, double> rotation1, std::pair<double, double> rotation2, int i, int newId, int opposite)
{
    std::pair<double, double> rotation1b = {opposite * rotation1.second, opposite * rotation1.first};
    std::pair<double, double> rotation2b = {opposite * rotation2.second, opposite * rotation2.first};
    bool checkDir1 = comparePair(_gameInfo.entity[i - 1].direction, rotation1);
    bool checkDir2 = comparePair(_gameInfo.entity[i + 1].direction, rotation2);
    bool checkDir1b = comparePair(_gameInfo.entity[i - 1].direction, rotation1b);
    bool checkDir2b = comparePair(_gameInfo.entity[i + 1].direction, rotation2b);
    if ((checkDir1 && checkDir2) || (checkDir1b && checkDir2b))
        _gameInfo.entity[i].id = newId;
}

void arcade::LibrarySnake::uniqueDirectionBody(std::pair<double, double> direction, int i, int newId)
{
    std::pair<double, double> dir1 = {-direction.first, -direction.second};
    bool checkSameDir1 = comparePair(_gameInfo.entity[i - 1].direction, direction);
    bool checkSameDir2 = comparePair(_gameInfo.entity[i + 1].direction, direction);
    bool checkSameDir1Opposite = comparePair(_gameInfo.entity[i - 1].direction, dir1);
    bool checkSameDir2Opposite = comparePair(_gameInfo.entity[i + 1].direction, dir1);
    if ((checkSameDir1 && checkSameDir2) || (checkSameDir1Opposite && checkSameDir2Opposite))
        _gameInfo.entity[i].id = newId;
}

void arcade::LibrarySnake::checkDirectionBody()
{
    std::size_t i = 1;
    for (; i < _gameInfo.entity.size() - 1; i++)
    {
        checkRotateBody({1, 0}, {0, -1}, i, 10, 1);
        checkRotateBody({-1, 0}, {0, -1}, i, 11, -1);
        checkRotateBody({-1, 0}, {0, 1}, i, 12, 1);
        checkRotateBody({1, 0}, {0, 1}, i, 13, -1);
        uniqueDirectionBody({1, 0}, i, 14);
        uniqueDirectionBody({0, 1}, i, 15);
    }
    if (comparePair(_gameInfo.entity[i].direction, {1, 0}))
        _gameInfo.entity[i].id = 9;
    if (comparePair(_gameInfo.entity[i].direction, {0, 1}))
        _gameInfo.entity[i].id = 6;
    if (comparePair(_gameInfo.entity[i].direction, {-1, 0}))
        _gameInfo.entity[i].id = 7;
    if (comparePair(_gameInfo.entity[i].direction, {0, -1}))
        _gameInfo.entity[i].id = 8;
}

void arcade::LibrarySnake::update(arcade::Event event, double delta_time)
{
    _lastTime += delta_time;
    if (event != arcade::Event::NOTHING)
        _lastEvent = event;
    if (_lastTime > UPDATE)
    {
        if (_lastEvent != _direction) {
            if (!changeDirection(_lastEvent, arcade::Event::DOWN, arcade::Event::UP, true))
                changeDirection(_lastEvent, arcade::Event::LEFT, arcade::Event::RIGHT, false);
        }
        if (!moveSnake())
            initGame();
        checkTouchBorderMap();
        checkEatFruit();
        enlargeBodySnake();
        _lastTime = 0;
        checkDirectionBody();
    }
}

struct arcade::Game &arcade::LibrarySnake::getGameEntity()
{
    return _gameInfo;
}

const std::pair<int, int> arcade::LibrarySnake::getNextLib() const
{
    return {-1, -1};
}

const std::string arcade::LibrarySnake::getAssetPath() const
{
    return "./assets/Snake";
}

const std::pair<int, int> arcade::LibrarySnake::getMapSize() const
{
    return {_sizeMapX, _sizeMapY};
}

extern "C" arcade::LibrarySnake *entryPoint()
{
    return new arcade::LibrarySnake;
}
