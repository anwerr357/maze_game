#include <bits/stdc++.h>
#include <unistd.h> // Pour usleep() sur Linux
#include <cstdlib>  // Pour system()
#include <parallel/compatibility.h>
#include "pathTrie.hpp"
#include "cell.hpp"
#include "Astar.hpp"

#include "functions.hpp" // Include the header file of functions.cpp
#include "count_score.hpp" // Include the header file of count_score.cpp
#define FAST ios::sync_with_stdio(0), cin.tie(0),cout.tie(0)
using namespace std;

//  vector<vector<int>> direction = {{0,-1} , {0,1}, {-1,0} , {1,0} ,
//         {1,1} , {1,-1} , {-1,-1},{-1,1}};
       
int count_score_func(string s, TrieNode* root){
    int score = 0 ;
    for(int i = 0;i<s.size();i++){
        string chemin = "";
        for(int j = i;j<s.size();j++){
            chemin+=s[j];
            if(searchKey(root,  chemin)) score++;
        }
    }   
    return score ;
}
  

void solve() {
       TrieNode* root = new TrieNode();
    //    int nb_mots_dictionnaires;
    //     cin>>nb_mots_dictionnaires;
    //     for(int i = 0;i<nb_mots_dictionnaires;i++) {
    //         string s; 
    //         cin>>s;
    //         insertKey(root , s) ; 
    //     }


        int nombre_lignes , nombres_colonnes;

        cout<<"entrer le nombre de lignes "<<endl;
        // lire le nombre de colonnes et lignes du grille
        cin>>nombre_lignes;
        cout<<"entrez le nombre de colonnes"<<endl;
        cin>>nombres_colonnes;


        // déclarer la grille correspond a ce taille 
        vector<vector<char>> grille(nombre_lignes+1,vector<char>(nombres_colonnes+1));
        vector<vector<bool>>visited(nombre_lignes+1,vector<bool>(nombres_colonnes+1,(false)));

        // matrice des couts pour aller a chaque noeud 
       vector<vector<int>> couts(nombre_lignes+1,vector<int>(nombres_colonnes+1));

        
        int depart_X,depart_Y,position_X , position_Y,arrive_X ,arrive_Y;
       // ecrire la case de départ avec l'abscisse et l'ordonnée correspondants
       cout<<"entrez les cordonnées du case de départ "<<endl;
       cin>>depart_X>>depart_Y;
       cout<<"entrez les cordonnées du case d'arrivée "<<endl;
       cin>>arrive_X>>arrive_Y;


        
        
        
        for(int i = 1;i<=nombre_lignes;i++){
            for(int j =1 ;j<=nombres_colonnes;j++){
                cin>>grille[i][j];
            }
        }

        pair<int, vector<pair<int,int>>> shortest_path;
        int  shortest_path_cost;
        vector<pair<int,int>> shortest_path_reconstructed;
      // lire la matrice des couts si c'est possible à faire  . 
        cout<<"est ce que le passage d'une noeud necessite un poids variable (peut etre different de 1)"<<endl;
        cout<<"si oui tapez 'Y' sinon tapez 'N'"<<endl;
        char weighted_graph;
        cin>>weighted_graph;
        if(toupper(weighted_graph)=='Y'){
                for(int i = 1;i<=nombre_lignes;i++){
                for(int j =1 ;j<=nombres_colonnes;j++){
                    cin>>couts[i][j];
                }
            
            }
        
        
            // shortest path with dijextra
            shortest_path = dijkstra(grille , couts ,{depart_X,depart_Y},{arrive_X,arrive_Y} );
            shortest_path_cost=shortest_path.first;
            shortest_path_reconstructed=shortest_path.second; 

        }
        // shortest path with A* algorithm in case the graph is unwegihted (what i mean each node cost is = 1) . 
        auto shortest_path_Astar = aStar(grille, {depart_X,depart_Y}, {arrive_X,arrive_Y});  
        int shortest_path_Astar_cost = shortest_path_Astar.first;
        auto shortest_path_Astar_reconstructed = shortest_path_Astar.second;




        if(shortest_path_Astar_cost == -1){
            cout<<"il n'y a aucun chemin a traverser dans cette grille"<<endl;
            return; 
        }
        for(auto k : shortest_path_Astar_reconstructed){
            cout<<"("<<k.first<<" "<<k.second<<") ";
        }
        cout<<endl;
        // cette fonction lambda a comme but d'afficher la grille a un certain moment du jeu
         auto afficherGrille = [&](int playerRow, int playerCol ){
        //system("cls"); // Efface l'écran (Windows)
         //cout << "\033[2J\033[1;1H" << std::flush;
        for (int i = 1; i <= nombre_lignes; i++) {
            for (int j = 1; j <= nombres_colonnes; j++) {
                    if(i==position_X && j == position_Y) visited[i][j] = true;
                    if(visited[i][j])  cout << grille[i][j]<<" "; // Les cases vides sont représentées par caractere . 
                    else cout<<"? ";
            }
            cout << endl;
        }
    };
     
            
    position_X = depart_X;
    position_Y = depart_Y;
    long long score = 0;
    string chemin = "" ;
    vector<vector<pair<int, int>>>allPaths ; 
    pair<int,int>start = {depart_X,  depart_Y};
    pair<int,int>end = {arrive_X,  arrive_Y};
    allPaths = find_all_paths(grille, start,  end);
    PathTrie trie({depart_X, depart_Y});
    for(auto path : allPaths){
         trie.insert(path);
    }
    
        

    chemin+=grille[depart_X][depart_Y];
    vector<pair<int,int>>current_path;
    current_path.push_back({depart_X,depart_Y});
    while (true) {
        //Affichage de la matrice avec la fonction lambda
        if(current_path.size()>1){
            cout<<"tu veux faire une retour en arriére ou non ? 'Y' "<<endl;
            char descision; 
            cin>>descision;
            if(descision=='Y'){
                auto to_delete_step = current_path.back();
                visited[to_delete_step.first][to_delete_step.second]=false;
                current_path.pop_back();
                auto last_step = current_path.back();
                position_X=last_step.first;
                position_Y=last_step.second;
                chemin = chemin.substr(0,chemin.size()-1);

            }

        }
        afficherGrille(position_X, position_Y);

        // Gestion des entrées clavier
        cout << "Veuillez entrer un numéro correspondant à la direction de déplacement :" << endl
            << "1: Gauche, 2: Droite, 3: Haut, 4: Bas, " << endl
            << "5: Bas-Droite, 6: Bas-Gauche, 7: Haut-Gauche, 8: Haut-Droite" << endl;
        int input; 
        // ****Capture la touche pressée****
        cin>>input;
        // ****Déplacement du joueur****
       
          if(input>=1 && input<=8){
                input--; 
                // ici on a fait input -- car le tableau est indexé de 0
                int prochaine_ligne = position_X+direction[input][0];
                int prochaine_colonne = position_Y+direction[input][1];
                if (verfier_colonne_ligne(prochaine_colonne, prochaine_ligne,nombre_lignes,nombres_colonnes)==true){
                         // Vérification si le joueur atteint le point d'arrivée
                        if(grille[prochaine_ligne][prochaine_colonne] == '1'){
                            cout<<"cette point du grille est un mur svp choisir une autre direction"<<endl;
                        }
                        if (prochaine_ligne == arrive_X && prochaine_colonne == arrive_Y) {
                            chemin+=depart_Y;
                                cout << "Felicitations! Vous avez atteint l'objectif!" << endl;
                                score = count_score_func(chemin,root);
                                cout<<"Votre score est: "<<score<<endl;
                                cout<<"Chemin: "<<" "<<chemin<<endl;
                                for(auto k : shortest_path_reconstructed){
                                    cout<<"("<<k.first<<" "<<k.second<<") "; 
                                }
                                cout<<endl;
                                
                                break;
                            }
                        cout<<"vous voulez un hint concernant la validité de votre chemin ? 'Y'"<<endl;                  
                        char hint_current; 
                        cin>>hint_current;
                        if(toupper(hint_current)=='Y'){
                                if(trie.contains_prefix(current_path)){
                                         cout<<" je pense que tu peux continuez"<<endl;                  
                                }
                                else {
                                         cout<<" c'est le temps de faire une marche arriére "<<endl;  
                                }
                        }
                        position_X = prochaine_ligne ; 
                        position_Y = prochaine_colonne ; 
                        current_path.push_back({position_X,position_Y});
                        
                 }
                else {
                     cout << "tu as sorti des  bords de la grille" << endl;
                     
                }

            }
            else{
                cout << "Touche non reconnue. Veuillez entrer un numéro correspondant à la direction de déplacement :" << endl
                    << "1: Gauche, 2: Droite, 3: Haut, 4: Bas, " << endl
                    << "5: Bas-Droite, 6: Bas-Gauche, 7: Haut-Gauche, 8: Haut-Droite" << endl;
                            
                //sleep(1000); // Pause pour afficher le message
               // break;
            }
    }

}
int main() {
    FAST;
//  #ifndef ONLINE_JUDGE
//    // freopen("input.txt", "r", stdin);
//    // freopen("output.txt", "w", stdout);
//  #endif
    int t = 1;
    //cin >> t;
   
    while (t--) solve();
    return  0;
}
