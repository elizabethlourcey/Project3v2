#include <iostream>
#include <algorithm>
#include "Cells.h"
#include "Trie.h"
#include "HashTable.h"

#include <SFML/Graphics.hpp>
using namespace std;

SearchBoard welcomeWindow() {
    int width = 1200;
    int height = 800;
    bool searchMode = false;
    bool choiceMode = false;
    bool trieMode = false; bool hashMode = false;



    // font for display
    sf::Font font;
    if (!font.loadFromFile("../font.ttf")) {
        cerr << "Error: Could not load font" << endl;
    }

    // initializing SFML textures and graphics
    sf::Texture titleTexture;
    titleTexture.loadFromFile("../images/title.png");
    sf::Sprite title;
    title.setTexture(titleTexture);
    title.setOrigin(title.getGlobalBounds().width / 2.f, title.getGlobalBounds().height / 2.f);
    title.setPosition(width / 2, height / 2 - 100);

    sf::Texture startTexture;
    startTexture.loadFromFile("../images/startButton.png");
    sf::Sprite start;
    start.setTexture(startTexture);
    start.setOrigin(start.getGlobalBounds().width / 2.f, start.getGlobalBounds().height / 2.f);
    start.setPosition(width / 2, height / 2 + 100);

    sf::Texture changeTexture;
    changeTexture.loadFromFile("../images/changeButton.png");
    sf::Sprite change;
    change.setTexture(changeTexture);
    change.setOrigin(change.getGlobalBounds().width / 2.f, change.getGlobalBounds().height / 2.f);
    change.setPosition(width / 2, height / 2 + 100);

    sf::Texture hashTexture;
    hashTexture.loadFromFile("../images/hashButton.png");
    sf::Sprite hash;
    hash.setTexture(hashTexture);
    hash.setOrigin(hash.getGlobalBounds().width / 2.f, hash.getGlobalBounds().height / 2.f);
    hash.setPosition(width/2 - 100, height/2 + 100);

    sf::Texture trieTexture;
    trieTexture.loadFromFile("../images/trieButton.png");
    sf::Sprite trie;
    trie.setTexture(trieTexture);
    trie.setOrigin(trie.getGlobalBounds().width / 2.f, trie.getGlobalBounds().height / 2.f);
    trie.setPosition(width/2 + 100, height/2 + 100);

    sf::Texture choiceTexture;
    choiceTexture.loadFromFile("../images/choice.png");
    sf::Sprite choice;
    choice.setTexture(choiceTexture);
    choice.setOrigin(choice.getGlobalBounds().width / 2.f, choice.getGlobalBounds().height / 2.f);
    choice.setPosition(width/2, height/2 - 100);

    vector<string> themes;
    themes.push_back("Birthday");
    themes.push_back("Summer");
    themes.push_back("SpongeBob");
    themes.push_back("Thanksgiving");
    themes.push_back("Olympics");

    vector<string> filepaths;
    filepaths.push_back("../wordSearches/birthday_wordsearch.txt");
    filepaths.push_back("../wordSearches/summer_wordsearch.txt");
    filepaths.push_back("../wordSearches/spongebob_search_19x19");
    filepaths.push_back("../wordSearches/thanksgiving_wordsearch.txt");
    filepaths.push_back("../wordSearches/olympics_wordsearch.txt");

    int themeidx = 0;
    string choiceFilePath = filepaths[themeidx];

    sf::Text searchChoice;
    searchChoice.setFont(font);
    searchChoice.setString("Your current word search theme is:");
    searchChoice.setCharacterSize(30);
    searchChoice.setFillColor(sf::Color::Blue);
    searchChoice.setStyle(sf::Text::Bold | sf::Text::Underlined);
    searchChoice = setText(searchChoice, width / 2, height / 2 - 200);

    sf::Text themeChoice;
    themeChoice.setFont(font);
    themeChoice.setString(themes[themeidx]);
    themeChoice.setCharacterSize(30);
    themeChoice.setFillColor(sf::Color::Blue);
    themeChoice.setStyle(sf::Text::Italic);
    themeChoice = setText(themeChoice, width / 2, height / 2 - 100);

    sf::RenderWindow window(sf::VideoMode(width, height), "Word Search Solvinator");
    sf::Event event;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mouse = sf::Mouse::getPosition(window);
                if (!searchMode && !choiceMode && start.getGlobalBounds().contains(window.mapPixelToCoords(mouse))) {
                    searchMode = true;
                    start.setPosition(width / 2 - 100, height / 2);
                    change.setPosition(width / 2 + 100, height / 2);

                }
                if (searchMode && !choiceMode && change.getGlobalBounds().contains(window.mapPixelToCoords(mouse))) {
                    themeidx += 1;
                    if (themeidx == themes.size())
                        themeidx = 0;
                    themeChoice.setString(themes[themeidx]);
                    choiceFilePath = filepaths[themeidx];
                }

                if (searchMode && !choiceMode && start.getGlobalBounds().contains(window.mapPixelToCoords(mouse))) {
                    choiceMode = true;
                    searchMode = false;
                }

                if (choiceMode && !searchMode && hash.getGlobalBounds().contains(window.mapPixelToCoords(mouse))) {
                    hashMode = true;
                    cout << "Gameplay using hash data structure" << endl;
                }
                if (choiceMode && !searchMode && trie.getGlobalBounds().contains(window.mapPixelToCoords(mouse))) {
                    trieMode = true;
                    cout << "Gameplay using trie data structure" << endl;
                }

                if (hashMode || trieMode) {
                    SearchBoard search(choiceFilePath);
                    search.filePath = choiceFilePath;
                    if (trieMode)
                        search.mode = "trie";
                    if (hashMode)
                        search.mode = "hash";
                    window.close();
                    return search;
                }

            }
        }

        window.clear(sf::Color::White);
        if (!searchMode && !choiceMode) {
            window.draw(title);
            window.draw(start);
        } else if (searchMode && !choiceMode) {
            window.draw(start);
            window.draw(change);
            window.draw(searchChoice);
            window.draw(themeChoice);
        }
        else if (!searchMode && choiceMode) {
            window.draw(choice);
            window.draw(hash);
            window.draw(trie);
        }

        window.display();
    }
}



