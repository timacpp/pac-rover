#ifndef ROVER_STATE_H
#define ROVER_STATE_H

#include "position.h"
#include "direction.h"

struct Sensor {
    virtual bool is_safe(coordinate_t x, coordinate_t y) = 0;

    virtual ~Sensor() = default;
};

using sensor_ptr = std::unique_ptr<Sensor>;
using sensor_vector = std::vector<sensor_ptr>;

class PositionIsUnsafe : public std::exception {
    [[nodiscard]] const char* what() const noexcept override {
        return "PositionIsUnsafe\0";
    }
};

class RoverNotLanded : public std::exception {
    [[nodiscard]] const char* what() const noexcept override {
        return "RoverNotLanded\0";
    }
};

class RoverState {
public:
    RoverState() : landed{false}, stopped{false}, direction{Direction::NORTH} {}

    void set(Position& landing_spot, Direction& facing_direction) noexcept {
        landed = true;
        stopped = false;
        position = landing_spot;
        direction = facing_direction;
    }

    void freeze() noexcept {
        stopped = true;
    }

    void advance_forward(const sensor_vector& sensors) {
        advance(sensors, true);
    }

    void advance_backward(const sensor_vector& sensors) {
        advance(sensors, false);
    }

    void rotate_right() {
        rotate(true);
    }

    void rotate_left() {
        rotate(false);
    }

    friend std::ostream& operator<<(std::ostream& out, const RoverState& state) noexcept {
        if (!state.landed)
            return out << "unknown";

        return out << state.position << " "
                   << state.direction
                   << (state.stopped ? " stopped" : "");
    }

private:
    void advance(const sensor_vector& sensors, bool forward) {
        if (!landed) {
            throw RoverNotLanded();
        }

        stopped = false;

        const Position dir_offset{offset(direction)};
        Position next_position = position + (forward ? dir_offset : -dir_offset);

        for (auto &sensor : sensors) {
            if (!sensor->is_safe(next_position.get_x(), next_position.get_y())) {
                stopped = true;
                throw PositionIsUnsafe();
            }
        }

        position = next_position;
    }

    void rotate(bool right) {
        if (!landed) {
            throw RoverNotLanded();
        }

        stopped = false;

        if (right) {
            ++direction;
        } else {
            --direction;
        }
    }

    bool landed;
    bool stopped;
    Position position;
    Direction direction;
};

#endif // ROVER_STATE_H
