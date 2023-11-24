/*
** EPITECH PROJECT, 2023
** Core.cpp
** File description:
** Core
*/

#include "Core.hpp"

arcade::Core::Core(const std::string &libraryName):_event(Event::NOTHING)
{
    getLibraryList();
    _indexLib = {-1, getLibraryIndex(libraryName, _libGraphical)};
    initLibrary<IGame> ("./lib/arcade_menu.so", _game, _gameLoader);
    initLibrary<IGraphical> (libraryName, _graphic, _graphicLoader);
    _graphic->setMapSize(_game->getMapSize());
    _graphic->setAssetPath(_game->getAssetPath());
}

arcade::Core::~Core()
{
}

bool comparePair(std::pair<int, int> pair1, std::pair<int, int> pair2)
{
    return pair1.first == pair2.first && pair1.second == pair2.second;
}

std::size_t arcade::Core::getLibraryIndex
                (const std::string &libraryName, std::vector<std::string> lib)
{
    std::vector<std::string>::iterator iterator =
                                std::find(lib.begin(), lib.end(), libraryName);
    if (iterator != lib.end())
        return std::distance(lib.begin(), iterator);
    throw Error::OpenLibraryError(libraryName);
}

void arcade::Core::changeLibrary()
{
    bool checkSelectLibrary = comparePair(_game->getNextLib(), {-1 , -1});
    bool checkSameLibrary = comparePair(_game->getNextLib(), _indexLib);
    int saveGraphicalIndex = _indexLib.second;

    if (!checkSelectLibrary && !checkSameLibrary)
    {
        _indexLib = _game->getNextLib();
        if (saveGraphicalIndex != _indexLib.second)
            initLibrary<IGraphical> (_libGraphical[_indexLib.second], _graphic, _graphicLoader);
        initLibrary<IGame> (_libGame[_indexLib.first], _game, _gameLoader);
        _graphic->setMapSize(_game->getMapSize());
        _graphic->setAssetPath(_game->getAssetPath());
    }
    if ((_event == Event::NEXT_GAME && _indexLib.first != -1) ||
        _event == Event::NEXT_GRAPHIC)
    {
        (_event == Event::NEXT_GAME && _indexLib.first != -1) ?
            setNextLib<IGame> (_indexLib.first, _libGame, _gameLoader, _game) :
            setNextLib<IGraphical> (_indexLib.second, _libGraphical, _graphicLoader, _graphic);
        _graphic->setMapSize(_game->getMapSize());
        _graphic->setAssetPath(_game->getAssetPath());
    }
}

void arcade::Core::arcadeGame()
{
    auto now = std::chrono::high_resolution_clock::now();
    auto dtime = std::chrono::duration_cast<std::chrono::duration<double>>(now - _lastTime);

    _lastTime = now;
    while (_event != Event::QUIT)
    {
        now = std::chrono::high_resolution_clock::now();
        dtime = now - _lastTime;
        _event = _graphic->getEvent(_game->getGameEntity());
        _game->update(_event, dtime.count());
        changeLibrary();
        _graphic->renderElement(_game->getGameEntity());
        _lastTime = now;
    }
}

void arcade::Core::getLibraryList()
{
    const std::filesystem::path libPath(LIB_PATH);
    for (std::filesystem::directory_entry const &dir_entry :
                                std::filesystem::directory_iterator{libPath})
    {
        if (dir_entry.is_directory() == false &&
                            dir_entry.path().filename().string()[0] != '.') {
            try
            {
                DLLoader load(dir_entry.path());
                std::string_view libraryName = *load.getInstance<char const **>("libraryName");
                int libraryType = *(load.getInstance<int *>("libraryType"));
                if (libraryName == "Menu")
                    continue;
                if (libraryType == static_cast<int> (LibraryType::GAME))
                    _libGame.emplace_back(dir_entry.path());
                if (libraryType == static_cast<int> (LibraryType::GRAPHIC))
                    _libGraphical.emplace_back(dir_entry.path());
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
