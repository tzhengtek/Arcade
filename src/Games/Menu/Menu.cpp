/*
** EPITECH PROJECT, 2023
** Menu.cpp
** File description:
** Menu
*/

#include "Menu.hpp"

int libraryType = 0;
char const *libraryName = NAME;

arcade::Menu::Menu()
{
    getAllLibraryName();
    _index = {-1, -1};
    _saveIndex = {-1, -1};
    _text = "text_";
    _mapSize = {900, 900};
    _indexName = 0;
    _nameValue = {0, 0, 0};
    _letter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    _continue = createTextEntity({0.65, 0.8}, _text + "Continue");
    _menu.entity.push_back(createTextEntity({0.5, 0.1}, _text + NAME));

    _menu.entity.push_back(_continue);
    _menu.score = -1;
    for (std::size_t i = 0; i < _gameLibName.size(); i++)
        _menu.entity.push_back(createTextEntity({0.05, 0.2 + 0.080 * (i + 1)}, _text + _gameLibName[i]));
    for (std::size_t i = 0; i < _graphicLibName.size(); i++)
        _menu.entity.push_back(createTextEntity({0.6, 0.200 + 0.080 * (i + 1)}, _text + _graphicLibName[i]));
    _menu.entity.push_back(createTextEntity({0.05, 0.75}, _text + "Player :"));
    _menu.entity.push_back(createTextEntity({0.05, 0.8}, _text + getNamePlayer()));
}

std::string arcade::Menu::getNamePlayer()
{
    std::string name = "";

    for (std::size_t i = 0; i < _nameValue.size(); i++)
        name += _letter[_nameValue[i]];
    return name;
}

arcade::Entity arcade::Menu::createTextEntity(std::pair<double, double> pos, const std::string &text)
{
    arcade::Entity entityText;

    entityText.pos = pos;
    entityText.type = text;
    return entityText;
}

arcade::Menu::~Menu()
{
}

void arcade::Menu::getAllLibraryName()
{
    const std::filesystem::path libPath(LIB_PATH);
    for (std::filesystem::directory_entry const &dir_entry :
                                std::filesystem::directory_iterator{libPath})
    {
        if (dir_entry.is_directory() == false && dir_entry.path().filename().string()[0] != '.')
        {
            try
            {
                DLLoader load(dir_entry.path());
                std::string_view libraryName = *load.getInstance<char const **>("libraryName");
                int libraryType = *load.getInstance<int *>("libraryType");
                if (libraryName == NAME)
                    continue;
                if (libraryType == static_cast<int> (LibraryType::GAME))
                    _gameLibName.emplace_back(libraryName);
                if (libraryType == static_cast<int> (LibraryType::GRAPHIC))
                    _graphicLibName.emplace_back(libraryName);
            }
            catch (const Error::OpenLibraryError &e)
            {
                std::cerr << e.what() << std::endl;
            }
            catch (const Error::NoSymbolError &e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
    }
}

bool onHitbox(std::pair<double, double> posText, std::size_t lengthText, std::size_t sizeText, std::pair<int, int> posMouse)
{
    bool posXStart = posMouse.first >= posText.first;
    bool posXEnd = posMouse.first <= posText.first + (lengthText * sizeText);
    bool posYStart = posMouse.second >= posText.second;
    bool posYEnd = posMouse.second <= posText.second + sizeText;

    return posXStart && posXEnd && posYStart && posYEnd;
}

void arcade::Menu::clickOnElement(std::string &elem, bool select)
{
    if (select)
    {
        elem.insert(_text.length(), "[");
        elem.insert(elem.length(), "]");
    }
    else
    {
        elem.erase(std::remove(elem.begin(), elem.end(), '['), elem.end());
        elem.erase(std::remove(elem.begin(), elem.end(), ']'), elem.end());
    }
}

void arcade::Menu::selectLibrary(std::string &elem, std::vector<std::string> lib, int &index)
{
    std::vector<std::string>::iterator indexLib = std::find(lib.begin(), lib.end(), elem.substr(_text.length()));
    if (indexLib != lib.end())
    {
        index = indexLib - lib.begin();
        clickOnElement(elem, true);
    }
}

void arcade::Menu::selectElem()
{
    for (std::size_t i = 0; i < _menu.entity.size(); i++)
    {
        std::pair<double, double> pos = {_menu.entity[i].pos.first * _mapSize.first,
                                         _menu.entity[i].pos.second * _mapSize.second};
        if (onHitbox(pos, _menu.entity[i].type.substr(_text.length()).length(), SIZE_TEXT, _menu.mouse_pos))
        {
            selectLibrary(_menu.entity[i].type, _gameLibName, _saveIndex.first);
            selectLibrary(_menu.entity[i].type, _graphicLibName, _saveIndex.second);
        }
    }
}

void arcade::Menu::renderSelectElem(int &index, std::string &elem, const std::vector<std::string> &lib)
{
    if (index != -1)
    {
        if (elem.substr(_text.length()) == lib[index])
            clickOnElement(elem, true);
    }
}

void arcade::Menu::renderElem()
{
    for (std::size_t i = 0; i < _menu.entity.size(); i++)
    {
        clickOnElement(_menu.entity[i].type, false);
        renderSelectElem(_saveIndex.first, _menu.entity[i].type, _gameLibName);
        renderSelectElem(_saveIndex.second, _menu.entity[i].type, _graphicLibName);
    }
}

void arcade::Menu::savePlayerName()
{
    std::ofstream save(".save");

    save << getNamePlayer();
    save.close();
}

void arcade::Menu::checkContinue()
{
    std::pair<double, double> pos = {_continue.pos.first * _mapSize.first, _continue.pos.second * _mapSize.second};
    if (onHitbox(pos, _continue.type.substr(_text.length()).length(), SIZE_TEXT, _menu.mouse_pos))
    {
        if (_saveIndex.first != -1 && _saveIndex.second != -1)
        {
            _index = _saveIndex;
            savePlayerName();
        }
    }
}

void arcade::Menu::update(arcade::Event event, double delta_time)
{
    (void) delta_time;
    if (event == arcade::Event::MOUSE_CLICK)
    {
        selectElem();
        renderElem();
        checkContinue();
    }
    if (event == arcade::Event::RIGHT)
        _indexName = (_indexName + 1) % _nameValue.size();
    if (event == arcade::Event::LEFT)
        _indexName = (_indexName == 0) ? _nameValue.size() - 1 : _indexName - 1;
    if (event == arcade::Event::DOWN)
        _nameValue[_indexName] = (_nameValue[_indexName] + 1) % _letter.length();
    if (event == arcade::Event::UP)
        _nameValue[_indexName] = (_nameValue[_indexName] == 0) ? _letter.length() - 1 : _nameValue[_indexName] - 1;
    _menu.entity[_menu.entity.size() - 1].type = _text + getNamePlayer();
}

arcade::Game &arcade::Menu::getGameEntity()
{
    return _menu;
}

const std::pair<int, int> arcade::Menu::getMapSize() const
{
    return _mapSize;
}

const std::string arcade::Menu::getAssetPath() const
{
    return "./assets/Menu";
}

const std::pair<int, int> arcade::Menu::getNextLib() const
{
    return _index;
}

extern "C" arcade::Menu *entryPoint()
{
    return new arcade::Menu;
}
