/*
** EPITECH PROJECT, 2023
** PacEntity.cpp
** File description:
** PacEntity
*/

#include <cmath>
#include "LibraryPacman.hpp"
#include "PacmanMap.hpp"

arcade::APacEntity::APacEntity()
{
    _entity.direction = {0, 0};
    _entity.display = true;
    _entity.speed = 3;
    _snapRange = 0.07;
    _nextDirection = {0, 0};
}

arcade::APacEntity::~APacEntity()
{
}

arcade::Entity &arcade::APacEntity::getEntity()
{
    return _entity;
}

double &arcade::APacEntity::getSnapRange()
{
    return _snapRange;
}

std::pair<double, double> arcade::APacEntity::getGridPosition(std::pair<double, double> position)
{
    return std::pair<double, double>(round(position.first), round(position.second));
}

void arcade::APacEntity::applyMovement(double dtime)
{
    std::pair<double, double> next;

    _entity.pos.first += _entity.direction.first * _entity.speed * dtime;
    _entity.pos.second += _entity.direction.second * _entity.speed * dtime;
    next = getNextCell(_entity.pos, _entity.direction);
    if (next.first < 0)
    {
        if (next.first < -1)
            _entity.pos.first = _map[0].size();
        return;
    }
    if (next.first > _map[0].size() - 1)
    {
        if (next.first > _map[0].size())
            _entity.pos.first = -1;
        return;
    }
    if (_map[next.second][next.first] <= PacmanMap::PAC_WALLS && _map[next.second][next.first] != 0)
    {
        _entity.pos = getGridPosition(_entity.pos);
        _entity.direction = {0, 0};
    }
}

std::pair<double, double> getFlooredPosition(std::pair<double, double> position, std::pair<double, double> dir)
{
    std::pair<double, double> flooredPosition = position;

    if (dir.first > 0)
        flooredPosition.first = floor(position.first);
    if (dir.second > 0)
        flooredPosition.second = floor(position.second);
    if (dir.first < 0)
        flooredPosition.first = floor(position.first + 1);
    if (dir.second < 0)
        flooredPosition.second = floor(position.second + 1);
    return flooredPosition;
}

std::pair<double, double> arcade::APacEntity::getNextCell(std::pair<double, double> pos, std::pair<double, double> dir)
{
    std::pair<double, double> nextCell = getFlooredPosition(pos, dir);

    nextCell.first += dir.first;
    nextCell.second += dir.second;
    return nextCell;
}

std::pair<double, double> eventToDir(arcade::Event event)
{
    if (event == arcade::Event::UP)
        return {0, -1};
    if (event == arcade::Event::DOWN)
        return {0, 1};
    if (event == arcade::Event::LEFT)
        return {-1, 0};
    if (event == arcade::Event::RIGHT)
        return {1, 0};
    return {0, 0};
}

bool arcade::APacEntity::canTurn(std::pair<double, double> dir)
{
    std::pair<double, double> next = getGridPosition(_entity.pos);

    if (!isSnapable(dir))
        return false;
    next.first += dir.first;
    next.second += dir.second;
    if (next.first > _map[0].size() - 1 || next.first < 0)
    {
        return false;
    }
    if (_map[next.second][next.first] <= PacmanMap::PAC_WALLS && _map[next.second][next.first] != 0)
        return false;
    return true;
}

void arcade::APacEntity::changeDirection(arcade::Event event)
{
    std::pair<double, double> tmp = eventToDir(event);

    if (tmp.first != 0 || tmp.second != 0)
        _nextDirection = tmp;
    if ((_nextDirection.first != _entity.direction.first || _nextDirection.second != _entity.direction.second) &&
        (_nextDirection.first != 0 || _nextDirection.second != 0))
    {
        if (canTurn(_nextDirection))
        {
            snapPosition(_nextDirection);
            _entity.direction = _nextDirection;
            _nextDirection = {0, 0};
        }
    }
}

bool arcade::APacEntity::isSnapable(std::pair<double, double> dir)
{
    std::pair<double, double> cmp;
    std::pair<double, double> next = getNextCell(_entity.pos, _entity.direction);

    if ((dir.first < 0 && _entity.direction.first > 0) ||
        (dir.first > 0 && _entity.direction.first < 0) ||
        (dir.second < 0 && _entity.direction.second > 0) ||
        (dir.second > 0 && _entity.direction.second < 0))
        return true;

    if (dir.second != 0)
        cmp.first = std::abs(_entity.pos.first - next.first);
    if (dir.first != 0)
        cmp.second = std::abs(_entity.pos.second - next.second);
    if (cmp.first < _snapRange && cmp.second < _snapRange)
        return true;
    return false;
}

