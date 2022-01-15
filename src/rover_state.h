//
// Created by Piotr Kamiński on 15/01/2022.
//

#ifndef SPACE_ROVER_ROVER_STATE_H
#define SPACE_ROVER_ROVER_STATE_H

using coordinates = std::pair<coordinate_t, coordinate_t>;

struct Sensor {
    virtual bool is_safe(coordinate_t x, coordinate_t y) = 0;

    virtual ~Sensor() { }
};

class SensorFalse : public std::exception {

};

class RoverState {
private:
    bool landed;
    bool stopped;
    Position current_position;
    Direction current_direction;

public:
    RoverState() : landed{false}, stopped{false}, current_position{} { }

    void land(Position landing_spot, Direction facing) {
        landed = true;
        stopped = false;
        current_position = landing_spot;
        current_direction = facing;
    }

    void stop_rover() {
        stopped = true;
    }

    void try_forward(const std::vector<std::unique_ptr<Sensor>> &sensors) {
        if (!landed)
            throw std::exception();
        stopped = false;
        Position position = current_position;
        switch (current_direction) {
            case Direction::NORTH:
                position += {0, 1};
                break;
            case Direction::EAST:
                position += {1, 0};
                break;
            case Direction::SOUTH:
                position += {0, -1};
                break;
            case Direction::WEST:
                position += {-1, 0};
        }

        for (auto &sensor : sensors) {
            if (!sensor->is_safe(position.get_x(), position.get_y())) {
                stopped = true;
                throw SensorFalse();
            }
        }

        current_position = position;
    }

    void try_backward(const std::vector<std::unique_ptr<Sensor>> &sensors) {
        if (!landed)
            throw std::exception();
        stopped = false;
        Position position = current_position;
        switch (current_direction) {
            case Direction::NORTH:
                position += {0, -1};
                break;
            case Direction::EAST:
                position += {-1, 0};
                break;
            case Direction::SOUTH:
                position += {0, 1};
                break;
            case Direction::WEST:
                position += {1, 0};
        }

        for (auto &sensor : sensors) {
            if (!sensor->is_safe(position.get_x(), position.get_y())) {
                stopped = true;
                throw SensorFalse();
            }
        }

        current_position = position;
    }

    void rotate_right() {
        if (!landed)
            throw std::exception();
        stopped = false;
        ++current_direction;
    }

    void rotate_left() {
        if (!landed)
            throw std::exception();
        stopped = false;
        --current_direction;
    }

    friend std::ostream& operator<<(std::ostream& out, const RoverState& state) noexcept {
        if (!state.landed)
            return out << "unknown";

        out << state.current_position << " " << state.current_direction;
        if (state.stopped)
            out << " " << "stopped";
        return out;
    }
};

#endif //SPACE_ROVER_ROVER_STATE_H
