#include <cassert>
#include <iostream>
#include <memory>

#include "../src/rover.h"
#include "../src/command.h"
#include "../src/direction.h"

struct TrueSensor : public Sensor {
    bool is_safe([[maybe_unused]] coordinate_t x,
                 [[maybe_unused]] coordinate_t y) override {
        return true;
    }
};

struct FalseSensor : public Sensor {
    bool is_safe([[maybe_unused]] coordinate_t x,
                 [[maybe_unused]] coordinate_t y) override {
        return false;
    }
};

// The output is:
// unknown
// (0, 0) EAST
// (1, 0) WEST
// (0, 0) WEST stopped
// (-3, 0) WEST
// (-1, -1) WEST stopped

int main() {
    // While building a rover, one can program commands
    auto rover = RoverBuilder()
            .program_command('F', move_forward())
            .program_command('B', move_backward())
            .program_command('R', rotate_right())
            .program_command('L', rotate_left())
            .program_command('U', compose({rotate_right(), rotate_right()}))
            .add_sensor(std::make_unique<TrueSensor>())
            .add_sensor(std::make_unique<TrueSensor>())
            .build();

    // Rover is controllable only after landing
    std::cout << rover << std::endl;
    try {
        rover.execute("F");
        assert(false);
    } catch (std::exception const& e) {
    }

    // After landing rover processes given commands
    rover.land({0, 0}, Direction::EAST);
    std::cout << rover << std::endl;
    rover.execute("FFBRLU");
    std::cout << rover << std::endl;

    // Rover stops if it doesn't know the command
    rover.execute("FXFFF");
    std::cout << rover << std::endl;

    // Examples of correct commands
    rover.execute("FFF");
    std::cout << rover << std::endl;

    // Rover stops if its sensors detect danger
    auto broken_rover = RoverBuilder()
            .program_command('X', move_forward())
            .add_sensor(std::make_unique<FalseSensor>())
            .build();
    broken_rover.land({-1, -1}, Direction::WEST);
    broken_rover.execute("X");
    std::cout << broken_rover << std::endl;
}