void arcade::APacEntity::snapPosition(std::pair<double, double> dir)
{
    if (dir.second != 0)
        _entity.pos.first = round(_entity.pos.first);
    if (dir.first != 0)
        _entity.pos.second = round(_entity.pos.second);
}

arcade::PacMan::PacMan()
{
    _entity.pos = {13.5, 23};
    // Player ID vaut 1
    _entity.id = 42;
    _entity.type = "Pacman";
    _entity.speed = 4.5;
    _snapRange = 0.09;
    _lastAnim = 0;
    _animState = 0;
}

arcade::PacMan::~PacMan()
{
}

void arcade::PacMan::update(double dtime, std::vector<std::vector<int>> &map, arcade::Event &event)
{
    _map = map;
    changeDirection(event);
    applyMovement(dtime);
    updateId(dtime);
}

void arcade::PacMan::reset()
{
    _entity.pos = {13.5, 23};
    _entity.direction = {0, 0};
    _entity.display = true;
    _entity.speed = 4.5;
    _snapRange = 0.1;
    _nextDirection = {0, 0};
    _lastAnim = 0;
    _animState = 0;
}

void arcade::PacMan::resetAndIncrease()
{
    _entity.direction = {0, 0};
    _entity.pos = {13.5, 23};
    _entity.speed += 0.5;
    _nextDirection = {0, 0};
    _snapRange += 0.01;
    _lastAnim = 0;
    _animState = 0;
}

void arcade::PacMan::checkCollision(std::vector<Ghost> &ghosts, std::vector<std::vector<int>> &map,
                                    std::vector<std::vector<int>> &saveMap, long unsigned int &score,
                                    double &beginTime)
{
    Entity entity;

    for (std::size_t i = 0; i < ghosts.size(); i++)
    {
        entity = ghosts[i].getEntity();
        if (_entity.pos.first < entity.pos.first + 1 && _entity.pos.first + 1 > entity.pos.first &&
            _entity.pos.second < entity.pos.second + 1 && _entity.pos.second + 1 > entity.pos.second)
        {
            if (ghosts[i].eatable.first == false && ghosts[i].alive == true)
            {
                reset();
                map = saveMap;
                score = 0;
                resetGhosts(ghosts);
                beginTime = 0;
                return;
            }
            if (ghosts[i].eatable.first == true && ghosts[i].alive == true)
            {
                ghosts[i].alive = false;
                ghosts[i].eatable.first = false;
                ghosts[i].getEntity().speed = 15;
                ghosts[i].getSnapRange() = 0.2;
                score += 200;
            }
        }
    }
}

void arcade::PacMan::resetGhosts(std::vector<Ghost> &ghosts)
{
    for (std::size_t i = 0; i < ghosts.size(); i++)
        ghosts[i].reset();
}

void arcade::PacMan::eatGums(std::vector<std::vector<int>> &map, long unsigned int &score, std::vector<Ghost> &ghosts)
{
    std::pair<double, double> current_pos = getGridPosition(_entity.pos);
    std::pair<double, double> tmpDir;

    if (current_pos.first < 0 || current_pos.first > _map[0].size() - 1)
        return;
    if (map[current_pos.second][current_pos.first] == PacmanMap::GUMS)
    {
        map[current_pos.second][current_pos.first] = PacmanMap::EMPTY;
        score += 10;
    }
    if (map[current_pos.second][current_pos.first] == PacmanMap::PACGUMS)
    {
        map[current_pos.second][current_pos.first] = PacmanMap::EMPTY;
        score += 50;
        for (std::size_t i = 0; i < ghosts.size(); i++)
        {
            ghosts[i].eatable = {true, 10};
            ghosts[i].setType(arcade::GhostType::RANDOM);
            tmpDir = ghosts[i].getEntity().direction;
            ghosts[i].getEntity().direction = {-tmpDir.first, -tmpDir.second};
            ghosts[i].getEntity().speed -= 1;
        }
    }
}

void arcade::PacMan::updateId(double dtime)
{
    std::pair<int, int> newAnim = {-1, -1};

    _lastAnim += dtime;
    if (_entity.direction.first == 1 && _entity.direction.second == 0)
        newAnim = {41, 42};
    if (_entity.direction.first == -1 && _entity.direction.second == 0)
        newAnim = {43, 44};
    if (_entity.direction.first == 0 && _entity.direction.second == 1)
        newAnim = {47, 48};
    if (_entity.direction.first == 0 && _entity.direction.second == -1)
        newAnim = {45, 46};
    if ((_entity.id == newAnim.first || _entity.id == newAnim.second) && _lastAnim < 0.2)
        return;
    if (newAnim.first == -1)
        return;
    _lastAnim = 0;
    _animState = (_animState + 1) % 2;
    if (_animState == 0)
        _entity.id = newAnim.first;
    else
        _entity.id = newAnim.second;
}

