/*
** EPITECH PROJECT, 2023
** DLLoader.cpp
** File description:
** DLLoader
*/

#include <dlfcn.h>
#include <memory>
#include "Core/DLLoader.hpp"

DLLoader::DLLoader()
{
    _handler = nullptr;
}

DLLoader::DLLoader(DLLoader &&other): _handler(other._handler)
{
    other._handler = nullptr;
}

DLLoader::DLLoader(const std::string &library)
{
    _handler = dlopen(library.c_str(), RTLD_LAZY);
    if (!_handler)
        throw Error::OpenLibraryError(library);
}

DLLoader::~DLLoader()
{
    closeHandler();
}

void DLLoader::closeHandler()
{
    if (_handler)
        dlclose(_handler);
}

DLLoader &DLLoader::operator=(DLLoader &&other)
{
    if (_handler != other._handler)
    {
        closeHandler();
        _handler = other._handler;
        other._handler = nullptr;
    }
    return *this;
}
