#include "app.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <fstream>

sf::Music music;
std::fstream MyFile;

int difficulty = 3, frameratelimit = 5, highscore = 0;
std::string username;
Game::app::app(int windowWidth, int windowHeight, const wchar_t* name)
    : winWidth{ windowWidth }, winHeight{ windowHeight }, common_divisor{ 40.0f } {
        std::wcout << L"Pick A Username: ";
        while (true)
        {
            std::cin >> username;
            if (username == "god")
            {
                std::wcout << L"You Are Not Talented Enough Pick Another Username: ";
            }
            else
            {
                break;
            }
        }
    std::wcout << L"Hard(1) , Normal(2) or Easy(3)? : (also pause is with escape and your highscore save in highscore.txt)";
    std::wcin >> difficulty;
    switch (difficulty)
    {
    case 1:
        frameratelimit = 20;
        std::wcout << L"Remember You Have 3 Second To Press On The Window Or You Keys Wont Work! \n";
        std::wcout << L"Now ";
        system("pause");
        break;
    case 2:
        frameratelimit = 10;
        std::wcout << L"Remember You Have 3 Second To Press On The Window Or You Keys Wont Work! \n";
        std::wcout << L"Now ";
        system("pause");
        break;
    case 3:
        frameratelimit = 5;
        std::wcout << L"Remember You Have 3 Second To Press On The Window Or You Keys Wont Work! \n";
        std::wcout << L"Now ";
        system("pause");
        break;
    default:
        difficulty = 3;
        std::wcout << L"Invalid Answer I Go For Easy\n";
        frameratelimit = 5;
        std::wcout << L"Remember You Have 3 Second To Press On The Window Or You Keys Wont Work! \n";
        std::wcout << L"Now ";
        system("pause");
        break;
    }
    window.create(sf::VideoMode(winWidth, winHeight), name);
    std::this_thread::sleep_for(std::chrono::seconds(3));
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

        case sf::Event::TextEntered:
            if (static_cast<char>(event.text.unicode) == 27)
            {
                window.setVisible(false);
                system("cls");
                std::wcout << L"Pause\n";
                std::wcout << L"Now ";
                system("pause");
                window.setVisible(true);
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }
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
    window.clear(sf::Color::Color(34,139,34));
    drawWindow();
    window.display();
}

// Starts the app
void Game::app::start() {
    if (!music.openFromFile("Noisestorm-Crab-Rave-Monstercat-Release.ogg"))
    {
        music.stop();
        music.openFromFile("Noisestorm-Crab-Rave-Monstercat-Release.ogg");
    }
    music.play();
    while (window.isOpen()) {
        handleEvents();
        board.update(window);
        updateWindow();
    }
}

void getHighscore()
{
    MyFile.open("highscore.txt");
    MyFile >> highscore;
    MyFile.close();
}

void Game::app::end() {
    music.stop();
    system("cls");
    getHighscore();
    std::cout << "Game Over! You Lose " << username << "!\nScore: " << board.score() << '\n' << "Highscore: " << highscore << '\n';
}