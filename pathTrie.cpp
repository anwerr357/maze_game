#include "pathTrie.hpp"

// PairHash implementation
size_t PairHash::operator()(const pair<int, int>& p) const {
    hash<int> hasher;
    return hasher(p.first) ^ (hasher(p.second) << 1);
}

// PathTrieNode constructor
PathTrieNode::PathTrieNode(pair<int, int> c) : cell(c), is_end(false) {}

// PathTrie constructor
PathTrie::PathTrie(pair<int, int> start_cell) {
    root = new PathTrieNode(start_cell);
}

// Insert a path into the trie
void PathTrie::insert(const vector<pair<int, int>>& path) {
    if (path.empty() || path[0] != root->cell) {
        return; // Invalid path (must start with root's cell)
    }

    PathTrieNode* current = root;
    for (size_t i = 1; i < path.size(); ++i) {
        auto next_cell = path[i];
        if (current->children.find(next_cell) == current->children.end()) {
            current->children[next_cell] = new PathTrieNode(next_cell);
        }
        current = current->children[next_cell];
    }
    current->is_end = true; // Mark end of path
}

// Check if a path exists in the trie
bool PathTrie::contains(const vector<pair<int, int>>& path) {
    if (path.empty() || path[0] != root->cell) {
        return false; // Invalid path
    }

    PathTrieNode* current = root;
    for (size_t i = 1; i < path.size(); ++i) {
        auto next_cell = path[i];
        if (current->children.find(next_cell) == current->children.end()) {
            return false;
        }
        current = current->children[next_cell];
    }
    return current->is_end; // True only if path ends here
}

// Check if a prefix exists in the trie
bool PathTrie::contains_prefix(const vector<pair<int, int>>& path) {
    if (path.empty() || path[0] != root->cell) {
        return false; // Invalid prefix
    }

    PathTrieNode* current = root;
    for (size_t i = 1; i < path.size(); ++i) {
        auto next_cell = path[i];
        if (current->children.find(next_cell) == current->children.end()) {
            return false;
        }
        current = current->children[next_cell];
    }
    return true; // True only if prefix is really a prefix of valid path
}