/*
** EPITECH PROJECT, 2023
** LibraryPacman.cpp
** File description:
** LibraryPacman
*/

#include "ConfigParser.hpp"
#include "LibraryPacman.hpp"
#include "PacmanMap.hpp"

int libraryType = 0;
char const *libraryName = NAME;

arcade::LibraryPacman::LibraryPacman()
{
    ConfigParser getMap;

    _ghosts.push_back(Ghost(arcade::GhostType::FOLLOW, {13, 11}, {{53, 54}, {55, 56}, {51, 52}, {49, 50}}));
    _ghosts.push_back(Ghost(arcade::GhostType::ANTICIPATE, {13, 14}, {{61, 62}, {63, 64}, {59, 60}, {57, 58}}));
    _ghosts.push_back(Ghost(arcade::GhostType::RANDOM, {12, 14}, {{69, 70}, {71, 72}, {67, 68}, {65, 66}}));
    _ghosts.push_back(Ghost(arcade::GhostType::RANDOM, {14, 14}, {{77, 78}, {79, 80}, {75, 76}, {73, 74}}));
    _saveMap = getMap.loadMapFromConfig("./assets/Pacman/PacmanMap.txt");
    _map = _saveMap;
    _gameInfo.score = 0;
    _gameInfo.name = "";
    _beginTime = 0;
    _dtime = -1;
    getNamePlayer();
}

arcade::LibraryPacman::~LibraryPacman()
{
}

void arcade::LibraryPacman::getNamePlayer()
{
    std::ifstream file(".save");

    if (file.is_open())
        file >> _gameInfo.name;
}

bool arcade::LibraryPacman::hasGetAllFood()
{
    for (std::size_t i = 0; i < _map.size(); i++)
    {
        for (std::size_t j = 0; j < _map[i].size(); j++)
        {
            if (_map[i][j] == PacmanMap::GUMS || _map[i][j] == PacmanMap::PACGUMS)
                return false;
        }
    }
    return true;
}

void arcade::LibraryPacman::update(arcade::Event event, double delta_time)
{
    std::size_t nbUpdate = 0;

    if (_dtime == -1)
    {
        _dtime = delta_time;
        return;
    }
    _dtime = delta_time;
    _beginTime += _dtime;
    _pacman.update(_dtime, _map, event);
    _pacman.eatGums(_map, _gameInfo.score, _ghosts);
    nbUpdate = _beginTime / 10 + 1;
    for (std::size_t i = 0; i < _ghosts.size() && i < nbUpdate; i++)
        _ghosts[i].update(_dtime, _map, _pacman.getEntity());
    if (nbUpdate < _ghosts.size())
    {
        for (std::size_t i = nbUpdate; i < _ghosts.size(); i++)
        {
            _ghosts[i].eatable.first = false;
            _ghosts[i].setToDefault();
        }
    }
    _pacman.checkCollision(_ghosts, _map, _saveMap, _gameInfo.score, _beginTime);
    if (hasGetAllFood())
    {
        _pacman.resetAndIncrease();
        for (std::size_t i = 0; i < _ghosts.size(); i++)
            _ghosts[i].resetAndIncrease();
        _map = _saveMap;
        _beginTime = 0;
    }
}

arcade::Entity arcade::LibraryPacman::createMapEntity
                            (int x, int y, int id, const std::string &type)
{
    struct Entity entity;

    entity.id = id;
    entity.direction = {0, 0};
    entity.display = true;
    entity.pos = {x, y};
    entity.type = type;
    return entity;
}

arcade::Game &arcade::LibraryPacman::getGameEntity()
{
    _gameInfo.entity.clear();
    for (std::size_t i = 0; i < _ghosts.size(); i++)
        _gameInfo.entity.push_back(_ghosts[i].getEntity());
    _gameInfo.entity.push_back(_pacman.getEntity());
    _gameInfo.map.clear();
    for (std::size_t i = 0; i < _map.size(); i++)
    {
        for (std::size_t j = 0; j < _map[i].size() ; j++)
        {
            _gameInfo.map.push_back(createMapEntity(j, i, _map[i][j], ""));
        }
    }
    return _gameInfo;
}

const std::pair<int, int> arcade::LibraryPacman::getNextLib() const
{
    return {-1, -1};
}

const std::string arcade::LibraryPacman::getAssetPath() const
{
    return "./assets/Pacman";
}

const std::pair<int, int> arcade::LibraryPacman::getMapSize() const
{
    return {_map[0].size(), _map.size()};
}

extern "C" arcade::LibraryPacman *entryPoint()
{
    return new arcade::LibraryPacman;
}
