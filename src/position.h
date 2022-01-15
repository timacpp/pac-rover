#ifndef POSITION_H
#define POSITION_H

#include <cstdint>
#include <ostream>

using coordinate_t = int64_t;

class Position {
public:
    Position() : Position(0, 0) {}

    Position(coordinate_t x, coordinate_t y) : x{x}, y{y} {}

    Position &operator=(const Position&) = default;

    coordinate_t get_x() const noexcept {
        return x;
    }

    coordinate_t get_y() const noexcept {
        return y;
    }

    Position& operator+=(const Position& pos) noexcept {
        this->x += pos.x;
        this->y += pos.y;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Position& pos) noexcept {
        return out << '(' << pos.x << ", " << pos.y << ')';
    }

private:
    coordinate_t x;
    coordinate_t y;
};


#endif // POSITION_H
