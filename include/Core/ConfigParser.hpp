/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-aldric.jourdain
** File description:
** ConfigParser
*/

#ifndef CONFIGPARSER_HPP_
    #define CONFIGPARSER_HPP_
    #include "../Arcade.hpp"
    #include "../Error.hpp"
    #include <string>
    #include <fstream>
    #include <iostream>
    #include <map>

static const size_t TEXTURE_CONFIG_LENGTH = 8;

class ConfigParser {
    public:
        /**
         * @brief 
         * Config loader depending of the type of file
         */
        std::vector<arcade::Entity> loadEntitiesFromConfig(const std::string &filepath);
        std::vector<std::map<std::string, std::string>> loadTexturesFromConfig(const std::string &filepath);
        std::vector<std::map<std::string, std::string>> loadNcursesTexturesFromConfig(const std::string &filepath);
        std::vector<std::vector<int>> loadMapFromConfig(const std::string &filepath);

    private:
        std::vector<std::vector<std::string>> parseConfigFile(const std::string &filepath, const std::vector<std::string> &delims);
        std::string removeComments(std::string str);
        std::pair<std::size_t, std::size_t> findDelim(std::string str, std::vector<std::string> delims);
        std::vector<std::string> splitLine(std::string str, const std::vector<std::string> &delims);
        int getIntFromString(std::string str);
        double getDoubleFromString(std::string str);
};

#endif
