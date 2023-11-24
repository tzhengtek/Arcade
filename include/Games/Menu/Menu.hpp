/*
** EPITECH PROJECT, 2023
** Menu.hpp
** File description:
** Menu
*/

#ifndef MENU_HPP_
    #define MENU_HPP_

    #include <iostream>
    #include <filesystem>
    #include <algorithm>
    #include <vector>
    #include <string>
    #include <fstream>
    #include "DLLoader.hpp"
    #include "../Arcade.hpp"
    #include "IGame.hpp"
    #include "IGraphical.hpp"
    #define NAME "Menu"
    #define LIB_PATH "./lib/"
    #define SIZE_TEXT 40

namespace arcade {
    /**
     * @brief 
     * Menu Class
     */
    class Menu : public IGame {
        public:
            Menu();
            ~Menu();
            void getAllLibraryName();
            void update(arcade::Event event, double delta_time);
            Game &getGameEntity();
            const std::pair<int, int> getMapSize() const;
            const std::string getAssetPath() const;
            const std::pair<int, int> getNextLib() const;

        protected:
        private:
            void savePlayerName();
            std::string getNamePlayer();
            std::string _letter;
            std::vector<std::size_t> _nameValue;
            std::size_t _indexName;
            std::string _text;
            arcade::Entity _continue;
            std::pair<int, int> _saveIndex;
            std::pair<int, int> _index;
            void selectLibrary(std::string &elem, std::vector<std::string> lib, int &index);
            void renderSelectElem(int &index, std::string &elem, const std::vector<std::string> &lib);
            void renderElem();
            void selectElem();
            void checkContinue();
            void clickOnElement(std::string &elem, bool select);
            arcade::Entity createTextEntity(std::pair<double, double> pos, const std::string &text);
            std::pair<int, int> _mapSize;
            Game _menu;
            std::vector<std::string> _gameLibName;
            std::vector<std::string> _graphicLibName;
    };
}

#endif /* !MENU_HPP_ */
