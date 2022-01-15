#ifndef COMMAND_H
#define COMMAND_H

#include <memory>
#include <vector>
#include <initializer_list>

#include "rover_state.h"

struct Command {
    virtual void perform(RoverState& state, const std::vector<sensor_ptr>& sensors) const = 0;

    virtual ~Command() = default; // TODO: default is bad
};

using command_ptr = std::shared_ptr<Command>;

struct MoveForward : public Command {
    MoveForward() = default;

    ~MoveForward() override = default;

    void perform(RoverState& state, const std::vector<sensor_ptr>& sensors) const override {
        state.advance_forward(sensors);
    }
};

struct MoveBackward : public Command {
    MoveBackward() = default;

    ~MoveBackward() override = default;

    void perform(RoverState& state, const std::vector<sensor_ptr>& sensors) const override {
        state.advance_backward(sensors);
    }
};

struct RotateLeft : public Command {
    RotateLeft() = default;

    ~RotateLeft() override = default;

    void perform(RoverState& state, const std::vector<sensor_ptr>& sensors) const override {
        state.rotate_left();
    }
};

struct RotateRight : public Command {
    RotateRight() = default;

    ~RotateRight() override = default;

    void perform(RoverState& state, const std::vector<sensor_ptr>& sensors) const override {
        state.rotate_right();
    }
};

struct Compose : public Command {
    Compose(std::initializer_list<command_ptr> commands) : commands{commands} {}

    ~Compose() override {  // TODO: idk if it's good
        commands.clear();
    }

    void perform(RoverState& state, const std::vector<sensor_ptr>& sensors) const override {
        for (const auto& command : commands) {
            command->perform(state, sensors);
        }
    }

private:
    std::vector<command_ptr> commands;
};

#define MOVE_FORWARD 0
#define MOVE_BACKWARD 1
#define ROTATE_LEFT 2
#define ROTATE_RIGHT 3
command_ptr basic_commands[4];

command_ptr move_forward() {
    if (!basic_commands[MOVE_FORWARD])
        basic_commands[MOVE_FORWARD] = std::make_shared<MoveForward>();
    return basic_commands[MOVE_FORWARD];
}

command_ptr move_backward() {
    if (!basic_commands[MOVE_BACKWARD])
        basic_commands[MOVE_BACKWARD] = std::make_shared<MoveBackward>();
    return basic_commands[MOVE_BACKWARD];
}

command_ptr rotate_left() {
    if (!basic_commands[ROTATE_LEFT])
        basic_commands[ROTATE_LEFT] = std::make_shared<RotateLeft>();
    return basic_commands[ROTATE_LEFT];
}

command_ptr rotate_right() {
    if (!basic_commands[ROTATE_RIGHT])
        basic_commands[ROTATE_RIGHT] = std::make_shared<RotateRight>();
    return basic_commands[ROTATE_RIGHT];
}

command_ptr compose(std::initializer_list<command_ptr> command_list) {
    return std::make_shared<Compose>(command_list);
}

#endif // COMMAND_H
