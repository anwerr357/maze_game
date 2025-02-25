#include <bits/stdc++.h>
#include <unistd.h>
#include <cstdlib> 
#include <parallel/compatibility.h>
#include "pathTrie.hpp"
#include "cell.hpp"
#include "generate-matrix.hpp"
#include "functions.hpp" 
#include "count_score.hpp"
#include "get_countries.hpp"
#define WALL "█"
#define PLAYER "▲" 
#define LAST "▼"
#define FAST ios::sync_with_stdio(0), cin.tie(0),cout.tie(0)
#define RED "\033[31m"
#define RESET "\033[0m"
#define YELLOW "\033[33m"

using namespace std;
string preferdRegion;
map<int,string>map_regions_by_number;
map<string,vector<string>>countriesByRegion;
map<string,string>countryToRegion;
int count_score_func(string s, TrieNode* root){
    int score = 0 ;
    for(int i = 0;i<s.size();i++){
        string current_path_string = "";
        for(int j = i;j<s.size();j++){
            current_path_string+=s[j];
            if(searchKey(root,  current_path_string)) score+=5;
            if(countryToRegion[current_path_string]==preferdRegion) score+=5;
        }
    }   
    return score ;
}
  

void solve() {
    TrieNode* root = new TrieNode();
    // Api to get countries and their regions 
    string url = "https://restcountries.com/v3.1/all";
    string jsonData = fetchData(url);
    // randomCountries : map of words for creating the maze 
    vector<string> randomCountries={"Tunisia", "Germany","Canada" , "Italy","Sapin", "Egypt" , "Jordan" , "Qatar" , "Syria"};
    
    auto [currCountriesByRegion, currCountryToRegion] = extractCountriesByRegion(jsonData);
    countriesByRegion = currCountriesByRegion;
    countryToRegion = currCountryToRegion;
     if (!jsonData.empty()) {
        // Pick 100 random countries
        randomCountries = getRandomCountries(countriesByRegion, 100);
    } else {
        cerr << "Failed to fetch data from the API." << endl;
    }
   int nb_mots_dictionnaires =randomCountries.size();
   vector<string>filterCountry;
   // filter the countries
   for(int i = 0;i<nb_mots_dictionnaires;i++) {
            string  s = randomCountries[i];
            bool flag =false; 
            for(auto c  : s)
                {
                    if(!(c>=65 && c<=65+25) && !(c>=97 && c<=97+25)){
                         flag = true;       
                    }
                    
                }

            if(!flag) {
                filterCountry.push_back(s);
                insertKey(root,toLowerCase(s));
            }
    }
    set<string>allRegions;
    for(auto [k,v] : countryToRegion){
       allRegions.insert(v);
    }
    int count = 1 ;
    for(auto k : allRegions) map_regions_by_number[count]=k,count++;
    cout<<"Choose you prefered region !"<<endl;
    for(auto [k,v] : map_regions_by_number) {
        cout<<"Number: "<<k<<" Region: "<<v<<endl;
    }
    int region ; 
    cin>>region; 
    preferdRegion = map_regions_by_number[region];
    cout<<"Choose dificulity: "<<endl;
    cout<<"1: Easy"<<endl;
    cout<<"2: Medium"<<endl;
    cout<<"3: Hard"<<endl;
    int difficulty; 
    cin>>difficulty;
    if(difficulty<1) difficulty=1;
    if(difficulty>3) difficulty=3;


    vector<vector<char>> maze = generateMaze(filterCountry,difficulty);
    int start_X=0,start_Y=0;
    int destination_X=maze.size()-1,destination_Y=maze[0].size()-1;
    int rows = maze.size(),columns=maze[0].size();
    
    maze[start_X][start_Y]=' ';
    maze[destination_X][destination_Y]=' ';
    
    pair<int, vector<pair<int,int>>> shortest_path;
    vector<vector<int>>cost(rows+1,vector<int>(columns+1,1));
    int  shortest_path_cost;
    vector<pair<int,int>> shortest_path_reconstructed;



        //    shortest path with dijextra
        shortest_path = dijkstra(maze , cost ,{start_X,start_Y},{destination_X,destination_Y} );
        shortest_path_cost=shortest_path.first;
        shortest_path_reconstructed=shortest_path.second;   // reconstructed path .

        
        // Compute shortest distances using BFS
        vector<vector<int>> dist(rows+1, vector<int>(columns+1, -1));
        pair<int,int> start =  {start_X,start_Y};
        pair<int,int> goal = {destination_X,destination_Y} ;
        bfs(maze,dist ,start);

        // If no path exists
        if (dist[destination_X][destination_Y] == -1) {
            cout << "No path exists!" << endl;
            return ;
        }

        // Find all shortest paths
       vector<vector<pair<int, int>>> allPaths;
       vector<pair<int, int>> currentPath;
       findAllPaths(maze,cost, dist, allPaths, currentPath, goal.first, goal.second, start);

        
        vector<vector<bool>>visited(rows+1,vector<bool>(columns+1,(false)));

        // This lambda  function is designed to display the grid at a specific point during the game.
        auto displayMaze = [&](int playerRow, int playerCol ){
            string padding(maze.size(), ' '); // Offset for alignment
            int width = maze[0].size();  // Maze width

            // Top Border
            cout <<YELLOW<< padding <<" +" << string(width*2, '-') << "+" <<RESET<<endl;

          for (int i = 0; i < rows; i++) {
            cout <<YELLOW<< padding << "| "<<RESET;
            for (int j = 0; j <columns; j++) {
                    if(i==playerRow && j == playerCol) visited[i][j] = true;
                    if(visited[i][j] && maze[i][j]== '#') cout<< WALL<<" "; // unvisited cells represented by a simple question mark . 
                    else if(i==playerRow && j == playerCol) cout<<RED<<PLAYER<<RESET<<" "; // unvisited cells represented by a simple question mark . 
                    else if(visited[i][j]) cout<<maze[i][j]<<" ";
                    else if(i==destination_X && j==destination_Y)cout<< RED<<LAST<<RESET<<" ";
                    else if(abs(i-playerRow)<=1 && abs(j-playerCol)<=1) cout<<maze[i][j]<<" ";
                    else if(!visited[i][j] && maze[i][j]>=65 && maze[i][j]<=65+25) cout<<YELLOW<<'?'<<RESET<<" ";
                    else if(!visited[i][j])cout<<'?'<<" ";
                    
            }
            cout << YELLOW<<" |" <<RESET<< endl;
        }
            cout << YELLOW <<padding<<" + " << string(width*2, '-') << "+" <<RESET<<endl;
    };
    int player_row = start_X;
    int player_col = start_Y;
    cout<<player_row<<" "<<player_col<<endl;
    long long score = 0;
    string current_path_string = "" ;
    PathTrie trie({start_X, start_Y});
    for(auto path : allPaths){
        trie.insert(path);
    }
    

    vector<pair<int,int>>current_path;
    current_path.push_back({start_X,start_Y});
    //displayMaze(player_row, player_col);

    while (true) {
     
        if(current_path.size()>1){
        cout << "Do you want to backtrack? Enter 'Y' if yes." << endl;
        char descision; 
            cin>>descision;
            if(descision=='Y'){
                auto to_delete_step = current_path.back();
                visited[to_delete_step.first][to_delete_step.second]=false;
                current_path.pop_back();
                auto last_step = current_path.back();
                player_row=last_step.first;
                player_col=last_step.second;
                current_path_string = current_path_string.substr(0,current_path_string.size()-1);

            }

        }
        displayMaze(player_row, player_col);

          cout << "Please enter a number corresponding to the movement direction:" << endl
            << "7: Up-Left   | 8: Up   | 9: Up-Right" << endl
            << "4: Left      | 5: hint | 6:Right" << endl
            << "1: Down-Left | 2: Down | 3: Down-Righ" << endl
            << "0: Backtarack" << endl;
        string input;
        // ****Capture the pressed key****
        cin >> input;
        // ****Player movement****
         // Displaying the matrix using the lambda function  
        // #ifdef _WIN32
        //     system("cls");  // Windows
        // #else
        //     system("clear"); // Linux/macOS
        // #endif  
        cout<<input<<endl;
        map<int,pair<int,int>>dir;
        dir[1]={1,-1},dir[2]={1,0},dir[3]={1,1},dir[4]={0,-1},dir[6]={0,1},dir[7]={-1,-1},dir[8]={-1,0},dir[9]={-1,1};
          if(input[0]>='1' && input[0]<='8' && input.size()==1){
                int inputNumb = input[0]-'0'; 
                cout<<"inputNumb  "<<inputNumb<<endl;
                // ici on a fait input -- car le tableau est indexé de 0
                int next_row = player_row+dir[inputNumb].first;
                int next_col = player_col+dir[inputNumb].first;
                if(current_path_string.size()>=1)cout<<"Current Score : "<<count_score_func(current_path_string,root)<<endl;
                
                if (verfier_colonne_ligne(next_col, next_row,rows,columns)==true){
                         // verify if the player reached the goal
                        if(maze[next_row][next_col] == '#'){
                            visited[next_row][next_col] = true;
                            cout << "This point in the maze is a wall. Please choose another direction." << endl;
                            continue;
                        }
                        if (next_row == destination_X && next_col == destination_Y) {
                                cout << "Congratulations! You have reached the goal!" << endl;
                                score = count_score_func(current_path_string,root);
                                double denom=1;
                                double bonus = (denom/current_path_string.size())*100;
                                if(trie.contains(current_path)) bonus+=10;
                                cout << "Your score is: " << score + bonus << endl;
                                cout << "HERE IT IS YOUR PATH: " << current_path_string << endl;
                                for(auto k : shortest_path_reconstructed){
                                    cout<<"("<<k.first<<" "<<k.second<<") "; 
                                }
                                cout<<endl;
                                break;
                        }
                        cout << "Would you like a hint about the validity of your current path ? Enter 'Y'." << endl;                 
                        string hint_current; 
                        cin>>hint_current;
                        if(toupper(hint_current[0])=='Y'){
                                if(trie.contains_prefix(current_path)){
                                        cout << "YES! CONTINUE!." << endl;
                                }
                                else if(dfs_check_path(player_row,player_col,maze,{destination_X,destination_Y})){
                                        cout << "Okay not that bad, you still have a chance to complete the game." << endl;
                                }
                                else {
                                        cout << "It's time to backtrack." << endl;
                                        
                                }
                        }
                        player_row = next_row ; 
                        player_col = next_col ; 
                        current_path.push_back({player_row,player_col});
                        current_path_string+=maze[next_row][next_col];
                        
                 }
                else {
                     cout << "You have gone outside the boundaries of the maze." << endl;
                     
                }

            }
            else{
                cout << "This key is not recognized" << endl;
                            
            }
    
    }

}
int main() {
    FAST;
//  #ifndef ONLINE_JUDGE
//    //freopen("input.txt", "r", stdin);
//    // freopen("output.txt", "w", stdout);
//  #endif
    int t = 1;
    //cin >> t;
   
    while (t--) solve();
    return  0;
}
