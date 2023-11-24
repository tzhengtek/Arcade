/*
** EPITECH PROJECT, 2023
** PathFinder.cpp
** File description:
** PathFinder
*/

#include <fstream>
#include <iostream>
#include <queue>
#include <algorithm>
#include "PathFinder.hpp"
#include "PacmanMap.hpp"

pathfinder::PathFinder::PathFinder()
{
}

pathfinder::PathFinder::~PathFinder()
{
}

void pathfinder::PathFinder::setMap(const std::vector<std::vector<int>> &map)
{
    _map = map;
}

std::vector<std::pair<int, int>> pathfinder::PathFinder::getPath(std::pair<int, int> pos, std::pair<int, int> end)
{
    std::queue<std::pair<int, int>> q;
    std::vector<std::vector<bool>> visited = _createEmptyVisited();
    std::vector<std::vector<std::pair<int, int>>> parent = _createParent();
    std::vector<std::pair<int, int>> path = {};
    int length = _map[0].size();
    int height = _map.size();
    std::pair<int, int> tmp;

    q.push(pos);
    visited[pos.second][pos.first] = true;
    parent[pos.second][pos.first] = {-1, -1};
    while (!q.empty())
    {
        tmp = q.front();
        q.pop();
        if (tmp.first > 0
            && (_map[tmp.second][tmp.first - 1] == 0 || _map[tmp.second][tmp.first - 1] > PacmanMap::GHOST_WALLS)
            && visited[tmp.second][tmp.first - 1] == false)
        {
            visited[tmp.second][tmp.first - 1] = true;
            q.push({tmp.first - 1, tmp.second});
            parent[tmp.second][tmp.first - 1] = tmp;
        }
        if (tmp.first < length - 1
            && (_map[tmp.second][tmp.first + 1] == 0 || _map[tmp.second][tmp.first + 1] > PacmanMap::GHOST_WALLS)
            && visited[tmp.second][tmp.first + 1] == false)
        {
            visited[tmp.second][tmp.first + 1] = true;
            q.push({tmp.first + 1, tmp.second});
            parent[tmp.second][tmp.first + 1] = tmp;
        }
        if (tmp.second > 0
            && (_map[tmp.second - 1][tmp.first] == 0 || _map[tmp.second - 1][tmp.first] > PacmanMap::GHOST_WALLS)
            && visited[tmp.second - 1][tmp.first] == false)
        {
            visited[tmp.second - 1][tmp.first] = true;
            q.push({tmp.first, tmp.second - 1});
            parent[tmp.second - 1][tmp.first] = tmp;
        }
        if (tmp.second + 1 < height - 1
            && (_map[tmp.second + 1][tmp.first] == 0 || _map[tmp.second + 1][tmp.first] > PacmanMap::GHOST_WALLS)
            && visited[tmp.second + 1][tmp.first] == false)
        {
            visited[tmp.second + 1][tmp.first] = true;
            q.push({tmp.first, tmp.second + 1});
            parent[tmp.second + 1][tmp.first] = tmp;
        }
    }
    if (visited[end.second][end.first] == false)
        return {};
    for (std::pair<int, int> i = end; i.first != -1 && i.second != -1; i = parent[i.second][i.first])
    {
        if ((i.first <= -2 || i.second <= -2) || i.first > length || i.second > height ||
            _alreadyInPath(path, i))
            return {};
        path.push_back(i);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

bool pathfinder::PathFinder::_alreadyInPath(const std::vector<std::pair<int, int>> &path, const std::pair<int, int> &pos)
{
    for (std::size_t i = 0; i < path.size(); i++)
    {
        if (path[i].first == pos.first && path[i].second == pos.second)
            return true;
    }
    return false;
}

std::vector<std::vector<bool>> pathfinder::PathFinder::_createEmptyVisited()
{
    std::vector<std::vector<bool>> visited;

    for (std::size_t i = 0; i < _map.size(); i++)
    {
        visited.push_back({});
        for (std::size_t j = 0; j < _map[i].size(); j++)
        {
            visited[i].push_back(false);
        }
    }
    return visited;
}

std::vector<std::vector<std::pair<int, int>>> pathfinder::PathFinder::_createParent()
{
    std::vector<std::vector<std::pair<int, int>>> parent;

    for (std::size_t i = 0; i < _map.size(); i++)
    {
        parent.push_back({});
        for (std::size_t j = 0; j < _map[i].size(); j++)
        {
            parent[i].push_back({-2, -2});
        }
    }
    return parent;
}
