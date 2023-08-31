#include "app.h"
#include <iostream>

int main() {
    int yan;
    while (true)
    {
        Game::app game(800, 600, L"Snake");
        game.start();
        game.end();
        std::wcout << L"Do You Want To Play Another Game? Yes(1) NO(0) : ";
        std::wcin >> yan;
        if (yan == 1)
        {

        }
        else
        {
            break;
        }
    }
}