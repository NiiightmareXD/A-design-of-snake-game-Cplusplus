#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Snake.h"
#include "Board.h"
#include "global.h"

namespace Game {
    class app {
    public:
        app(int windowWidth, int windowHeight, const wchar_t* name);
        ~app() = default;

        // Runs the app
        void start();
        void end();

        // MEMBER VARIABLES

        const int winWidth, winHeight;
        const float common_divisor;
        sf::RenderWindow window;
        Board board;
        sf::Font calibri;

        // MEMBER FUNCTIONS

        void drawWindow();
        void handleEvents();
        void updateWindow();
    };
}