/*
** EPITECH PROJECT, 2023
** Main.ppp
** File description:
** Main
*/

#include <memory>
#include <map>
#include "Error.hpp"
#include "Macro.hpp"
#include "Core/DLLoader.hpp"
#include "IGraphical.hpp"
#include "IGame.hpp"
#include "Core.hpp"
#include "Menu.hpp"

#include <dirent.h>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <filesystem>
#include <algorithm>

void error_handling(int ac)
{
    if (ac != 2) {
        if (ac == 1)
            throw Error::NotEnoughArgumentsError();
        throw Error::TooManyArgumentsError(ac);
    }
}

int main(int ac, const char * const av[])
{
    srand(time(0));
    try
    {
        error_handling(ac);
        arcade::Core core(av[1]);
        core.arcadeGame();
    }
    catch(const Error::NoSymbolError &e)
    {
        std::cerr << e.what() << std::endl;
        return exitFailure;
    }
    catch(const Error::OpenLibraryError &e)
    {
        std::cerr << e.what() << std::endl;
        return exitFailure;
    }
    catch(const Error::TooManyArgumentsError &e)
    {
        std::cerr << e.what() << std::endl;
        return exitFailure;
    }
    catch(const Error::NotEnoughArgumentsError &e)
    {
        std::cerr << e.what() << std::endl;
        return exitFailure;
    }
    catch(const Error::InitSDLError &e)
    {
        std::cerr << e.what() << std::endl;
        return exitFailure;
    }
    catch(const Error::BadConfigFileError &e)
    {
        std::cerr << e.what() << std::endl;
        return exitFailure;
    }
    return exitSuccess;
}
