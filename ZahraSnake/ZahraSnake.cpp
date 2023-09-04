#include "app.h"
#include <iostream>
#include <Windows.h>

int main() {
    Game::app game(800, 600, L"Zahra Snake");

    LPWSTR* szArglist;
    int nArgs;
    szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);

    std::wstring wstr(szArglist[1]);
    std::string str(wstr.begin(), wstr.end());
    int speed = std::stoi(str);

    game.start(speed);
    game.end();

    LocalFree(szArglist);

    return highscore;
}
