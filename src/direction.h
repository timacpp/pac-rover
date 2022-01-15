#ifndef DIRECTION_H
#define DIRECTION_H

#include <cstdint>
#include <array>

enum class Direction : uint8_t {
    NORTH = 0x0,
    EAST  = 0x1,
    SOUTH = 0x2,
    WEST  = 0x3,
};

namespace {
    using ordinal_t = std::underlying_type<Direction>::type;

    constexpr ordinal_t MAX_ORDINAL{
        static_cast<ordinal_t>(std::max({
            Direction::NORTH, Direction::SOUTH,
            Direction::WEST, Direction::EAST
        }))
    };

    constexpr std::array<std::string_view, MAX_ORDINAL + 1> DIRECTION_NAME = {
            "NORTH", "EAST", "SOUTH", "WEST"
    };

    constexpr std::array<Position, MAX_ORDINAL + 1> DIRECTION_OFFSET = {
            Position(0, 1), Position(1, 0),
            Position(0, -1), Position(-1, 0)
    };
}

Direction& operator++(Direction& dir) {
    auto next_ordinal{static_cast<ordinal_t>(dir) + 1};

    next_ordinal %= (MAX_ORDINAL + 1);
    dir = static_cast<Direction>(next_ordinal);
    return dir;
}

Direction& operator--(Direction& dir) {
    auto next_ordinal{static_cast<ordinal_t>(dir) - 1};

    next_ordinal = (next_ordinal + MAX_ORDINAL + 1) % (MAX_ORDINAL + 1);
    dir = static_cast<Direction>(next_ordinal);

    return dir;
}

Position offset(const Direction& dir) noexcept {
    return DIRECTION_OFFSET[static_cast<ordinal_t>(dir)];
}

std::ostream& operator<<(std::ostream& out, const Direction& dir) {
    return out << DIRECTION_NAME[static_cast<ordinal_t>(dir)];
}


#endif // DIRECTION_H
