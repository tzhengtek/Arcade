/*
** EPITECH PROJECT, 2023
** LibrarySDL2.hpp
** File description:
** LibrarySDL2
*/

#ifndef LIBRARYSDL2
    #define LIBRARYSDL2

    #include <iostream>
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>
    #include <SDL2/SDL_image.h>
    #include <filesystem>
    #include <algorithm>
    #include "IGraphical.hpp"
    #include "ConfigParser.hpp"
    #define NAME "SDL2"
    #define WIDTH 900
    #define HEIGHT 1000

namespace arcade {

    /**
     * @brief 
     * LibrarySDL2 Class
     */
    class LibrarySDL2 : public arcade::IGraphical {
        public:
            LibrarySDL2();
            ~LibrarySDL2();
            LibrarySDL2(LibrarySDL2 const &) = delete;
            arcade::Event getEvent(arcade::Game &game);
            void renderElement(const struct Game &gameEntity);
            void setMapSize(std::pair<int, int> mapSize);
            void setAssetPath(const std::string &path);

        protected:
        private:
            /**
             * @brief 
             * Necessary variable to load and display SDL2 lib
             */
            SDL_Texture *_texture;
            SDL_Surface *_image;
            SDL_Window *_window;
            SDL_Renderer *_renderer;
            TTF_Font *_font;
            std::map<int, SDL_Rect> _rects;
            void displayText(const std::string &text, SDL_Color color, std::pair<int, int> pos);
            void displayEntity(const struct Game &gameEntity);
            std::pair<int, int> _mapSize;
    };

}

#endif /* !LIBRARYSDL2 */
