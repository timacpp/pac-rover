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

    ptr_to_command c = move_forward();

    ptr_to_command cc = compose({move_forward(), move_forward(), rotate_left(), move_forward()});
    std::unordered_map<char, std::shared_ptr<Command>> comm;
    comm.insert({'A', c});
    comm.insert({'B', cc});
    comm.insert({'C', rotate_left()});
    comm.insert({'D', rotate_right()});

    vector<shared_ptr<Sensor>> sensors;
    Rover r{comm, sensors};
    r.land({0, 0}, Direction::EAST);
    cout << r;
    r.execute("C");
    cout << r;
    r.execute("C");
    cout << r;
    r.execute("C");
    cout << r;
    r.execute("C");
    cout << r;

    r.execute("D");
    cout << r;
    r.execute("D");
    cout << r;
    r.execute("D");
    cout << r;
    r.execute("D");
    cout << r;
    /*
    cout << r;
    r.execute("AAAAA");
    cout << r;
    r.execute("B");
    cout << r;
    r.execute("B");
    cout << r;
    r.execute("BA");
    cout << r;
    r.execute("BA");
    cout << r; */

}
