#ifndef MAZE_GENERATOR_HPP
#define MAZE_GENERATOR_HPP

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <utility>

using namespace std ; 
// Function declarations

void shuffleDirections(int directions[8]);


bool isInsideMaze(int x, int y, int n, int m);


vector<vector<char>> generateMazeWallsDFS(int x, int y, vector<vector<char>>& maze);


bool dfs(int x, int y, int index, const string& word, std::vector<std::vector<char>>& M, vector<pair<int, int>>& path);

vector<vector<char>> placeWordsDFS(const vector<string>& list, vector<vector<char>>& M);

vector<vector<char>> generateMaze(const vector<string> list, int d);
bool bfs_check(const vector<vector<char>>grid, pair<int, int> start,pair<int,int>end);
// dictionnaire 
#endif // MAZE_GENERATOR_HPP