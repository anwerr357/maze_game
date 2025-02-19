#include <bits/stdc++.h>
using namespace std;
// functions.hpp
#ifndef FUNCTIONS_HPP 
#define FUNCTIONS_HPP
#include <iostream> 
bool verfier_colonne_ligne(int a, int b, int n, int m);
pair<int,vector<pair<int,int>>> dijkstra(vector<vector<char>>& grille, vector<vector<int>>& cost_grid, pair<int, int> start, pair<int, int> end);
extern vector<vector<int>> direction;
void findAllPaths( vector<vector<char>>& grid,vector<vector<int>>& cost,  vector<vector<int>>& dist, vector<vector<pair<int, int>>>& paths, vector<pair<int, int>>& currentPath, int x, int y, pair<int, int> start) ;
void bfs(const vector<vector<char>>& grid,vector<vector<int>>& dist, pair<int, int> start) ;
bool dfs_check_path(int position_x, int position_y, vector<vector<char>>& maze ,pair<int,int>goal );

bool dfs_check(int position_x, int position_y, vector<vector<char>>& maze ,vector<vector<bool>>&visited,pair<int,int>goal );

#endif // FUNCTIONS_HPP