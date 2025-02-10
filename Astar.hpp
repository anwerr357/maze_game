#include <bits/stdc++.h>
using namespace std;

#ifndef ASTAR_HPP // Include guard
#define ASTAR_HPP
// Structure to represent a cell in the grid
pair<int, vector<pair<int, int>>> aStar(vector<vector<char>>& grid, pair<int, int> start, pair<int, int> end);
#endif // ASTAR_H