arcade::Ghost::Ghost(GhostType type, std::pair<int, int> pos, struct arcade::TextureIds ids)
{
    _entity.pos = pos;
    _entity.id = ids.up.first;
    _entity.type = "Ghost";
    _defaultType = type;
    _type = type;
    alive = true;
    _defaultSpeed = _entity.speed;
    _defaultSnapRange = _snapRange;
    eatable = {false, 0};
    _defaultPos = pos;
    _ids = ids;
    _lastAnim = 0;
    _animState = 0;
}

arcade::Ghost::~Ghost()
{
}

void arcade::Ghost::update(double dtime, std::vector<std::vector<int>> &map, const arcade::Entity &pacman)
{
    std::pair<double, double> pos = getGridPosition(_entity.pos);

    _map = map;
    _pathfinder.setMap(_map);
    if (eatable.first == true)
    {
        eatable.second -= dtime;
        if (eatable.second <= 0)
        {
            eatable.first = false;
            _type = _defaultType;
            _entity.speed = _defaultSpeed;
        }
    }
    if (alive == false)
    {
        if (pos.first == 13 && pos.second == 14 && isSnapable(_entity.direction))
        {
            alive = true;
            _entity.speed = _defaultSpeed;
            _snapRange = _defaultSnapRange;
            _type = _defaultType;
        }
        else
            changeDirection(followPath({13, 14}));
    }
    if (alive == true)
    {
        if (_type == arcade::GhostType::RANDOM)
            changeDirection(randomDir());
        if (_type == arcade::GhostType::FOLLOW)
            changeDirection(followPath(getGridPosition(pacman.pos)));
        if (_type == arcade::GhostType::ANTICIPATE)
            anticipate(pacman);
    }
    applyMovement(dtime);
    updateId(dtime);
}

void arcade::Ghost::updateId(double dtime)
{
    std::pair<int, int> newAnim;

    _lastAnim += dtime;
    if (alive && !eatable.first)
    {
        if (_entity.direction.first == 1 && _entity.direction.second == 0)
            newAnim = _ids.right;
        if (_entity.direction.first == -1 && _entity.direction.second == 0)
            newAnim = _ids.left;
        if (_entity.direction.first == 0 && _entity.direction.second == 1)
            newAnim = _ids.down;
        if (_entity.direction.first == 0 && _entity.direction.second == -1)
            newAnim = _ids.up;
        if (_entity.direction.first == 0 && _entity.direction.second == 0)
            newAnim = _ids.up;
    }
    if (!alive)
    {
        if (_entity.direction.first == 1 && _entity.direction.second == 0)
            newAnim = {85, 85};
        if (_entity.direction.first == -1 && _entity.direction.second == 0)
            newAnim = {86, 86};
        if (_entity.direction.first == 0 && _entity.direction.second == 1)
            newAnim = {88, 88};
        if (_entity.direction.first == 0 && _entity.direction.second == -1)
            newAnim = {87,87};
        if (_entity.direction.first == 0 && _entity.direction.second == 0)
            newAnim = {87, 87};
    }
    if (alive && eatable.first)
        newAnim = {81, 82};
    if ((_entity.id == newAnim.first || _entity.id == newAnim.second) && _lastAnim < 0.2)
        return;
    _lastAnim = 0;
    _animState = (_animState + 1) % 2;
    if (_animState == 0)
        _entity.id = newAnim.first;
    else
        _entity.id = newAnim.second;
}

void arcade::Ghost::applyMovement(double dtime)
{
    std::pair<double, double> next;

    _entity.pos.first += _entity.direction.first * _entity.speed * dtime;
    _entity.pos.second += _entity.direction.second * _entity.speed * dtime;
    next = getNextCell(_entity.pos, _entity.direction);
    if (next.first < 0)
    {
        if (next.first < -1)
            _entity.pos.first = _map[0].size();
        return;
    }
    if (next.first > _map[0].size())
    {
        _entity.pos.first = -1;
        return;
    }
    if (_map[next.second][next.first] <= PacmanMap::GHOST_WALLS && _map[next.second][next.first] != 0)
    {
        _entity.pos = getGridPosition(_entity.pos);
        _entity.direction = {0, 0};
    }
}

