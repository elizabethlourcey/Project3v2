#include "Trie.h"
#include <string>
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

}

void Node::printLetter() {
    //print node letter
    cout << letter << endl;

}

TrieTree::TrieTree() {
    Node* rootNode = new Node;
    root = rootNode;
}

void TrieTree::insertWord(string word) {
    Node* curr = root;
    char letter;
    int index;
    while(word.length() > 0){
        letter = word[0];
        letter = tolower(letter);
        //cout << letter << endl;
        index = letter;
        index -= 97;
        //cout << index << endl;
        if(curr->letters[index] == nullptr){
            curr->letters[index] = new Node();
            curr->letters[index]->setLetter(letter);

        }
        curr = curr->letters[index];
        word = word.substr(1, word.length()-1);
    }
    curr->setEndWord(true);
}

Node *TrieTree::getRoot() {
    return root;
}

bool TrieTree::searchWord(string word) {
    Node* curr = root;
    char letter;
    int index;
    while (word.length() > 0) {
        letter = word[0];
        letter = tolower(letter);
        index = letter;
        index -= 97;
        if (curr->letters[index] == nullptr) {
            return false;
        }
        curr = curr->letters[index];
        word = word.substr(1, word.length()-1);
    }
    return true;
}

void TrieTree::buildDictionary(string bank) {
    ifstream file;
    file.open("../words_alpha.txt");


    if (!file.is_open()) {
        cerr << "Error: Could not open 'words_alpha.txt'!" << endl;
    }

    string word;
    while (getline(file, word)){
        insertWord(word);
    }

    file.close();
    cout << "done" << endl;
}

void TrieTree::buildWordBank(std::string bank) {
    ifstream file;
    file.open(bank);


    if (!file.is_open()) {
        cerr << "Error: Could not open '" << bank << "'!" << endl;
    }

    string word;
    while (getline(file, word)){
        insertWord(word);
    }
    file.close();
}

void TrieTree::traversal(Node* curr) {
    if (curr == nullptr) {return;}
    curr->printLetter();
    if(curr->endOfWord) {cout << endl;}
    for(int i = 0; i < 26; i++){
        traversal(curr->letters[i]);
    }
}

void TrieTree::findWords(std::string file) {
    string dimensions;

    ifstream wordSearch;
    wordSearch.open(file);

    if (!wordSearch.is_open()) {
        cerr << "Error: Could not open '" << file << "'!" << endl;
    }

    getline(wordSearch, dimensions);
    string del = " ";
    auto position = dimensions.find(del);
    int rows = stoi(dimensions.substr(0, position));
    int cols = stoi(dimensions.substr(position + 1));

    string word;
    string blockText[rows];
    for(int i = 0; i < rows; i++){
        string wordRow;
        getline(wordSearch, wordRow);
        blockText[i] = wordRow;
    }




}