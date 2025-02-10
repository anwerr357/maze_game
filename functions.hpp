#include <bits/stdc++.h>
using namespace std;
// functions.hpp
#ifndef FUNCTIONS_HPP // Include guard
#define FUNCTIONS_HPP
#include <iostream> // Include necessary headers
bool verfier_colonne_ligne(int a, int b, int n, int m);
pair<int,vector<pair<int,int>>> dijkstra(vector<vector<char>>& grille, vector<vector<int>>& cost_grid, std::pair<int, int> start, std::pair<int, int> end);
vector<vector<pair<int, int>>> find_all_paths(vector<vector<char>>& matrix, pair<int, int> start, pair<int, int> end);
extern vector<vector<int>> direction;







#endif // FUNCTIONS_HPP