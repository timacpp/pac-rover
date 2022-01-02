//
// Created by Piotr Kamiński on 02/01/2022.
//

#ifndef SPACE_ROVER_DIRECTION_H
#define SPACE_ROVER_DIRECTION_H

enum class Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

Direction to_right(Direction &dir) {
    switch (dir) {
        case Direction::NORTH:
            return Direction::EAST;
        case Direction::EAST:
            return Direction::SOUTH;
        case Direction::SOUTH:
            return Direction::WEST;
        case Direction::WEST:
            return Direction::NORTH;
    }
}

Direction to_left(Direction &dir) {
    switch (dir) {
        case Direction::NORTH:
            return Direction::WEST;
        case Direction::EAST:
            return Direction::NORTH;
        case Direction::SOUTH:
            return Direction::EAST;
        case Direction::WEST:
            return Direction::SOUTH;
    }
}

#endif //SPACE_ROVER_DIRECTION_H
