#ifndef SPACE_ROVER_H
#define SPACE_ROVER_H

#include <string>
#include <vector>
#include "direction.h"

using coordinate_t = int;
// TODO: potencjalnie mozna zrobic klase coordinates, razem z ostreamem
using coordinates = std::pair<coordinate_t, coordinate_t>;

struct Sensor {
    virtual bool is_safe(coordinate_t x, coordinate_t y) = 0;
};

class Rover {
private:
    coordinates coord;
    Direction direction;
    bool landed = false;
    bool stopped = false;
    std::vector<Sensor> sensors;

    bool is_safe(coordinates coords) {
        for (auto &sensor : sensors)
            if (!sensor.is_safe(coords.first, coords.second))
                return false;
        return true;
    }

public:
    Rover() {};

    Direction get_direction() {
        return direction;
    }

    void set_direction(Direction _direction) {
        direction = _direction;
    }

    coordinates get_coordinates() {
        return coord;
    }

    bool got_stopped() {
        return stopped;
    }

    int check_and_go(coordinates _coord) {
        stopped = !is_safe(_coord);
        if (!stopped) {
            coord = _coord;
            return 0;
        }
        return 1;
    }

    void land(coordinates _coord, Direction _direction) {
        coord = _coord;
        direction = _direction;
        landed = true;
    };

    void execute(std::string programm) {
        if (!landed)
            throw std::exception();


    }

    friend std::ostream& operator<<(std::ostream& ostream, const Rover& rover) {
        if (!rover.landed) {
            ostream << "unknown\n";
            return ostream;
        }
        else {
            ostream << '(' << rover.coord.first << ", " << rover.coord.second << ") "
                    << "DIRECTION";
            if (rover.stopped)
                ostream << " stopped";
            ostream << '\n';
            return ostream;
        }
    }
};

#endif // SPACE_ROVER_H
