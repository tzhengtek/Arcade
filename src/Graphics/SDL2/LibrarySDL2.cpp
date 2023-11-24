/*
** EPITECH PROJECT, 2023
** Library.cpp
** File description:
** Library
*/

#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_rect.h>
#include "Error.hpp"
#include "LibrarySDL2.hpp"

int libraryType = 1;
char const *libraryName = NAME;

arcade::LibrarySDL2::LibrarySDL2()
{
    if (TTF_Init() == -1)
        throw Error::InitSDLError(SDL_GetError());
    if (IMG_Init(IMG_INIT_PNG) == -1)
        throw Error::InitSDLError(SDL_GetError());
    _font = TTF_OpenFont("./assets/fonts/ARCADECLASSIC.TTF", 40);
    if (_font == NULL)
        throw Error::InitSDLError(SDL_GetError());
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw Error::InitSDLError(SDL_GetError());
    _window = SDL_CreateWindow("GAME",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                WIDTH, HEIGHT, 0);
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    _image = nullptr;
    _texture = nullptr;
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
}

arcade::LibrarySDL2::~LibrarySDL2()
{
    if (_texture)
        SDL_DestroyTexture(_texture);
    if (_image)
        SDL_FreeSurface(_image);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    TTF_CloseFont(_font);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

arcade::Event arcade::LibrarySDL2::getEvent(arcade::Game &game)
{
    (void) game;
    SDL_Event event;

    while (SDL_PollEvent(&event) > 0)
    {
        switch (event.type)
        {
            case SDL_QUIT:
                return arcade::Event::QUIT;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                        return arcade::Event::UP;
                    case SDLK_DOWN:
                        return arcade::Event::DOWN;
                    case SDLK_RIGHT:
                        return arcade::Event::RIGHT;
                    case SDLK_LEFT:
                        return arcade::Event::LEFT;
                    case SDLK_m:
                        return arcade::Event::NEXT_GAME;
                    case SDLK_p:
                        return arcade::Event::NEXT_GRAPHIC;
                }
        }
        switch (event.button.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                game.mouse_pos = {event.button.x, event.button.y};
                return arcade::Event::MOUSE_CLICK;
        }
    }
    return arcade::Event::NOTHING;
}

void arcade::LibrarySDL2::displayEntity(const arcade::Game &gameEntity)
{
    SDL_Rect rect;
    std::pair<int, int> size = {WIDTH / _mapSize.first, WIDTH / _mapSize.first};

    if (size.second * gameEntity.map.size() > 1000)
        size = {WIDTH / _mapSize.second, WIDTH / _mapSize.second};
    rect.w = size.first;
    rect.h = size.second;
    for (std::size_t i = 0; i < gameEntity.map.size(); i++)
    {
        rect.y = gameEntity.map[i].pos.second * size.second;
        rect.x = gameEntity.map[i].pos.first * size.first;
        if (gameEntity.map[i].display &&
                            _rects.find(gameEntity.map[i].id) != _rects.end())
            SDL_RenderCopy(_renderer, _texture, &_rects[gameEntity.map[i].id], &rect);
    }
    for (std::size_t i = 0; i < gameEntity.entity.size(); i++)
    {
        if (gameEntity.entity[i].type.substr(0, 5) == "text_")
        {
            rect.y = gameEntity.entity[i].pos.second * size.second * _mapSize.first;
            rect.x = gameEntity.entity[i].pos.first * size.first * _mapSize.second;
            displayText(gameEntity.entity[i].type.substr(5), {255, 255, 255, 255}, {rect.x, rect.y});
            continue;
        }
        if (gameEntity.entity[i].display &&
                        _rects.find(gameEntity.entity[i].id) != _rects.end())
        {
            rect.y = gameEntity.entity[i].pos.second * size.second;
            rect.x = gameEntity.entity[i].pos.first * size.first;
            SDL_RenderCopy(_renderer, _texture, &_rects[gameEntity.entity[i].id], &rect);
        }
    }
    if (gameEntity.score != static_cast<std::size_t> (-1))
    {
        std::string score = std::to_string(gameEntity.score);
        displayText("Score :" + score, {255, 255, 255, 255}, {20, WIDTH});
        std::string name = "Player: " + gameEntity.name;
        displayText(name, {255, 255, 255, 255}, {WIDTH - (name.length() * 40) , WIDTH});
    }
}

void arcade::LibrarySDL2::displayText(const std::string &text, SDL_Color color, std::pair<int, int> pos)
{
    SDL_Surface *textSurface = TTF_RenderText_Solid(_font, text.c_str(), color);
    SDL_Rect rect = { pos.first, pos.second, 0, 0 };
    SDL_Texture *textTexture;

    if (textSurface == NULL)
        throw Error::InitSDLError(SDL_GetError());
    textTexture = SDL_CreateTextureFromSurface(_renderer, textSurface);
    if (textTexture == NULL)
        throw Error::InitSDLError(SDL_GetError());
    SDL_QueryTexture(textTexture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(_renderer, textTexture, NULL, &rect);
    SDL_DestroyTexture(textTexture);
}

void arcade::LibrarySDL2::renderElement(const struct Game &gameEntity)
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
    displayEntity(gameEntity);
    SDL_RenderPresent(_renderer);
}

void arcade::LibrarySDL2::setMapSize(std::pair<int, int> mapSize)
{
    _mapSize = mapSize;
}


void arcade::LibrarySDL2::setAssetPath(const std::string &path)
{
    int index = 0;
    ConfigParser configParser;
    std::vector<std::map<std::string, std::string>> parsedConfig;
    bool file_found = false;
    bool file_png = false;
    std::string new_path = path;

    if (path == "./assets/Menu")
        return;
    if (_image)
        SDL_FreeSurface(_image);
    if (_texture)
        SDL_DestroyTexture(_texture);

    try {
        for(std::filesystem::directory_entry const &dir_entry : std::filesystem::directory_iterator(new_path)) {
            if (dir_entry.is_directory() == false && dir_entry.path().filename().string().find("Textures") != std::string::npos) {
                parsedConfig = configParser.loadTexturesFromConfig(dir_entry.path());
                file_found = true;
            }
            if (dir_entry.is_directory() == false && dir_entry.path().filename().string().find(".png") != std::string::npos) {
                _image = IMG_Load(dir_entry.path().c_str());
                _texture = SDL_CreateTextureFromSurface(_renderer, _image);
                file_png = true;
            }
        }
        if (!file_found)
            throw Error::BadConfigFileError("Unable to open or find's config file in \"" + new_path + "\"");
        if (!file_png)
            throw Error::BadConfigFileError("Unable to open or find spritesheet file");
    } catch(std::filesystem::filesystem_error &e) {
        throw Error::BadConfigFileError("Unable to open or find \"" + new_path + "\"");
    }
    SDL_Rect rect;
    for (std::size_t i = 0; i < parsedConfig.size(); i++) {
        index = stoi(parsedConfig[i]["id"]);
        if (index != 0)
        {
            rect = {stoi(parsedConfig[i]["pos_x"]),
                    stoi(parsedConfig[i]["pos_y"]),
                    stoi(parsedConfig[i]["width"]),
                    stoi(parsedConfig[i]["height"])};
            _rects[index] = rect;
        }
    }
}

extern "C" arcade::LibrarySDL2 *entryPoint()
{
    return new arcade::LibrarySDL2;
}
