/*
** EPITECH PROJECT, 2023
** architecture
** File description:
** IGraphical
*/

#ifndef IGRAPHICAL_HPP_
    #define IGRAPHICAL_HPP_

    #include <string>
    #include <vector>
    #include <map>
    #include "../Arcade.hpp"

namespace arcade {
    /**
    @brief An interface for defining graphical libraries.
    */

    class IGraphical {
        public:
            /* @brief Pure virtual destructor.*/
            virtual ~IGraphical() = default;

            /**
            ** @brief Get the event received if there is one.
            ** @return The received event name.
            */
            virtual arcade::Event getEvent(arcade::Game &game) = 0;

            /**
            ** @brief Set the Map Size object
            */
            virtual void setMapSize(std::pair<int, int> mapSize) = 0;
            /**
            ** @brief Load the map that is needed to be draw.
            */
            virtual void renderElement(const arcade::Game &game) = 0;

            /**
             * @brief Set the Asset Path object
             * @param path
             */
            virtual void setAssetPath(const std::string &path) = 0;
    };
}

#endif /* !IGRAPHICAL_HPP_ */