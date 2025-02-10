// count_score.hpp
#ifndef COUNT_SCORE_HPP // Include guard
#define COUNT_SCORE_HPP

#include <string> // For std::string

using namespace std; // Using namespace std directly

// TrieNode structure declaration
struct TrieNode {
    TrieNode* child[26];
    bool wordEnd;
    TrieNode();
};

// Function declarations
void insertKey(TrieNode* root, const string& key);
bool searchKey(TrieNode* root, const string& key);

#endif // COUNT_SCORE_HPP