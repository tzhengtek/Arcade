/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-aldric.jourdain
** File description:
** ConfigParser
*/

#include "ConfigParser.hpp"
#include <sstream>

std::string ConfigParser::removeComments(std::string str) {
    std::size_t commentStart = -1;

    for (std::size_t i = 0; i < str.length(); i++) {
        if (str[i] == '#')
            commentStart = i;
    }
    if (commentStart != std::size_t(-1))
        return str.substr(0, commentStart);
    return str;
}

std::pair<std::size_t, std::size_t> ConfigParser::findDelim(std::string str, std::vector<std::string> delims) {
    std::pair<std::size_t, std::size_t> result;
    std::size_t pos = std::string::npos;
    result.first = pos;
    result.second = 0;

    for (std::size_t i = 0; i < delims.size(); i++) {
        pos = str.find(delims[i]);
        if (pos < result.first) {
            result.first = pos;
            result.second = delims[i].length();
        }
    }
    return result;
}

std::vector<std::string> ConfigParser::splitLine(std::string str, const std::vector<std::string> &delims) {
    std::vector<std::string> lineParts;
    std::string part;

    std::pair<std::size_t, std::size_t> pos;
    while ((pos = findDelim(str, delims)).first != std::string::npos) {
        if (pos.first != 0) {
            part = str.substr(0, pos.first);
            lineParts.push_back(part);
        }
        str.erase(0, pos.first + pos.second);
    }
    if (str.length() > 0)
        lineParts.push_back(str);
    return lineParts;
}

std::vector<std::vector<std::string>> ConfigParser::parseConfigFile(const std::string &filepath, const std::vector<std::string> &delims) {
    std::vector<std::vector<std::string>> parts;
	std::fstream configFile;
    std::string line;

	configFile.open(filepath, std::ios::in);
    if (!configFile.is_open() || !configFile.good())
        throw Error::BadConfigFileError("Unable to open or find \"" + filepath + "\"");

    while(getline(configFile, line)) {
        line = removeComments(line);
        if (line.length() == 0)
            continue;
        parts.push_back(splitLine(line, delims));
    }
    configFile.close();
    return parts;
}

int ConfigParser::getIntFromString(std::string str) {
    int value = 0;

    try {
        value = std::stoi(str);
    } catch(std::invalid_argument &e) {
        std::ostringstream message;
        message << "Not an integer in config file" << std::endl;
        throw Error::BadConfigFileError(message.str());
    }
    return value;
}

double ConfigParser::getDoubleFromString(std::string str) {
    double value = 0.0;

    try {
        value = std::stof(str);
    } catch(std::invalid_argument &e) {
        std::ostringstream message;
        message << "Not an double in config file" << std::endl;
        throw Error::BadConfigFileError(message.str());
    }
    return value;
}

std::vector<std::vector<int>> ConfigParser::loadMapFromConfig(const std::string &filepath) {
    const std::vector<std::string> delims = { "," };
    std::vector<std::vector<std::string>> lines = parseConfigFile(filepath, delims);
    std::vector<std::vector<int>> map(lines.size());

    for (std::size_t i = 0; i < lines.size(); i++)
    {
        for (std::size_t j = 0; j < lines[i].size(); j++)
            map[i].push_back(stoi(lines[i][j]));
    }
    return map;
}

std::vector<std::map<std::string, std::string>> ConfigParser::loadNcursesTexturesFromConfig(const std::string &filepath) {
    const std::vector<std::string> delims = { " ", ":" };
    std::vector<std::vector<std::string>> lines = parseConfigFile(filepath, delims);
    std::vector<std::map<std::string, std::string>> textures;
    std::map<std::string, std::string> texture;
    int currentId = -1;

    for (std::size_t i = 0; i < lines.size(); i++) {
        if (lines[i].size() == 1) {
            if (lines[i][0][0] == '-' && currentId != -1) {
                textures.push_back(texture);
                texture = std::map<std::string, std::string>();
                currentId = -1;
                continue;
            }
        }
        if (lines[i].size() == 2) {
            if (lines[i][0] == "id") {
                int value = getIntFromString(lines[i][1]);
                currentId = value;
                texture["id"] = lines[i][1];
            }
            if (lines[i][0] == "color_pair" && currentId != -1) {
                getIntFromString(lines[i][1]);
                texture["color_pair"] = lines[i][1];
            }
            if (lines[i][0] == "print" && currentId != -1)
                texture["print"] = lines[i][1];
        }
    }
    return textures;
}

std::vector<std::map<std::string, std::string>> ConfigParser::loadTexturesFromConfig(const std::string &filepath) {
    std::vector<std::map<std::string, std::string>> textures;
    std::map<std::string, std::string> texture;
    const std::vector<std::string> delims = { " " };
    std::vector<std::vector<std::string>> lines = parseConfigFile(filepath, delims);

    for (std::size_t i = 0; i < lines.size(); i++) {
        if (lines[i].size() != TEXTURE_CONFIG_LENGTH)
            continue;
        texture = std::map<std::string, std::string>();
        texture["description"] = lines[i][0];
        texture["id"] = lines[i][1];
        texture["pos_x"] = lines[i][2];
        texture["pos_y"] = lines[i][3];
        texture["width"] = lines[i][4];
        texture["height"] = lines[i][5];
        texture["scale_x"] = lines[i][6];
        texture["scale_y"] = lines[i][7];
        textures.push_back(texture);
    }
    return textures;
}

std::vector<arcade::Entity> ConfigParser::loadEntitiesFromConfig(const std::string &filepath) {
    std::vector<arcade::Entity> entities;
    const std::vector<std::string> delims = { " ", ":" };
    std::vector<std::vector<std::string>> lines = parseConfigFile(filepath, delims);
    arcade::Entity entity;
    int currentId = -1;

    for (std::size_t i = 0; i < lines.size(); i++) {
        if (lines[i].size() == 1) {
            if (lines[i][0][0] == '-' && currentId != -1) {
                entities.push_back(entity);
                entity = arcade::Entity();
                currentId = -1;
                continue;
            }
        }
        if (lines[i].size() == 2) {
            if (lines[i][0] == "id") {
                int value = getIntFromString(lines[i][1]);
                currentId = value;
                entity.id = value;
            }
            if (lines[i][0] == "type" && currentId != -1)
                entity.type = lines[i][1];
            if (lines[i][0] == "speed" && currentId != -1) {
                double value = getDoubleFromString(lines[i][1]);
                entity.speed = value;
            }
            if (lines[i][0] == "display" && currentId != -1) {
                int value = getIntFromString(lines[i][1]);
                if (value == 1)
                    entity.display = true;
                else
                    entity.display = false;
            }
            if (lines[i][0] == "x" && currentId != -1) {
                double value = getDoubleFromString(lines[i][1]);
                entity.pos.first = value;
            }
            if (lines[i][0] == "y" && currentId != -1) {
                double value = getDoubleFromString(lines[i][1]);
                entity.pos.second = value;
            }
            if (lines[i][0] == "dir_x" && currentId != -1) {
                double value = getDoubleFromString(lines[i][1]);
                entity.direction.first = value;
            }
            if (lines[i][0] == "dir_y" && currentId != -1) {
                double value = getDoubleFromString(lines[i][1]);
                entity.direction.second = value;
            }
        }
    }
    return entities;
}
