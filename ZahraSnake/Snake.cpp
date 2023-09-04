#include "Snake.h"

// Initializes a two-piece snake
Snake::Snake()
    : dir{ RIGHT } {

    Snake_segment head{ {10, 7}, {9, 7} };
    snakeContainer.push_back(head);

    --head.current.x;
    snakeContainer.push_back(head);
}

Coord Snake::add() {
    snakeContainer.push_back({
        snakeContainer.back().previous,
        snakeContainer.back().previous
        });

    return snakeContainer.back().current;
}

size_t Snake::size() {
    return snakeContainer.size();
}

// Changes the direction based on input (BUGGED)
void Snake::changeDirection(char input) {
    switch (input) {
    case 'w':
        if (dir != DOWN) dir = UP;
        break;

    case 'd':
        if (dir != LEFT) dir = RIGHT;
        break;

    case 's':
        if (dir != UP) dir = DOWN;
        break;

    case 'a':
        if (dir != RIGHT) dir = LEFT;

    }
}

// All the pieces follow the head
Coord Snake::follow() {

    auto it = snakeContainer.begin();
    for (auto prev = it++; it != snakeContainer.end(); ++it, ++prev) {
        it->previous = it->current;
        it->current = prev->previous;
    }

    return snakeContainer.back().previous;
}


Coord Snake::moveHead() {

    snakeContainer[0].previous = snakeContainer[0].current;

    switch (dir) {
    case UP:
        --snakeContainer[0].current.y;
        break;

    case RIGHT:
        ++snakeContainer[0].current.x;
        break;

    case DOWN:
        ++snakeContainer[0].current.y;
        break;

    case LEFT:
        --snakeContainer[0].current.x;

    }

    return snakeContainer.front().current;
}

Snake::Snake_segment Snake::operator[](int i) const { return snakeContainer[i]; }
Coord Snake::headLocation()                   const { return snakeContainer.front().current; }