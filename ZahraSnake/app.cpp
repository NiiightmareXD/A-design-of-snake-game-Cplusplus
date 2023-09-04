#include "app.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <fstream>

std::fstream MyFile;

int difficulty = 3, frameratelimit = 5, highscore = 0;
std::string username;
Game::app::app(int windowWidth, int windowHeight, const wchar_t* name)
    : winWidth{ windowWidth }, winHeight{ windowHeight }, common_divisor{ 40.0f } {
    window.create(sf::VideoMode(winWidth, winHeight), name);
    window.setFramerateLimit(frameratelimit);
}

// Handles any game event
void Game::app::handleEvents() {

    sf::Event event;

    while (window.pollEvent(event)) {
        switch (event.type) {

        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
            case 73:
                board.changeDirection('w');
                break;
            case 72:
                board.changeDirection('d');
                break;
            case 74:
                board.changeDirection('s');
                break;
            case 71:
                board.changeDirection('a');
                break;
            default:
                break;
            }
            break;
        case sf::Event::TextEntered:
            board.changeDirection(static_cast<char>(event.text.unicode));
        }
    }
}

// Draws all game objects
void Game::app::drawWindow() {

    for (size_t i = 0, h = Board::height; i < h; ++i) {
        for (size_t j = 0, w = Board::width; j < w; ++j) {

            // Draws walls
            if (board[i * w + j] == 2) {
                sf::RectangleShape rect;
                rect.setSize({ common_divisor, common_divisor });

                rect.setPosition({ common_divisor * j, common_divisor * i });
                window.draw(rect);
            }

            // Draws snake
            else if (board[i * w + j] == 3) {

                sf::RectangleShape rect;
                rect.setFillColor(sf::Color::Green);
                rect.setSize({ common_divisor, common_divisor });

                rect.setPosition({ common_divisor * j, common_divisor * i });
                window.draw(rect);
            }

            // Draws food
            else if (board[i * w + j] == 4) {

                sf::RectangleShape rect;
                rect.setFillColor(sf::Color::Red);
                rect.setSize({ common_divisor, common_divisor });

                rect.setPosition({ common_divisor * j, common_divisor * i });
                window.draw(rect);
            }

        }
    }

    // Draws the game score
    sf::Text text;
    text.setFont(calibri);
    text.setPosition({ 0.0f, 0.0f });
    text.setString("Score: " + std::to_string(board.score()));
    text.setFillColor(sf::Color::Black);
    window.draw(text);
}

// Updates the render window
void Game::app::updateWindow() {
    window.clear(sf::Color::Color(9, 80, 40));
    drawWindow();
    window.display();
}

// Starts the app
void Game::app::start(int frameratelimit) {
    HWND hwnd = window.getSystemHandle();
    SetFocus(hwnd);
    SetForegroundWindow(hwnd);
    SetActiveWindow(hwnd);
    window.setFramerateLimit(frameratelimit);

    while (window.isOpen()) {
        handleEvents();
        board.update(window);
        updateWindow();
    }
}

void Game::app::end() {}
