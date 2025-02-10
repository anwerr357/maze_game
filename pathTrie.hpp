#ifndef PATHTRIE_H
#define PATHTRIE_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional> // For hashing

using namespace std;

// Hash function for pair<int, int>
struct PairHash {
    size_t operator()(const pair<int, int>& p) const;
};

// TrieNode class
class PathTrieNode {
public:
    pair<int, int> cell;
    bool is_end;
    unordered_map<pair<int, int>, PathTrieNode*, PairHash> children;

    PathTrieNode(pair<int, int> c);
};

// PathTrie class
class PathTrie {
public:
    PathTrieNode* root;

    PathTrie(pair<int, int> start_cell);
    void insert(const vector<pair<int, int>>& path);
    bool contains(const vector<pair<int, int>>& path);
    bool contains_prefix(const vector<pair<int, int>>& path);
};

#endif // PATHTRIE_H