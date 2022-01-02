#ifndef SPACE_ROVER_H
#define SPACE_ROVER_H

#include "direction.h"

using coordinate_t = int;
using coordinates = std::pair<coordinate_t, coordinate_t>;

class Rover {
private:
    coordinates coordinates;
    Direction direction;
    bool landed = false;

public:
    Rover() {};

    void land(::coordinates _coordinates, Direction _direction) {
        coordinates = _coordinates;
        direction = _direction;
        landed = true;
    };

};

#endif // SPACE_ROVER_ROVER_H
