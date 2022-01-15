#ifndef ROVER_STATE_H
#define ROVER_STATE_H

#include "position.h"
#include "direction.h"

struct Sensor {
    virtual bool is_safe(coordinate_t x, coordinate_t y) = 0;

    virtual ~Sensor() = default; // TODO: default is bad
};

using sensor_ptr = std::unique_ptr<Sensor>;

class SensorFalse : public std::exception {

};

class RoverState {
public:
    RoverState() : landed{false}, stopped{false}, direction{Direction::NORTH} {}

    void set(Position& landing_spot, Direction& facing_direction) {
        landed = true;
        position = landing_spot;
        direction = facing_direction;
    }

    void stop_rover() {
        stopped = true;
    }

    void advance_forward(const std::vector<sensor_ptr>& sensors) {
        if (!landed)
            throw std::exception();
        stopped = false;
        Position other_position = position;
        switch (direction) {
            case Direction::NORTH:
                other_position += {0, 1};
                break;
            case Direction::EAST:
                other_position += {1, 0};
                break;
            case Direction::SOUTH:
                other_position += {0, -1};
                break;
            case Direction::WEST:
                other_position += {-1, 0};
        }

        for (auto &sensor : sensors) {
            if (!sensor->is_safe(other_position.get_x(), other_position.get_y())) {
                stopped = true;
                throw SensorFalse();
            }
        }

        position = other_position;
    }

    void advance_backward(const std::vector<sensor_ptr>& sensors) {
        if (!landed)
            throw std::exception();
        stopped = false;
        Position other_position = position;
        switch (direction) {
            case Direction::NORTH:
                other_position += {0, -1};
                break;
            case Direction::EAST:
                other_position += {-1, 0};
                break;
            case Direction::SOUTH:
                other_position += {0, 1};
                break;
            case Direction::WEST:
                other_position += {1, 0};
        }

        for (auto &sensor : sensors) {
            if (!sensor->is_safe(other_position.get_x(), other_position.get_y())) {
                stopped = true;
                throw SensorFalse();
            }
        }

        position = other_position;
    }

    void rotate_right() {
        if (!landed)
            throw std::exception();
        stopped = false;
        ++direction;
    }

    void rotate_left() {
        if (!landed)
            throw std::exception();
        stopped = false;
        --direction;
    }

    friend std::ostream& operator<<(std::ostream& out, const RoverState& state) noexcept {
        if (!state.landed)
            return out << "unknown";

        return out << state.position << " "
                   << state.direction
                   << (state.stopped ? " stopped" : "");
    }
private:
    bool landed;
    bool stopped;
    Position position;
    Direction direction;
};

#endif // ROVER_STATE_H
