/*
** EPITECH PROJECT, 2023
** LibraryNCURSE.hpp
** File description:
** LibraryNCURSE
*/

#ifndef LIBRARYNCURSE
    #define LIBRARYNCURSE
    #include <iostream>
    #include "IGraphical.hpp"
    #include <ncurses.h>
    #define NAME "nCurses"

namespace arcade {

    /**
     * @brief 
     * LibraryNCurse Class
     */

    class LibraryNCurse : public arcade::IGraphical {
        public:
            LibraryNCurse();
            LibraryNCurse(LibraryNCurse const &) = delete;
            ~LibraryNCurse();
            arcade::Event getEvent(arcade::Game &game);
            void renderElement(const struct Game &gameEntity);
            void setMapSize(std::pair<int, int> mapSize);
            void setAssetPath(const std::string &path);

        protected:
        private:
            /**
             * @brief 
             * function to display element on ncurses
             */
            void initColors();
            void colorPrint(int line, int column, char c, int color);
            void drawRectangle(int y1, int x1, int y2, int x2);
            void showMapBorders(int height, int width);
            void showElement(const struct Game &gameEntity, int height, int width);

            /**
             * @brief 
             * Variable static for set the highest color
             */
            static const short COLOR_PINK = 8;
            static const short MAX_COLOR = 8;

            /**
             * @brief 
             * Class to stock the information about the texture in ncurses
             */

            struct Texture {
                char character;
                int color;
            };

            SCREEN * _screen;
            std::pair<int, int> _mapSize;
            std::map<int, LibraryNCurse::Texture> _textures;
    };
}

#endif /* !LIBRARYNCURSE */
