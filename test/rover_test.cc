#include <cassert>
#include <iostream>
#include <memory>

#include "../src/rover.h"
#include "../src/command.h"
#include "../src/direction.h"

// import "../src/rover"; // TODO: idk how to import from a subdirectory

using namespace std;

int main() {
    // Podczas budowy łazika można zaprogramawać jego komendy oraz ustawić różne czujniki.
    Rover r{};
    cout << r;
    r.land({0, 0}, Direction::EAST);
    cout << r;
    ptr_to_command c = move_forward();
    c->move_rover(r);
    cout << r;
    ptr_to_command cc = compose({move_forward(), move_forward(), rotate_left(), move_forward()});
    cc->move_rover(r);
    cout << r;
}
