#include <SFML/Graphics.hpp>
#include <vector>
#pragma once
#include <string>
#include <fstream>

using namespace std;

struct Cell {
    char value = ' ';
    //sf::Sprite backgroundColor;
    sf::Font font;
    sf::Text character;

    Cell() {
        value = ' ';
        character.setString(' ');
        if (!font.loadFromFile("../font.ttf")){
            cerr << "Error: Could not load font" << endl;
        }

    }


    Cell(char _value) {
        if (!font.loadFromFile("../font.ttf")){
            cerr << "Error: Could not load font" << endl;
        }
        value = _value;
        character.setFont(font);
        character.setString(value);
        character.setCharacterSize(24);
        character.setFillColor(sf::Color::Blue);
        character.setStyle(sf::Text::Bold);
    }
};


struct SearchBoard {
    int rows = 1;
    int cols = 1;
    int width = 1200;
    int height = 800;
    float gridWidth = 0;
    float gridHeight = 0;
    vector<vector<Cell*>> board;
    void readFile(vector<vector<Cell*>>& board, string filename);

    SearchBoard(string filename){
      readFile(this->board, filename);
    }

};


sf::Text setText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(x, y));
    return text;
}

 void SearchBoard::readFile(vector<vector<Cell*>>& board, string filename) {
    ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open '" << filename << "'!" << endl;
    }
    string dimensions;
    string line;
    getline(file, dimensions);
    string del = " ";
    auto position = dimensions.find(del);
    this->rows = stoi(dimensions.substr(0, position));
    this->cols = stoi(dimensions.substr(position + 1));
    this->gridWidth = float((this->width - 400) / this->cols);
    this->gridHeight = float((this->height - 200) / this->rows);

    int i = 0;
    while(getline(file, line)) {
            vector<Cell*> row;
            for (int j = 0; j < this->cols; j++) {
                Cell *temp = new Cell(line[j]);
                temp->character = setText(temp->character, j * gridWidth + gridWidth, i * gridHeight + gridHeight);
                row.push_back(temp);
            }
            board.push_back(row);
            i += 1;
        }


}
