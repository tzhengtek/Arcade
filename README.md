# Arcade - Epitech

Arcade is an Epitech project, that have for goal to implement diffents, game and graphical libraries.
After all, the goal is to have to possibility to share you're libraries with another team that have the same architecture as you.

``` text
Configuration File

So this configuration file is templated for the Sfml/SDL2 library that use sprites.

description id pos_x pos_y width height scale_x scale_y
Example :
left_top_double_corner 1 745 214 8 8 2 2

So this configuration file is templated for the Ncurses library that don't use sprites.

id:1
print:W
color_pair:4
---------

File to configure and fill the std::vector<arcade::Entity> entity stocked in the game structure.
Type can be for example {Player, Ghosts, Wall, Food, ...}

id:1
type:Player  <-- Example
x:0
y:0
dir_x:0
dir_y:0
speed:0
display:1
-----------------------

```

## Usage/Examples

```cpp


/**
 * @brief Include the Graphical interface to use it.
*/
#include "IGraphical.hpp"
#include "IGame.hpp"


// Main function
int main(int argc, char *argv[])
{
    /**
     * @brief Create a library instance with the path to the .so file gived by the user.
     * The loadLibrary(char *path) function will open the asked library and will return a IGraphical class.
    */
    initLibrary<IGraphical> (argv[1], _graphic, _graphicLoader);
    /**
     * @brief Create a game instance with the path to the .so file gived by the user.
     * Load Menu game Lib
    */
    initLibrary<IGame> ("./lib/arcade_menu.so", _game, _gameLoader);
    /**
     * @brief Create an event variable to store the actual event
    */
    event_t event = NOTHING;

    /**
     * @brief Loop the game while the actual event isn't a "quit" event
    */

    while (_event != Event::QUIT)
    {
        /**
        * @brief Clock for game
        */
        now = std::chrono::high_resolution_clock::now();
        ms_double = now - _lastTime;
        /**
         * @brief Get event from the user
         */
        _event = _graphic->getEvent(_game->getGameEntity());
        /**
         * @brief Update game depending of the input
         */
        _game->update(_event, ms_double.count());
        /**
         * @brief Change library depending of input
         */
        changeLibrary();
        /**
         * @brief Render element by the graphic library
         */
        _graphic->renderElement(_game->getGameEntity());
        _lastTime = now;
    }
}
```

## Authors

-   [@tzhengtek](https://www.github.com/tzhengtek)
-   [@AldricJourdain](https://www.github.com/AldricJourdain)
-   [@MathieuMarques](https://www.github.com/MathieuMarques)
