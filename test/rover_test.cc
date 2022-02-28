#include <cassert>
#include <iostream>
#include <memory>

#include "../src/rover.h"
#include "../src/command.h"
#include "../src/direction.h"

using namespace std;

int main() {
    command_ptr c = move_forward();

    command_ptr cc = compose({move_forward(), move_forward(), rotate_left(), move_forward()});
    std::unordered_map<char, command_ptr> comm;
    comm.insert({'A', c});
    comm.insert({'B', cc});
    comm.insert({'C', rotate_left()});
    comm.insert({'D', rotate_right()});

    vector<sensor_ptr> sensors;
    Rover r{std::move(comm), std::move(sensors)};
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
    cout << r;
}
