//
// Created by Piotr Kamiński on 02/01/2022.
//

#ifndef SPACE_ROVER_COMMAND_H
#define SPACE_ROVER_COMMAND_H

#include <utility>
#include <vector>
#include <initializer_list>
#include <memory>
#include "rover_state.h"
#include "direction.h"

struct Command {
    virtual void move_rover(RoverState& rover_state, const std::vector<std::unique_ptr<Sensor>>& sensors) = 0;
};

using ptr_to_command = std::shared_ptr<Command>;

struct MoveForward : Command {
    MoveForward() = default;

    void move_rover(RoverState& rover_state, const std::vector<std::unique_ptr<Sensor>>& sensors) override {
        rover_state.try_forward(sensors);
    }
};


struct MoveBackward : Command {
    MoveBackward() = default;

    void move_rover(RoverState& rover_state, const std::vector<std::unique_ptr<Sensor>>& sensors) override {
        rover_state.try_backward(sensors);
    }
};


struct RotateLeft : Command {
    RotateLeft() = default;

    void move_rover(RoverState& rover_state, const std::vector<std::unique_ptr<Sensor>>& sensors){
        rover_state.rotate_left();
    }
};

struct RotateRight : Command {
    RotateRight() = default;

    void move_rover(RoverState& rover_state, const std::vector<std::unique_ptr<Sensor>>& sensors) {
        rover_state.rotate_right();
    }
};


struct Compose : Command {
    Compose(std::initializer_list<ptr_to_command> _commands) : commands{_commands} { }

    void move_rover(RoverState& rover_state, const std::vector<std::unique_ptr<Sensor>>& sensors) {
        for (auto &command : commands)
            command->move_rover(rover_state, sensors);
    }

private:
    std::vector<ptr_to_command> commands;
};


#define MOVE_FORWARD 0
#define MOVE_BACKWARD 1
#define ROTATE_LEFT 2
#define ROTATE_RIGHT 3
ptr_to_command basic_commands[4];

ptr_to_command move_forward() {
    if (!basic_commands[MOVE_FORWARD])
        basic_commands[MOVE_FORWARD] = std::make_shared<MoveForward>();
    return basic_commands[MOVE_FORWARD];
}

ptr_to_command move_backward() {
    if (!basic_commands[MOVE_BACKWARD])
        basic_commands[MOVE_BACKWARD] = std::make_shared<MoveBackward>();
    return basic_commands[MOVE_BACKWARD];
}

ptr_to_command rotate_left() {
    if (!basic_commands[ROTATE_LEFT])
        basic_commands[ROTATE_LEFT] = std::make_shared<RotateLeft>();
    return basic_commands[ROTATE_LEFT];
}

ptr_to_command rotate_right() {
    if (!basic_commands[ROTATE_RIGHT])
        basic_commands[ROTATE_RIGHT] = std::make_shared<RotateRight>();
    return basic_commands[ROTATE_RIGHT];
}

ptr_to_command compose(std::initializer_list<ptr_to_command> command_list) {
    return std::make_shared<Compose>(command_list);
}

#endif //SPACE_ROVER_COMMAND_H
