/*
** EPITECH PROJECT, 2023
** LibrarySNAKE.hpp
** File description:
** LibrarySNAKE
*/

#ifndef LIBRARYSNAKE
    #define LIBRARYSNAKE

    #include <IGame.hpp>
    #include <iostream>
    #include <ctime>
    #include <chrono>
    #include <map>
    #include <filesystem>
    #include "ConfigParser.hpp"
    #define NAME "Snake"

static const double UPDATE = 0.150;

namespace arcade {

    /**
     * @brief 
     * LibrarySnake Class
     */

    class LibrarySnake : public arcade::IGame {
        public:
            LibrarySnake();
            ~LibrarySnake();
            void update(arcade::Event event, double delta_time);
            arcade::Game &getGameEntity();
            const std::pair<int, int> getMapSize() const;
            const std::pair<int, int> getNextLib() const;
            const std::string getAssetPath() const;

        protected:
        private:
            /**
             * @brief Get the Name Player object saved in a file
             */
            void getNamePlayer();
            /**
             * @brief All function to get the direction of the snake
             */
            void uniqueDirectionBody(std::pair<double, double> sens, int i, int newId);
            void checkRotateBody(std::pair<double, double> rotation1,
                    std::pair<double, double> rotation2, int i, int newId, int opposite);
            void checkDirectionBody();
            bool changeDirection(arcade::Event event, arcade::Event lateralDir1, arcade::Event lateralDir2, bool check);

            /**
             * @brief 
             * Check and modify position of the snake, depending on its direction
             */
            bool moveSnake();
            bool isSamePos();

            /**
             * @brief Create a Entity object
             * Init and reset Game function
             */
            void resetGame();
            void initGame();
            void initGameEntity();

            /**
             * @brief Create a Entity object
             * check Event Gameplay on snake
             */
            void checkEatFruit();
            void enlargeBodySnake();
            void checkTouchBorderMap();

            /**
             * @brief Create a Entity object
             * createEntity function
             */
            struct Entity createEntity(std::pair<double, double> direction, std::size_t startX, std::size_t startY, int id, const std::string &type);

            /**
             * @brief 
             * useful variable for the snake
             */
            double _lastTime;
            std::vector<std::vector<int>> _saveMap;
            std::vector<arcade::Entity> _entities;
            struct Game _gameInfo;
            std::size_t _countFruit;
            std::size_t _sizeMapX;
            std::size_t _sizeMapY;
            arcade::Event _direction;
            std::size_t _size;
            bool _axisDirectionX;
            bool _axisDirectionY;
            bool _enlargeBody;
            std::pair<double, double> _enlargePos;
            std::pair<double, double> _fruitPos;
            arcade::Event _lastEvent;
    };
}

#endif /* !LIBRARYSNAKE */
