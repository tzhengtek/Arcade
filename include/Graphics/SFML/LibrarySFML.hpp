/*
** EPITECH PROJECT, 2023
** LibrarySFML.hpp
** File description:
** LibrarySFML
*/

#ifndef LIBRARYSFML_HPP_
    #define LIBRARYSFML_HPP_
    #include <iostream>
    #include <SFML/Graphics.hpp>
    #include "IGraphical.hpp"
    #include "Error.hpp"
    #define NAME "SFML"
    #define WIDTH 900
    #define HEIGHT 1000
    #define FONT 40

namespace arcade {

    /**
     * @brief 
     * LibrarySFML Class
     */

    class LibrarySFML : public arcade::IGraphical {
        public:
            LibrarySFML();
            LibrarySFML(LibrarySFML const &) = delete;
            ~LibrarySFML();
            arcade::Event getEvent(arcade::Game &game);
            void renderElement(const struct Game &gameEntity);
            void setMapSize(std::pair<int, int> mapSize);
            void setAssetPath(const std::string &path);

        protected:
        private:
            void displayText(const std::string &text, sf::Color color, std::pair<float, float> pos);
            std::pair<int, int> _mapSize;
            sf::RenderWindow _window;
            sf::Font _font;
            sf::Texture _texture;
            std::map<int, sf::RectangleShape> _rects;
    };

}


#endif /* !LIBRARYSFML_HPP_ */
