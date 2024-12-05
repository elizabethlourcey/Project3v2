#include "Trie.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>


Node::Node() {
    //node constructor
    for(int i = 0; i < 26; i++){
        letters[i] = nullptr;
    }
    endOfWord = false;
}

void Node::setLetter(char newLetter) {
    //set node char
    letter = tolower(newLetter);
}

void Node::setEndWord(bool end) {
    //set if node is end of a word
    endOfWord = end;
    //cout << letter << endl;
}

void Node::printLetter() {
    //print node letter
    cout << letter << endl;

}

TrieTree::TrieTree() {
    //tree constructor
    root = new Node();
}

void TrieTree::insertWord(string word) {
    //insert word in trie
    Node* curr = root;
    int index;
    for (char c : word) {
        //iterate through word
        index = c - 'a';
        if (index < 0 || index >= 26) {return;} //out of index
        if (curr->letters[index] == nullptr) {
            //if node doesn't exist yet
            curr->letters[index] = new Node();
            curr->letters[index]->setLetter(c);
        }
        //next node
        curr = curr->letters[index];
    }
    //set end of word
    curr->setEndWord(true);
}


Node *TrieTree::getRoot() {
    //root getter function
    return root;
}

bool TrieTree::searchWord(string word) {
    //search for word in trie
    Node* curr = root;
    int index;
    for (int i = 0; i < word.length(); i++) {
        //iterate down tree using letter as index
        char letter = tolower(word[i]);
        index = letter - 'a';
        if (index < 0 || index >= 26 || curr->letters[index] == nullptr) {
            return false;
        }
        curr = curr->letters[index];
        if(curr == nullptr){return false;}
    }
    //return end of word
    return curr->endOfWord;
}


void TrieTree::buildTrie(std::string bank) {
    //build trie with all words in file (all english words)
    ifstream file;
    file.open(bank);

    if (!file.is_open()) {
        //check file is open
        cerr << "Error: Could not open '" << bank << "'!" << endl;
    }

    string word;
    while (getline(file, word)){
        //insert each word
        if (!word.empty()) {
            insertWord(word);
        }
    }
    //close file
    file.close();
}

// destructor
TrieTree::~TrieTree() {
    deleteNodes(root);
}

void TrieTree::deleteNodes(Node* curr) {
    if (!curr) return;
    for (int i = 0; i < 26; i++) {
        deleteNodes(curr->letters[i]);
    }
    delete curr;
}
