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
    sf::RectangleShape outline;
    sf::Text character;
    int rowPos = 0;
    int colPos = 0;
    int rowEnd = 0;
    int colEnd = 0;

    bool clicked = false;

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
        outline.setFillColor(sf::Color::White);
        outline.setOutlineColor(sf::Color::Red);
        outline.setOutlineThickness(2);

    }
};


struct SearchBoard {
    int rows = 1;
    int cols = 1;
    int width = 1200;
    int height = 800;
    float gridWidth = 0;
    float gridHeight = 0;
    string filePath = " ";
    string mode = " ";
    vector<vector<Cell*>> board;

    void readFile(vector<vector<Cell*>>& board, string filename);
    SearchBoard() {

    }
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

sf::RectangleShape setRect(sf::RectangleShape &rect, float x, float y) {
    sf::FloatRect textRect = rect.getLocalBounds();
    rect.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    rect.setPosition(sf::Vector2f(x, y));
    return rect;
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
    int xOrigin = 0; int yOrigin = 0;
    while(getline(file, line)) {
            vector<Cell*> row;
            for (int j = 0; j < this->cols; j++) {
                Cell *temp = new Cell(line[j]);
                temp->character = setText(temp->character, j * gridWidth + gridWidth, i * gridHeight + gridHeight);
                temp->outline.setSize(sf::Vector2f(gridWidth, gridHeight));
                temp->outline.setOrigin(gridWidth/2, gridHeight/2);
                xOrigin = j * gridWidth + gridWidth; yOrigin = i * gridHeight + gridHeight;
                temp->outline.setPosition(xOrigin, yOrigin);
                temp->rowPos = yOrigin - gridHeight/2; temp->rowEnd = yOrigin + gridHeight/2;
                temp->colPos = xOrigin - gridWidth/2; temp->colEnd = xOrigin + gridWidth/2;
                row.push_back(temp);
            }
            board.push_back(row);
            i += 1;
        }


}
