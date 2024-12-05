#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node{
    //node struct
    Node* letters[26];
    bool endOfWord;
    char letter;
    Node();
    void setLetter(char newLetter);
    void setEndWord(bool end);
    void printLetter();
};

class TrieTree{
    //trie class
private:
    Node* root;
    void deleteNodes(Node* curr);

public:
    TrieTree();
    void insertWord(string word);
    bool searchWord(string word);
    Node* getRoot();
    void buildTrie(string bank);
    ~TrieTree();


};
