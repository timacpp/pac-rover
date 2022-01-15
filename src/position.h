#ifndef POSITION_H
#define POSITION_H

#include <cstdint>
#include <ostream>

using coordinate_t = int64_t;

class Position {
public:
    constexpr Position() : Position(0, 0) {}

    constexpr Position(coordinate_t x, coordinate_t y) : x{x}, y{y} {}

    Position& operator=(const Position&) = default;

    coordinate_t get_x() const noexcept {
        return x;
    }

    coordinate_t get_y() const noexcept {
        return y;
    }

    Position& operator+=(const Position& pos) noexcept {
        return *this = *this + pos;
    }

    friend Position operator+(const Position& first, const Position& second) noexcept {
        return {first.x + second.x, first.y + second.y};
    }

    friend Position operator-(const Position& pos) noexcept {
        return {-pos.x, -pos.y};
    }

    friend std::ostream& operator<<(std::ostream& out, const Position& pos) noexcept {
        return out << '(' << pos.x << ", " << pos.y << ')';
    }

private:
    coordinate_t x;
    coordinate_t y;
};

#endif // POSITION_H
