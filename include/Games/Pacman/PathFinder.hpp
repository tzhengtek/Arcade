/*
** EPITECH PROJECT, 2023
** PathFinder.hpp
** File description:
** PathFinder
*/

#ifndef PATHFINDER_HPP_
#define PATHFINDER_HPP_
    #include <vector>
    #include <string>
    #include <map>

namespace pathfinder {

    /**
     * @brief 
     * PathFinder Class for the ghosts
     */

    class PathFinder {
        public:
            PathFinder();
            ~PathFinder();

            /**
             * @brief
             * All function for the ghost path finding
             */
            void setMap(const std::vector<std::vector<int>> &map);
            std::vector<std::pair<int, int>> getPath(std::pair<int, int> pos, std::pair<int, int> end);
        private:
            bool _alreadyInPath(const std::vector<std::pair<int, int>> &path, const std::pair<int, int> &pos);
            std::vector<std::vector<bool>> _createEmptyVisited();
            std::vector<std::vector<std::pair<int, int>>> _createParent();

            std::vector<std::vector<int>> _map;
    };

};

#endif /* !PATHFINDER_HPP_ */
