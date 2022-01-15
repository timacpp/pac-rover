#ifndef SPACE_ROVER_H
#define SPACE_ROVER_H

#include <string>
#include <vector>
#include <unordered_map>
#include "direction.h"
#include "position.h"
#include "command.h"
#include "rover_state.h"


class Rover {
private:
    RoverState state;
    std::vector<std::shared_ptr<Sensor>> sensors;
    std::unordered_map<char, std::shared_ptr<Command>> buttons;

public:
    Rover() = delete;

    Rover(std::unordered_map<char, std::shared_ptr<Command>>& _buttons,
          std::vector<std::shared_ptr<Sensor>>& _sensors) :
          buttons(std::move(_buttons)),
          sensors(std::move(_sensors))
          { };

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
        return ostream << rover.state << '\n';
    }
};

#endif // SPACE_ROVER_H
