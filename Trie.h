#include <iostream>
#include <string>

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

public:
    TrieTree();
    void insertWord(string word);
    bool searchWord(string word);
    Node* getRoot();
    void buildDictionary(string bank);
    void buildWordBank(string bank);
    void traversal(Node* curr);
    void findWords(string file);
};
