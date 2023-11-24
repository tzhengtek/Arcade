/*
** EPITECH PROJECT, 2023
** Library.cpp
** File description:
** Library
*/

#include <iostream>
#include "LibraryNCurse.hpp"
#include "ConfigParser.hpp"
#include <filesystem>
#include <algorithm>

int libraryType = 1;
char const *libraryName = NAME;

arcade::LibraryNCurse::LibraryNCurse()
{
    _screen = newterm(getenv("TERM"), stdout, stdin);
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    initColors();
}

arcade::LibraryNCurse::~LibraryNCurse()
{
    endwin();
    delscreen(_screen);
}

void arcade::LibraryNCurse::initColors() {
    start_color();
    init_color(COLOR_RED, 1000, 0, 0);
    init_color(COLOR_GREEN, 0, 1000, 0);
    init_color(COLOR_YELLOW, 1000, 1000, 0);
    init_color(COLOR_BLUE, 0, 0, 1000);
    init_color(COLOR_MAGENTA, 1000, 0, 1000);
    init_color(COLOR_CYAN, 0, 1000, 1000);
    init_color(COLOR_WHITE, 1000, 1000, 1000);
    init_color(COLOR_PINK, 1000, 752, 796);

    for (int i = 1; i <= MAX_COLOR; i++) {
        for (int j = 0; j <= MAX_COLOR; j++) {
            init_pair(i * 10 + j, i, j);
        }
    }
}

arcade::Event arcade::LibraryNCurse::getEvent(arcade::Game &game)
{
    (void) game;
    int key = 0;
    MEVENT event;

    timeout(0);
    key = wgetch(stdscr);
    if (key == 'q')
        return arcade::Event::QUIT;
    if (key == KEY_UP)
        return arcade::Event::UP;
    if (key == KEY_RIGHT)
        return arcade::Event::RIGHT;
    if (key == KEY_DOWN)
        return arcade::Event::DOWN;
    if (key == KEY_LEFT)
        return arcade::Event::LEFT;
    if (key == 'm')
        return arcade::Event::NEXT_GAME;
    if (key == 'p')
        return arcade::Event::NEXT_GRAPHIC;
    if (key == KEY_MOUSE)
    {
        if (OK == getmouse(&event))
        {
            game.mouse_pos = {event.x * (_mapSize.first / COLS), event.y * (_mapSize.second / LINES)};
            return arcade::Event::MOUSE_CLICK;
        }
    }
    return arcade::Event::NOTHING;
}

void arcade::LibraryNCurse::drawRectangle(int y1, int x1, int y2, int x2)
{
    mvhline(y1, x1, 0, x2 - x1);
    mvhline(y2, x1, 0, x2 - x1);
    mvvline(y1, x1, 0, y2 - y1);
    mvvline(y1, x2, 0, y2 - y1);
    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y2, x1, ACS_LLCORNER);
    mvaddch(y1, x2, ACS_URCORNER);
    mvaddch(y2, x2, ACS_LRCORNER);
}

void arcade::LibraryNCurse::showElement(const struct Game &gameEntity, int height, int width)
{
    int xScore = (COLS / 2) + (width / 2) + 2;
    int yScore = (LINES / 2) - (height / 2);
    int xName = (COLS / 2) + (width / 2) + 2;
    int yName = (LINES / 2) - (height / 2) + 3;
    std::string text = "Score: " + std::to_string(gameEntity.score);
    std::string name = "Player: " + gameEntity.name;

    drawRectangle(yScore - 1, xScore, yScore + 1, xScore + text.length() + 1);
    mvprintw(yScore, xScore + 1, "%s", text.c_str());
    drawRectangle(yName - 1, xName, yName + 1, xName + name.length() + 1);
    mvprintw(yName, xName + 1, "%s", name.c_str());
}

void arcade::LibraryNCurse::showMapBorders(int height, int width)
{
    int y1 = (LINES / 2) - (height / 2) - 1;
    int x1 = (COLS / 2) - (width / 2) - 1;
    int y2 = (LINES / 2) + (height / 2);
    if (height % 2 != 0)
        y2++;
    int x2 = (COLS / 2) + (width / 2);
    if (width % 2 != 0)
        x2++;
    drawRectangle(y1, x1, y2, x2);
}

void arcade::LibraryNCurse::colorPrint(int line, int column, char c, int color) {
    attron(COLOR_PAIR(color));
    mvprintw(line, column, "%c", c);
    attroff(COLOR_PAIR(color));
}

void arcade::LibraryNCurse::renderElement(const struct Game &gameEntity)
{
    int line = 0;
    int column = 0;
    int offset_x = COLS / 2 - _mapSize.first / 2;
    int offset_y = LINES / 2 - _mapSize.second / 2;

    erase();

    showMapBorders(_mapSize.second, _mapSize.first);
    showElement(gameEntity, _mapSize.second, _mapSize.first);
    for (std::size_t i = 0; i < gameEntity.map.size(); i++)
    {
        if (gameEntity.map[i].display)
        {
            line = gameEntity.map[i].pos.second + offset_y;
            column = gameEntity.map[i].pos.first + offset_x;
            colorPrint(line, column, _textures[gameEntity.map[i].id].character, _textures[gameEntity.map[i].id].color);
        }
    }
    for (std::size_t i = 0; i < gameEntity.entity.size(); i++)
    {
        line = gameEntity.entity[i].pos.second + offset_y;
        column = gameEntity.entity[i].pos.first + offset_x;
        if (gameEntity.entity[i].type.substr(0, 5) == "text_")
            mvprintw(gameEntity.entity[i].pos.second * LINES, gameEntity.entity[i].pos.first * COLS, "%s", gameEntity.entity[i].type.substr(5).c_str());
        else if (gameEntity.entity[i].display)
            colorPrint(line, column, _textures[gameEntity.entity[i].id].character, _textures[gameEntity.entity[i].id].color);
    }
}

void arcade::LibraryNCurse::setMapSize(std::pair<int, int> mapSize)
{
    _mapSize = mapSize;
}

void arcade::LibraryNCurse::setAssetPath(const std::string &path)
{
    Texture texture;
    int index;
    ConfigParser configParser;
    std::vector<std::map<std::string, std::string>> parsedConfig;
    bool file_found = false;
    std::string new_path = path + "/Ncurses";

    if (path == "./assets/Menu")
        return;

    try {
        for(std::filesystem::directory_entry const &dir_entry : std::filesystem::directory_iterator(new_path)) {
            if (dir_entry.is_directory() == false) {
                parsedConfig = configParser.loadNcursesTexturesFromConfig(dir_entry.path());
                file_found = true;
            }
        }
        if (!file_found)
            throw Error::BadConfigFileError("Unable to open or find Ncurses's config file in \"" + new_path + "\"");
    } catch(std::filesystem::filesystem_error &e) {
        throw Error::BadConfigFileError("Unable to open or find \"" + new_path + "\"");
    }

    for (size_t i = 0; i < parsedConfig.size(); i++) {
        texture = Texture();
        index = stoi(parsedConfig[i]["id"]);
        texture.color = stoi(parsedConfig[i]["color_pair"]);
        texture.character = parsedConfig[i]["print"][0];
        _textures[index] = texture;
    }
}

extern "C" arcade::LibraryNCurse *entryPoint()
{
    return new arcade::LibraryNCurse;
}
