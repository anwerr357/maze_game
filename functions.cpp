// functions.cpp
#include "functions.hpp" // Include the header file
#include "cell.hpp"

 vector<vector<int>> direction = {{0,-1} , {0,1}, {-1,0} , {1,0} ,
        {1,1} , {1,-1} , {-1,-1},{-1,1}};
    

bool verfier_colonne_ligne(int a,int b, int n , int m  ){
    if(a>=1 && a<= n && b>=1 && b<=m ) return true;
    return false;
}

vector<pair<int, int>> reconstructPath(pair<int, int> start, pair<int, int> end, vector<vector<pair<int, int>>>& predecessor) {
    vector<pair<int, int>> path;
    pair<int, int> current = end;

    while (current != start) {
        path.push_back(current);
        current = predecessor[current.first][current.second];
    }
    path.push_back(start);

    reverse(path.begin(), path.end());
    return path;
}

pair<int,vector<pair<int,int>>> dijkstra( vector<vector<char>>& grille, vector<vector<int>>& cost_grid, pair<int, int> start, pair<int, int> end) {
    int rows = cost_grid.size()-1;
    int cols = cost_grid[0].size()-1;
    vector<vector<pair<int, int>>> predecessor(rows+1, vector<pair<int, int>>(cols+1, {-1, -1}));

    // Matrice de distances minimales
    vector<vector<int>> dist(rows+1, vector<int>(cols+1, INT_MAX));
    dist[start.first][start.second] = cost_grid[start.first][start.second];
    
    // File de priorité (min-heap)
    priority_queue<Cell, vector<Cell>, greater<Cell>> pq;
    pq.push(Cell(start.first, start.second, 0));
    
    while (!pq.empty()) {

        Cell current = pq.top();
        pq.pop();
        
        // Si on atteint la destination
        if (current.x == end.first && current.y == end.second) {
            vector<pair<int,int>> reconstructed_path = reconstructPath(start, end, predecessor);

            return {current.cost, reconstructed_path}  ;
        }
        
        // Explorer les voisins
        for (int i = 0; i < 8; ++i) {
            int nx = current.x + direction[i][0];
            int ny = current.y + direction[i][1];
            
            // Vérifier les limites de la grille
            if (nx >= 1 && nx <= rows && ny >= 1 && ny <= cols && grille[nx][ny]!='#') {
                int new_cost = current.cost + cost_grid[nx][ny];
                
                // Mettre à jour si meilleur chemin trouvé
                if (new_cost < dist[nx][ny]) {
                    dist[nx][ny] = new_cost;
                    pq.push(Cell(nx, ny, new_cost));
                    predecessor[nx][ny] = {current.x, current.y};
                }
            }
        }
    }
    
    return {-1 , {{-1,-1}}}; // Pas de chemin trouvé
}


void dfs(vector<vector<char>>& matrix, pair<int, int> start, pair<int, int> end, vector<pair<int, int>>& path, set<pair<int, int>>& visited, vector<vector<pair<int, int>>>& paths) {
    int rows = matrix.size()-1;
    int cols = matrix[0].size()-1;
        if (start == end) {
        paths.push_back(path);
        return;
    }

    visited.insert(start);

    for (auto& dir : direction) {
        int r = start.first + dir[0];
        int c = start.second + dir[1];

        if (r >= 1 && r <= rows && c >=1 && c <= cols && visited.find({r, c}) == visited.end() && matrix[r][c] != '#') {
            path.push_back({r, c}); // Add to the current path
            dfs(matrix, {r, c}, end, path, visited, paths); // Recurse
            path.pop_back(); // Backtrack
        }
    }


    visited.erase(start);
}

vector<vector<pair<int, int>>> find_all_paths(vector<vector<char>>& matrix, pair<int, int> start, pair<int, int> end) {
    vector<vector<pair<int, int>>> paths;
    vector<pair<int, int>> path = {start}; 
    set<pair<int, int>> visited;

    dfs(matrix, start, end, path, visited, paths);
    return paths;
}