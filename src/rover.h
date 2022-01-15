#ifndef SPACE_ROVER_H
#define SPACE_ROVER_H

#include <vector>
#include <unordered_map>

#include "command.h"
#include "position.h"
#include "direction.h"
#include "rover_state.h"

class RoverBuilder;

class Rover {
public:
    void land(Position&& coord, Direction&& direction) {
        state.set(coord, direction);
    };

    void execute(std::string&& program) {
        try {
            for (char subprogram : program) {
                auto command_it = buttons.find(subprogram);
                if (command_it == buttons.end()) {
                    state.stop_rover();
                    break;
                }
                else {
                    command_it->second->perform(state, sensors);
                }
            }
        }
        catch (SensorFalse &s_false) { }
    }

    void execute(std::string& program) {
        execute(std::move(program));
    }

    friend std::ostream& operator<<(std::ostream& ostream, const Rover& rover) {
        return ostream << rover.state;
    }

private:
    friend class RoverBuilder;

    RoverState state;
    std::vector<sensor_ptr> sensors;
    std::unordered_map<char, command_ptr> buttons;

    Rover(std::unordered_map<char, command_ptr>&& buttons, std::vector<sensor_ptr>&& sensors) :
            buttons(std::move(buttons)), sensors(std::move(sensors)) {};
};

class RoverBuilder {
public:
    RoverBuilder() = default;

    RoverBuilder& program_command(char button, command_ptr&& command) {
        buttons[button] = std::move(command);
        return *this;
    }

    RoverBuilder& add_sensor(sensor_ptr&& sensor) {
        sensors.push_back(std::move(sensor));
        return *this;
    }

    Rover build() {
        return {std::move(buttons), std::move(sensors)};
    }
private:
    std::vector<sensor_ptr> sensors;
    std::unordered_map<char, command_ptr> buttons;
};

#endif // SPACE_ROVER_H
