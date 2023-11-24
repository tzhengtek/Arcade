/*
** EPITECH PROJECT, 2023
** Core.hpp
** File description:
** Core
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

    #include <memory>
    #include <iostream>
    #include <filesystem>
    #include <algorithm>
    #include <chrono>
    #include "Error.hpp"
    #include "Core/DLLoader.hpp"
    #include "IGraphical.hpp"
    #include "IGame.hpp"
    #include "ConfigParser.hpp"
    #define GAME_LOADER arcade::IGame * (*) ()
    #define GRAPHICAL_LOADER arcade::IGraphical * (*) ()
    #define LIB_PATH "./lib/"

namespace arcade {
    /**
     * @brief 
     * Core Class
     */
    class Core {
        public:
            Core(const std::string &libraryName);
            ~Core();
            void getLibraryList();
            std::size_t getLibraryIndex(const std::string &libraryName, std::vector<std::string> lib);
            void arcadeGame();
            void changeLibrary();

            /**
             * @brief 
             * Template to init Library by calling the symbol
             */

            template <typename T>
            void initLibrary(const std::string &libName, std::unique_ptr<T> &component, DLLoader &loader)
            {
                component.reset();
                loader = DLLoader(libName);
                component = std::unique_ptr<T> (loader.getInstance<T * (*) ()> ("entryPoint") ());
            }

            /**
             * @brief Set the Next Lib object
             * Set the nextLib
             */
            template<typename T>
            void setNextLib(int &index, const std::vector<std::string> &lib,
                DLLoader &loader, std::unique_ptr<T> &component)
            {
                index = (index + 1) % lib.size();
                initLibrary<T> (lib[index], component, loader);
            }

        protected:
        private:
            int _indexMenu;
            arcade::Event _event;
            arcade::Game _entity;
            std::vector<std::string> _libGraphical;
            std::vector<std::string> _libGame;
            std::pair<int, int> _indexLib;
            DLLoader _graphicLoader;
            DLLoader _gameLoader;
            std::unique_ptr<arcade::IGame> _game;
            std::unique_ptr<arcade::IGraphical> _graphic;
            std::chrono::_V2::system_clock::time_point _lastTime;
    };
}
#endif /* !CORE_HPP_ */
