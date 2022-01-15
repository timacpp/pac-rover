#ifndef SPACE_ROVER_H
#define SPACE_ROVER_H

#include <string>
#include <vector>
#include <unordered_map>
#include "direction.h"
#include "position.h"
#include "command.h"
#include "rover_state.h"

class RoverBuilder;

class Rover {
    friend class RoverBuilder;
private:
    RoverState state;
    std::vector<std::unique_ptr<Sensor>> sensors;
    std::unordered_map<char, std::shared_ptr<Command>> buttons;

    Rover(std::unordered_map<char, std::shared_ptr<Command>>&& _buttons,
          std::vector<std::unique_ptr<Sensor>>&& _sensors) :
            buttons(std::move(_buttons)),
            sensors(std::move(_sensors))
    { };

public:
    void land(Position _coord, Direction _direction) {
        state.land(_coord, _direction);
    };

    void execute(std::string&& program) {
        try {
            for (char c : program) {
                auto command = buttons.find(c);
                if (command == buttons.end()) {
                    state.stop_rover();
                    break;
                }
                else {
                    command->second->move_rover(state, sensors);
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
};

class RoverBuilder {
    std::vector<std::unique_ptr<Sensor>> sensors;
    std::unordered_map<char, std::shared_ptr<Command>> buttons;
public:
    RoverBuilder() = default;

    RoverBuilder& program_command(char button, std::shared_ptr<Command>&& command) {
        buttons.insert({button, std::move(command)});
        return *this;
    }

    RoverBuilder& add_sensor(std::unique_ptr<Sensor> sensor) {
        sensors.push_back(std::move(sensor));
        return *this;
    }

    Rover build() {
        return {std::move(buttons), std::move(sensors)};
    }
};

#endif // SPACE_ROVER_H
