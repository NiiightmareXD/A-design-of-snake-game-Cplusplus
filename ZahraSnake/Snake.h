#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Coord.h"
#include "global.h"

class Snake {
public:

    Snake();
    ~Snake() = default;

    // Changes the dir value based on the input
    void changeDirection(char input);

    // Adds a piece to the snake and returns its location
    Coord add();
    size_t size();

    /* Moves all pieces and returns
    the previous position of last piece */
    Coord follow();
    Coord moveHead(); // Moves and returns position of new head
    Coord headLocation() const;

private:

    // MEMBER VARIABLES 
    struct Snake_segment
    {
        Coord current, previous;
    };

    enum direction {
        UP = 0,
        RIGHT,
        DOWN,
        LEFT
    };

    std::vector<Snake_segment> snakeContainer;
    direction dir;

public:

    Snake_segment operator[](int i) const;
};