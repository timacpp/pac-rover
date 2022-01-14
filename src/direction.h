#ifndef DIRECTION_H
#define DIRECTION_H

#include <cstdint>
#include <array>

using ordinal_t = uint8_t;

enum class Direction : ordinal_t {
    NORTH = 0x0,
    EAST  = 0x1,
    SOUTH = 0x2,
    WEST  = 0x3,
};

constexpr ordinal_t MAX_ORDINAL{
    static_cast<ordinal_t>(std::max({
        Direction::NORTH, Direction::SOUTH,
        Direction::WEST, Direction::EAST
    }))
};

std::array<std::string_view, MAX_ORDINAL + 1> DIRECTION_NAME {
    "NORTH", "EAST", "SOUTH", "WEST"
};

std::ostream& operator<<(std::ostream& out, Direction& dir) {
    return out << DIRECTION_NAME[static_cast<ordinal_t>(dir)];
}

Direction& operator++(Direction& dir) {
    const auto next_ordinal{static_cast<ordinal_t>(dir) + 1};
    dir = static_cast<Direction>(next_ordinal % MAX_ORDINAL);
    return dir;
}

Direction& operator--(Direction& dir) {
    const auto next_ordinal{static_cast<ordinal_t>(dir) - 1};
    dir = static_cast<Direction>((MAX_ORDINAL + next_ordinal) % MAX_ORDINAL);
    return dir;
}


#endif // DIRECTION_H
