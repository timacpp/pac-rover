//
// Created by Piotr Kamiński on 02/01/2022.
//

#ifndef SPACE_ROVER_COMMAND_H
#define SPACE_ROVER_COMMAND_H

#include "rover.h"

class rover_command {
public:
    virtual void move_rover(Rover &rover) = 0;
};

class move_forward : public rover_command {
public:
    move_forward() {};

    void move_rover(Rover &rover) override {

    };
};


#endif //SPACE_ROVER_COMMAND_H