void arcade::Ghost::reset()
{
    _entity.id = _ids.up.first;
    _entity.direction = {0, 0};
    _entity.display = true;
    _entity.speed = 3;
    _snapRange = 0.07;
    _nextDirection = {0, 0};
    alive = true;
    _entity.pos = _defaultPos;
    _defaultSnapRange = _snapRange;
    _defaultSpeed = _entity.speed;
    _lastAnim = 0;
    _animState = 0;
    eatable = {false, 0};
}

void arcade::Ghost::resetAndIncrease()
{
    _entity.id = _ids.up.first;
    _entity.direction = {0, 0};
    _entity.display = true;
    _entity.speed += 0.5;
    _snapRange += 0.01;
    _nextDirection = {0, 0};
    alive = true;
    _entity.pos = _defaultPos;
    _defaultSnapRange = _snapRange;
    _defaultSpeed = _entity.speed;
    _lastAnim = 0;
    _animState = 0;
    eatable = {false, 0};
}

void arcade::Ghost::setType(GhostType type)
{
    _type = type;
}

arcade::Event arcade::Ghost::dirToEvent(const std::pair<double, double> &dir)
{
    if (dir.first > 0)
        return arcade::Event::RIGHT;
    if (dir.first < 0)
        return arcade::Event::LEFT;
    if (dir.second > 0)
        return arcade::Event::DOWN;
    if (dir.second < 0)
        return arcade::Event::UP;
    return arcade::Event::NOTHING;
}

arcade::Event arcade::Ghost::randomDir()
{
    std::vector<std::pair<double, double>> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    std::vector<std::pair<double, double>> randDir;
    std::pair<double, double> tmp;
    int randId = 0;
    arcade::Event ret;

    for (std::size_t i = 0; i < dir.size(); i++)
    {
        if (dir[i].first == -_entity.direction.first && dir[i].second == -_entity.direction.second)
            continue;
        if (canTurn(dir[i]))
            randDir.push_back(dir[i]);
    }
    if (randDir.size() == 0)
        return arcade::Event::NOTHING;
    randId = (rand() % ((randDir.size() - 1) + 1));
    ret = dirToEvent(randDir[randId]);
    return ret;
}

arcade::Event arcade::Ghost::followPath(std::pair<int, int> end)
{
    std::pair<int, int> pos = getGridPosition(_entity.pos);
    std::pair<int, int> dir = {0, 0};
    std::vector<std::pair<int, int>> path;
    int size = _map[0].size();

    if (pos.first < 0 || pos.first > size - 1)
        return arcade::Event::NOTHING;
    if (end.first < 0 || end.first > size - 1)
        return arcade::Event::NOTHING;
    path = _pathfinder.getPath(pos, end);
    if (path.size() > 1)
    {
        dir.first = path[1].first - pos.first;
        dir.second = path[1].second - pos.second;
        if (dir.first > 0)
            return arcade::Event::RIGHT;
        if (dir.first < 0)
            return arcade::Event::LEFT;
        if (dir.second > 0)
            return arcade::Event::DOWN;
        if (dir.second < 0)
            return arcade::Event::UP;
    }
    return arcade::Event::NOTHING;
}

void arcade::Ghost::anticipate(const arcade::Entity &pacman)
{
    std::pair<double, double> dest = {pacman.pos.first + (pacman.direction.first * 4),
                                    pacman.pos.second + (pacman.direction.second * 4)};
    double length = _map[0].size();
    double height = _map.size();

    if (dest.first < 0)
        dest.first = 0;
    if (dest.first > length - 1)
        dest.first = length - 1;
    if (dest.second < 0)
        dest.second = 0;
    if (dest.second > height - 1)
        dest.second = height - 1;
    for (int i = 0; i < 4 && _map[dest.second][dest.first] <= PacmanMap::GHOST_WALLS
                        && _map[dest.second][dest.first] != 0; i++)
    {
        dest.first -= pacman.direction.first;
        dest.second -= pacman.direction.second;
    }
    changeDirection(followPath(getGridPosition(dest)));
}

bool arcade::Ghost::canTurn(std::pair<double, double> dir)
{
    std::pair<double, double> next = getGridPosition(_entity.pos);

    if (!isSnapable(dir))
        return false;
    next.first += dir.first;
    next.second += dir.second;
    if (next.first > _map[0].size() - 1 || next.first < 0)
    {
        return false;
    }
    if (_map[next.second][next.first] <= PacmanMap::GHOST_WALLS && _map[next.second][next.first] != 0)
        return false;
    return true;
}

void arcade::Ghost::setToDefault()
{
    _type = _defaultType;
    _entity.speed = _defaultSpeed;
    _snapRange = _defaultSnapRange;
}
