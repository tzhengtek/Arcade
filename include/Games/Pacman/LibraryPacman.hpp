/*
** EPITECH PROJECT, 2023
** LibraryPacman.hpp
** File description:
** LibraryPacman
*/

#ifndef LIBRARYPACMAN_HPP_
#define LIBRARYPACMAN_HPP_

    #include <chrono>
    #include <IGame.hpp>
    #include <iostream>
    #include "PathFinder.hpp"
    #define NAME "Pacman"

namespace arcade {

    enum class GhostType {
        FOLLOW,
        ANTICIPATE,
        RANDOM
    };

    /**
     * @brief 
     * TextureIds struct
     */
    struct TextureIds {
        std::pair<int, int> up;
        std::pair<int, int> down;
        std::pair<int, int> left;
        std::pair<int, int> right;
    };

    /**
     * @brief 
     * APacEntity Class
     */
    class APacEntity {
        public:
            APacEntity();
            ~APacEntity();

            arcade::Entity &getEntity();
            double &getSnapRange();
        protected:
            /**
             * @brief 
             * All function to move and snap position of the pacman
             */
            virtual void applyMovement(double dtime);
            std::pair<double, double> getGridPosition(std::pair<double, double> position);
            std::pair<double, double> getNextCell(std::pair<double, double> pos, std::pair<double, double> dir);
            void changeDirection(Event event);
            bool isSnapable(std::pair<double, double> dir);
            virtual bool canTurn(std::pair<double, double> dir);
            void snapPosition(std::pair<double, double> dir);

            arcade::Entity _entity;
            double _snapRange;
            std::pair<double, double> _nextDirection;
            std::vector<std::vector<int>> _map;
    };

    /**
     * @brief 
     * Ghost Class
     */
    class Ghost : public APacEntity {
        public:
            Ghost(GhostType type, std::pair<int, int> pos, struct TextureIds ids);
            ~Ghost();

            void update(double dtime, std::vector<std::vector<int>> &map, const arcade::Entity &pacman);
            void setType(GhostType type);
            void reset();
            void resetAndIncrease();
            void setToDefault();

            bool alive;
            std::pair<bool, double> eatable;
        private:
            void updateId(double dtime);
            void applyMovement(double dtime);
            bool canTurn(std::pair<double, double> dir);
            arcade::Event followPath(std::pair<int, int> end);
            arcade::Event randomDir();
            arcade::Event dirToEvent(const std::pair<double, double> &dir);
            void anticipate(const arcade::Entity &pacman);

            pathfinder::PathFinder _pathfinder;
            GhostType _type;
            GhostType _defaultType;
            double _defaultSpeed;
            double _defaultSnapRange;
            std::pair<int, int> _defaultPos;
            struct TextureIds _ids;
            double _lastAnim;
            int _animState;
    };


    /**
     * @brief 
     * PacMan Class
     */
    class PacMan : public APacEntity {
        public:
            PacMan();
            ~PacMan();

            /**
             * @brief 
             * Pacman entity function to load ans reset game + handle event in game
             */
            void update(double dtime, std::vector<std::vector<int>> &map, arcade::Event &event);
            void reset();
            void resetAndIncrease();
            void checkCollision(std::vector<Ghost> &ghosts, std::vector<std::vector<int>> &map,
                                std::vector<std::vector<int>> &saveMap, long unsigned int &score,
                                double &beginTime);
            void resetGhosts(std::vector<Ghost> &ghosts);
            void eatGums(std::vector<std::vector<int>> &map, long unsigned int &score, std::vector<Ghost> &ghosts);
        private:
            void updateId(double dtime);

            double _lastAnim;
            int _animState;
    };

    /**
     * @brief 
     * LibraryPacman Class
     */
    class LibraryPacman : public IGame {
        public:
            LibraryPacman();
            ~LibraryPacman();
            void update(arcade::Event event, double delta_time);
            arcade::Game &getGameEntity();
            const std::pair<int, int> getMapSize() const;
            const std::pair<int, int> getNextLib() const;
            const std::string getAssetPath() const;

        protected:

        private:
            void getNamePlayer();
            struct Entity createMapEntity(int x, int y, int id, const std::string &type);
            bool hasGetAllFood();

            Game _gameInfo;
            double _dtime;
            arcade::PacMan _pacman;
            std::vector<Ghost> _ghosts;
            std::vector<std::vector<int>> _map;
            std::vector<std::vector<int>> _saveMap;
            double _beginTime;
    };

}

#endif /* !LIBRARYPACMAN_HPP_ */
