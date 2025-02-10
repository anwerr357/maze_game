// cell.hpp
#ifndef CELL_HPP // Include guard
#define CELL_HPP
#include <iostream>
#include <vector>
#include <string>
using namespace std;
// Define the Cell struct
struct Cell {
    int x, y;       // Coordinates
    int cost;       // Cost to reach this cell

    // Constructor
    Cell(int x = 0, int y = 0, int cost = 0) : x(x), y(y), cost(cost) {}

    // Overload the > operator for priority_queue
    bool operator>(const Cell& other) const {
        return cost > other.cost;
    }
};

#endif // CELL_HPP