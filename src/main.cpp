#include "Game.h"
#include <iostream>

int main()
{
    std::srand(std::time(nullptr));

    try
    {
        Game* game = new Game();
        game->Run();
        delete game;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
