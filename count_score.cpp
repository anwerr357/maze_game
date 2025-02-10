#include "count_score.hpp" // Include the header file



// TrieNode constructor
TrieNode::TrieNode() {
    wordEnd = false;
    for (int i = 0; i < 26; i++) {
        child[i] = nullptr;
    }
}

// Method to insert a key into the Trie
void insertKey(TrieNode* root, const string& key) {
    TrieNode* curr = root;
    for (char c : key) {
        if (curr->child[c - 'a'] == nullptr) {
            TrieNode* newNode = new TrieNode();
            curr->child[c - 'a'] = newNode;
        }
        curr = curr->child[c - 'a'];
    }
    curr->wordEnd = true;
}

// Method to search a key in the Trie
bool searchKey(TrieNode* root, const string& key) {
    TrieNode* curr = root;
    for (char c : key) {
        if (curr->child[c - 'a'] == nullptr)
            return false;
        curr = curr->child[c - 'a'];
    }
    return curr->wordEnd;
}