void gameWindow(SearchBoard& search) {
    int width = 1200;
    int height = 800;

    sf::Texture checkTexture;
    checkTexture.loadFromFile("../images/checkButton.png");
    sf::Sprite check;
    check.setTexture(checkTexture);
    check.setOrigin(check.getGlobalBounds().width / 2.f, check.getGlobalBounds().height / 2.f);
    check.setPosition(1000, 200);

    sf::Texture autoSolveTexture;
    autoSolveTexture.loadFromFile("../images/autoSolve.png");
    sf::Sprite autoSolve;
    autoSolve.setTexture(autoSolveTexture);
    autoSolve.setOrigin(autoSolve.getGlobalBounds().width / 2.f, autoSolve.getGlobalBounds().height / 2.f);
    autoSolve.setPosition(1000, 300);

    TrieTree trie;
    HashTable hash;
    vector<string> wordBank;

    if (search.mode == "trie") {
        trie.buildTrie("../englishWords.txt");
        cout << "Trie successfully created" << endl;

    }

    else if (search.mode == "hash") {
        hash.insertAll();
        cout << "Hash successfully created" << endl;
    }

    // game control
    string runningString = "";
    bool right = false; bool down = false;
    bool solvinator = false;
    int prevRow = 0; int prevCol = 0;
    Cell* currCell;



    sf::RenderWindow window(sf::VideoMode(width, height), "Word Search Solvinator");
    sf::Event event;

    while(window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mouse = sf::Mouse::getPosition(window);
                if (!solvinator && autoSolve.getGlobalBounds().contains(window.mapPixelToCoords(mouse))) {
                    solvinator = true;
                    currCell = search.board[0][0];
                    // check all horizontal rows
                    cout << "Horizontal Search" << endl;
                    string word = "";
                    for (int i = 0; i < search.rows; i++) {
                        for (int j = 0; j < search.cols; j++) {
                            word = "";
                            for (int k = j; k < search.cols; k++) {
                                word += tolower(search.board[i][k]->value);
                                currCell = search.board[i][k];
                                if ((trie.searchWord(word) && search.mode == "trie") ||
                                    ((hash.searchWord(word)) && search.mode == "hash")) {
                                    currCell->found = true;
                                    prevCol = k;
                                    currCell->character.setFillColor(sf::Color::Green);

                                    for (int m = 1; m < word.length(); m++) {
                                        search.board[i][prevCol - 1]->found = true;
                                        search.board[i][prevCol - 1]->character.setFillColor(sf::Color::Green);
                                        prevCol -= 1;
                                    }
                                }
                            }
                        }
                    }
                    // check all vertical columns
                    for (int i = 0; i < search.cols; i++) {
                        for (int j = 0; j < search.rows; j++) {
                            word = "";
                            for (int k = j; k < search.rows; k++) {
                                word += tolower(search.board[k][i]->value);
                                currCell = search.board[k][i];
                                if ((trie.searchWord(word) && search.mode == "trie") ||
                                    ((hash.searchWord(word)) && search.mode == "hash")) {
                                    //currCell->found = true;
                                    prevRow = k;
                                    currCell->character.setFillColor(sf::Color::Green);

                                    for (int m = 1; m < word.length(); m++) {
                                        //search.board[prevRow - 1][i]->found = true;
                                        search.board[prevRow - 1][i]->character.setFillColor(sf::Color::Green);
                                        prevRow -= 1;
                                    }
                                }
                            }

                        }
                    }

                    // clear any cells that are magenta
                    for (int i = 0; i < search.rows; i++) {
                        for (int j = 0; j < search.cols; j++) {
                            if (!search.board[i][j]->found)
                                search.board[i][j]->character.setFillColor(sf::Color::Blue);
                        }
                    }
                    cout << "Vertical Search" << endl;

                }

                if (!solvinator && check.getGlobalBounds().contains(window.mapPixelToCoords(mouse))) {

                    currCell = search.board[prevRow][prevCol];

                    if ((trie.searchWord(runningString) && search.mode == "trie") ||
                        ((hash.searchWord(runningString)) && search.mode == "hash")) {
                        if (search.mode == "trie")
                            cout << "Word found in trie" << endl;
                        else if (search.mode == "hash")
                            cout << "Word found in hash table" << endl;
                        currCell->found = true;

                        currCell->character.setFillColor(sf::Color::Green);

                        for (int i = 1; i < runningString.length(); i++) {
                            if (down) {
                                search.board[prevRow - 1][prevCol]->found = true;
                                search.board[prevRow - 1][prevCol]->character.setFillColor(sf::Color::Green);
                                prevRow -= 1;
                            } else if (right) {
                                search.board[prevRow][prevCol - 1]->found = true;
                                search.board[prevRow][prevCol - 1]->character.setFillColor(sf::Color::Green);
                                prevCol -= 1;
                            }
                        }
                        down = false;
                        right = false;
                    } else {
                        if (search.mode == "hash") {
                            cout << "Hash" << endl;
                            if (!hash.searchWord(runningString));
                            cout << "Word not found" << endl;
                        }

                        if (search.mode == "trie") {
                            cout << "Trie" << endl;
                            if (!trie.searchWord(runningString))
                                cout << "Word not found" << endl;
                        }

                        currCell->clicked = false;
                        currCell->character.setFillColor(sf::Color::Blue);

                        for (int i = 1; i < runningString.length(); i++) {
                            if (down) {
                                search.board[prevRow - 1][prevCol]->clicked = false;
                                search.board[prevRow - 1][prevCol]->character.setFillColor(sf::Color::Blue);
                                prevRow -= 1;
                            } else if (right) {
                                search.board[prevRow][prevCol - 1]->clicked = false;
                                search.board[prevRow][prevCol - 1]->character.setFillColor(sf::Color::Blue);
                                prevCol -= 1;
                            }
                        }
                    }
                    down = false;
                    right = false;
                    runningString = "";
                }


                if (!solvinator) {
                    for (int i = 0; i < search.rows; i++) {
                        for (int j = 0; j < search.cols; j++) {
                            currCell = search.board[i][j];
                            if (mouse.x >= currCell->colPos && mouse.x < currCell->colEnd &&
                                mouse.y >= currCell->rowPos && mouse.y < currCell->rowEnd) {
                                cout << "click" << endl;
                                if (currCell->clicked && !currCell->found) {
                                    if (i == prevRow && j == prevCol) {
                                        currCell->clicked = false;
                                        currCell->character.setFillColor(sf::Color::Blue);
                                        runningString.erase(runningString.length() - 1);
                                        cout << "Word: " << runningString << endl;
                                        if (down) {
                                            prevRow = i - 1;
                                            prevCol = j;
                                        } else if (right) {
                                            prevRow = i;
                                            prevCol = j - 1;
                                        }
                                        if (runningString.length() == 1 || runningString.length() == 0) {
                                            down = false;
                                            right = false;
                                            if (runningString.length() == 0) {
                                                prevRow = -1;
                                                prevCol = -1;
                                            }

                                        }

                                    }

                                } else if (!currCell->clicked && !currCell->found) {
                                    if (((down && i == prevRow + 1 && j == prevCol) ||
                                         (right && j == prevCol + 1 && i == prevRow)) || runningString.length() == 0
                                        || runningString.length() == 1) {
                                        if (runningString.length() == 1) {
                                            if (i == prevRow + 1 && j == prevCol)
                                                down = true;
                                            else if (j == prevCol + 1 && i == prevRow)
                                                right = true;
                                            else
                                                continue;
                                        }
                                        currCell->clicked = true;
                                        currCell->character.setFillColor(sf::Color::Magenta);
                                        runningString += currCell->value;
                                        cout << "Word: " << runningString << endl;
                                        prevRow = i;
                                        prevCol = j;
                                    } else {
                                        currCell->clicked = false;
                                        continue;
                                    }
                                } else if (currCell->clicked && currCell->found)
                                    continue;

                                cout << "Down : " << down << endl;
                                cout << "Right: " << right << endl;


                            }
                        }
                    }


                }
            }
        }
        window.clear(sf::Color::White);
        window.draw(check);
        window.draw(autoSolve);
        for (int i = 0; i < search.rows; i++) {
            for (int j = 0; j < search.cols; j++) {
                window.draw(search.board[i][j]->outline);
                window.draw(search.board[i][j]->character);
            }
        }


        window.display();
    }
}

int main() {
    SearchBoard search = welcomeWindow();
    gameWindow(search);

    return 0;
}
