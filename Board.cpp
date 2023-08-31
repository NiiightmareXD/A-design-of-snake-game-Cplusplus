#include "Board.h"

#include <random>
#include "app.h"
#include <iostream>
#include <thread>
#include <fstream>

bool tf = true;

Board::Board()
    : m_score{ 0 } {

    // Creates a 20x15 grid
    map = {
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
        2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
        2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
        2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
        2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
        2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
        2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
        2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
        2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
        2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
        2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
        2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
        2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
    };
    switch (difficulty)
    {
    case 1:
        difficulty = NULL;
        break;
    case 2:
        genFood();
        difficulty = NULL;
        break;
    case 3:
        genFood();
        genFood();
        difficulty = NULL;
        break;
    default:
        break;
    }
    genFood();
}

int Board::at(Coord coord) const {
    return map[coord.y * width + coord.x];
}

bool Board::isEmpty(Coord coord) const {
    return at(coord) == OPEN;
}

// Sets a cell a certain value
bool Board::place(Coord coord, int item) {
    if (item != OPEN && !isEmpty(coord))
        return false;

    map[coord.y * width + coord.x] = item;
    return true;
}

void Board::genFood() {

    int fx, fy;

    do {
        std::random_device gen;
        std::uniform_int_distribution<int> disX(0, width - 1);
        std::uniform_int_distribution<int> disY(0, height - 1);

        fx = disX(gen);
        fy = disY(gen);
    } while (map[fy * Board::width + fx] != OPEN);

    map[fy * width + fx] = FOOD;
}

void Board::update(sf::RenderWindow& win) {
    auto newHead{ snake.moveHead() };
    place(snake.follow(), OPEN);
    std::fstream MyFile;
    switch (at(snake.headLocation())) {
    case WALL:
    case SNAKE:
        win.close();
        break;

    case FOOD:
        place(snake.headLocation(), OPEN);
        place(snake.add(), SNAKE);
        switch (frameratelimit)
        {
        case 20:
            m_score += 150;
            break;
        case 10:
            m_score += 100;
            break;
        case 5:
            m_score += 50;
            break;
        default:
            break;
        }
        system("cls");
        std::wcout << "Your Score Is " << m_score;
        if (m_score > highscore)
        {
            highscore = m_score;
            MyFile.open("highscore.txt");
            if (MyFile.is_open())
            {
                std::cout << " Saving Highscore To File\n";
                MyFile << highscore << std::endl;
                MyFile.close();
            }
            else
            {
                std::cout << "\nSaving Highscore To File FAILED";
            }
        }
        if (m_score == 2500)
        {
            system("cls");
            std::cout << "You Win \nnow ";
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
        genFood();
    }

    place(newHead, SNAKE);
}

void Board::changeDirection(char input) {
    snake.changeDirection(input);
}

char Board::operator[](int i) const { return map[i]; }
int Board::score()            const { return m_score; }