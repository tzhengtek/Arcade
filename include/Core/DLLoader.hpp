/*
** EPITECH PROJECT, 2023
** DLLoader.hpp
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
    #define DLLOADER_HPP_

    #include <dlfcn.h>
    #include <iostream>
    #include <cstdint>
    #include "Error.hpp"

class DLLoader {
    public:
        DLLoader();
        DLLoader(const std::string &library);
        DLLoader(DLLoader const &) = delete;
        ~DLLoader();
        DLLoader(DLLoader &&other);
        DLLoader &operator = (DLLoader &&other);
        void closeHandler();

        /**
         * @brief Get the Instance object
         * Get Instance to get a symbol of a dynamic library
         */
        template <typename T>
        T getInstance(const std::string &entryPoint) const
        {
            T symbol = reinterpret_cast<T> (dlsym(_handler, entryPoint.c_str()));
            if (dlerror() == NULL)
                return symbol;
            throw Error::NoSymbolError(entryPoint);
        }

    protected:
    private:
        void *_handler;
};

#endif /* !DLLOADER_HPP_ */
