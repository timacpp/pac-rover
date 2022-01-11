//
// Created by Piotr Kamiński on 02/01/2022.
//

#ifndef SPACE_ROVER_COMMAND_H
#define SPACE_ROVER_COMMAND_H

#include <utility>
#include <vector>
#include <initializer_list>
#include <memory>
#include "rover.h"
#include "direction.h"

struct Command {
    virtual int move_rover(Rover &rover) = 0;
};

using ptr_to_command = std::shared_ptr<Command>;

struct MoveForward : Command {
    MoveForward() = default;

    int move_rover(Rover &rover) override {
        coordinates coords = rover.get_coordinates();
        switch (rover.get_direction()) {
            case Direction::NORTH:
                coords = {coords.first, coords.second + 1};
                break;
            case Direction::EAST:
                coords = {coords.first + 1, coords.second};
                break;
            case Direction::SOUTH:
                coords = {coords.first, coords.second - 1};
                break;
            case Direction::WEST:
                coords = {coords.first - 1, coords.second};
        }

        if (rover.check_and_go(coords) != 0)
            return 1;
        return 0;
    }
};

struct MoveBackward : Command {
    MoveBackward() = default;

    int move_rover(Rover &rover) override {
        coordinates coords = rover.get_coordinates();
        switch (rover.get_direction()) {
            case Direction::NORTH:
                coords = {coords.first, coords.second - 1};
                break;
            case Direction::EAST:
                coords = {coords.first - 1, coords.second};
                break;
            case Direction::SOUTH:
                coords = {coords.first, coords.second + 1};
                break;
            case Direction::WEST:
                coords = {coords.first + 1, coords.second};
        }

        if (rover.check_and_go(coords) != 0)
            return 1;
        return 0;
    }
};

struct RotateLeft : Command {
    RotateLeft() = default;

    int move_rover(Rover &rover) override {
        rover.set_direction(to_left(rover.get_direction()));
        return 0;
    }
};

struct RotateRight : Command {
    RotateRight() = default;

    int move_rover(Rover &rover) override {
        rover.set_direction(to_right(rover.get_direction()));
        return 0;
    }
};


struct Compose : Command {
    Compose(std::initializer_list<ptr_to_command> _commands) : commands{_commands} { }

    int move_rover(Rover &rover) override {
        for (auto &command : commands)
            if (command->move_rover(rover) != 0)
                return 1;
        return 0;
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
