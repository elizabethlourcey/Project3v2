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
















vector<string> TrieTree::findWords(std::string file) {
    //find all words in a block of text (horizontal and vertical forward spelling only)
    //open word search file
    ifstream wordSearch;
    wordSearch.open(file);

    if (!wordSearch.is_open()) {
        cerr << "Error: Could not open '" << file << "'!" << endl;
        return {};
    }

    //get search dimensions
    string dimensions;
    getline(wordSearch, dimensions);
    string del = " ";
    auto position = dimensions.find(del);
    int rows = stoi(dimensions.substr(0, position));
    int cols = stoi(dimensions.substr(position + 1));

    //get each row of word search
    vector<string> blockText(rows);
    for(int i = 0; i < rows; i++){
        getline(wordSearch, blockText[i]);
    }
    wordSearch.close();


    vector<string> found;
    for(int i = 0; i < rows; i++){
        //search the word search horizontally
         vector<string> words = searchHorizontal(blockText[i]);
         found.insert(found.end(), words.begin(), words.end());
    }
    for(int i = 0; i < cols; i++){
        //search the word search vertically
        vector<string> words = searchVertical(blockText, i);
        found.insert(found.end(), words.begin(), words.end());
    }
    return found;
}

vector<string> TrieTree::searchHorizontal(string row) {
    //search a row for words
    vector<string> foundWords;
    int rowSize = row.length();
    for(int i = 0; i < rowSize; i++){
        //iterate down the row looking for all possible words at each position
        string currWord = "";
        for(int j = i; j < rowSize; j++){
            currWord += tolower(row[j]);
            if(searchWord(currWord)){foundWords.push_back(currWord);}
        }
    }
    return foundWords;
}

vector<string> TrieTree::searchVertical(vector<string> block, int col) {
    //search a column for words
    vector<string> foundWords;
    int rows = block.size();
    for (int i = 0; i < rows; i++) {
        //iterate down the columns
        string currWord = "";
        for (int j = i; j < rows; j++) {
            if (col >= block[j].length()) {
                break;  // Out of bounds
            }
            currWord += tolower(block[j][col]);

            if (searchWord(currWord)) {
                foundWords.push_back(currWord);
            }
        }
    }
    return foundWords;
}

