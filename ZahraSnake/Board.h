#pragma once

#include "Snake.h"
#include "global.h"

class Board {
public:

    Board();
    ~Board() = default;

    void update(sf::RenderWindow& win);
    void changeDirection(char input);
    char operator[](int i) const;
    int score() const;

    static constexpr int width = 20;
    static constexpr int height = 15;

private:

    enum Tile {
        OPEN = 1,
        WALL,
        SNAKE,
        FOOD
    };

    Snake snake;
    std::string map;
    int m_score;

    void genFood();
    bool place(Coord coord, int item);
    bool isEmpty(Coord coord) const;
    int at(Coord coord)       const;

};