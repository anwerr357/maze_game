#include <bits/stdc++.h>
#include "Astar.hpp"
using namespace std;

// Structure to represent a cell in the grid
struct Cell {
    int x, y;
    double cost; // f(n) = g(n) + h(n)
    bool operator>(const Cell& other) const {
        return cost > other.cost;
    }
};

// Heuristic function: Euclidean distance (for 8-direction movement)
double heuristic(int x1, int y1, int x2, int y2) {
    return sqrt(pow(abs(x1 - x2), 2) + pow(abs(y1 - y2), 2));
}

// Function to reconstruct the shortest path
vector<pair<int, int>> reconstructPath_Astar(pair<int, int> start, pair<int, int> end, vector<vector<pair<int, int>>>& predecessor) {
    vector<pair<int, int>> path;
    pair<int, int> current = end;

    // Backtrack from the end to the start
    while (current != start) {
        path.push_back(current);
        current = predecessor[current.first][current.second];
    }
    path.push_back(start);

    // Reverse to get the path from start to end
    reverse(path.begin(), path.end());
    return path;
}

// A* Algorithm
pair<int, vector<pair<int, int>>> aStar(vector<vector<char>>& grid, pair<int, int> start, pair<int, int> end) {
    int rows = grid.size()-1;
    int cols = grid[0].size()-1;

    // Matrice de distances minimales (g(n))
    vector<vector<int>> g(rows+1, vector<int>(cols+1, INT_MAX));
    g[start.first][start.second] = 0;

    // Matrice des prédécesseurs
    vector<vector<pair<int, int>>> predecessor(rows+1, vector<pair<int, int>>(cols+1, {-1, -1}));

    // File de priorité (min-heap) based on f(n) = g(n) + h(n)
    priority_queue<Cell, vector<Cell>, greater<Cell>> pq;
    pq.push(Cell{start.first, start.second, g[start.first][start.second] + heuristic(start.first, start.second, end.first, end.second)});

    // Directions (8 directions)
    int direction[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    bool flag = false;
    while (!pq.empty()) {
        Cell current = pq.top();
        pq.pop();

        // Si on atteint la destination
        if (current.x == end.first && current.y == end.second) {
            flag = true;
        }

        // Explorer les voisins
        for (int i = 0; i < 8; i++) {
            int nx = current.x + direction[i][0];
            int ny = current.y + direction[i][1];

            // Vérifier les limites de la grille
            if (nx >= 1 && nx <= rows && ny >= 1 && ny <= cols && grid[nx][ny] != '#') {
                int new_g = g[current.x][current.y] + 1; // Cost is always 1

                // Mettre à jour si meilleur chemin trouvé
                if (new_g < g[nx][ny]) {
                    g[nx][ny] = new_g;
                    predecessor[nx][ny] = {current.x, current.y};
                    double f = new_g + heuristic(nx, ny, end.first, end.second); // f(n) = g(n) + h(n)
                    pq.push(Cell{nx, ny, f});
                }
            }   
        }
    }
    if(flag){
        vector<pair<int, int>> reconstructed_path = reconstructPath_Astar(start, end, predecessor);
            return {g[end.first][end.second], reconstructed_path};
    }
    return {-1, {{-1, -1}}};
}