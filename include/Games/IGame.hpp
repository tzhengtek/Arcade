/*
** EPITECH PROJECT, 2023
** architecture
** File description:
** IGame
*/

#ifndef IGAME_HPP_
    #define IGAME_HPP_

    #include "../Arcade.hpp"
    #include <vector>
    #include <string>

/**
** @brief Arcade namespace.
*/
namespace arcade {

    /**
    ** @brief An interface for defining different arcade games.
    ** Each games specific assets or elements will be created in the game constructor
    ** in order to keep it generics.
    */
    class IGame {
        public:
            /** @brief Pure virtual destructor.*/
            virtual ~IGame() = default;

            /**
            ** @brief This function will update every states and elements of the
            ** game in relation to the event passed in parameters. */
            virtual void update(arcade::Event event, double delta_time) = 0;

            /** @brief Get the last updated map in order to draw it with a graphical library.*/
            virtual arcade::Game &getGameEntity() = 0;

            /** @brief Get the size of the map to print on the screen. */
            virtual const std::pair<int, int> getMapSize() const = 0;

            /**
             * @brief Get the Next Lib object
             * Return a std::pair of the nextLib to set
             * @return const std::pair<int, int>
             */
            virtual const std::pair<int, int> getNextLib() const = 0;

            /**
             * @brief Get the Asset Path object
             * get the assetPath for the graphicalLib
             * @return const std::string
             */
            virtual const std::string getAssetPath() const = 0;
    };
};

#endif /* !IGAME_HPP_ */
