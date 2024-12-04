#include <iostream>
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

    TrieTree trie;
    HashTable hash;

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
    bool click = false;
    int prevRow = 0; int prevCol = 0;
    vector<string> wordBank;


    sf::RenderWindow window(sf::VideoMode(width, height), "Word Search Solvinator");
    sf::Event event;

    while(window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mouse = sf::Mouse::getPosition(window);

                    if (check.getGlobalBounds().contains(window.mapPixelToCoords(mouse))) {
                        if (search.mode == "trie") {
                            cout << "Ok" << endl;
                        }
                    }

                    for (int i = 0; i < search.rows; i++) {
                        for (int j = 0; j < search.cols; j++) {
                            Cell* currCell = search.board[i][j];
                            if (mouse.x >= currCell->colPos && mouse.x < currCell->colEnd &&
                                mouse.y >= currCell->rowPos && mouse.y < currCell->rowEnd) {
                                if(currCell->clicked) {
                                    currCell->clicked = false;
                                    currCell->character.setFillColor(sf::Color::Blue);
                                    runningString.erase();
                                    cout << "Word: " << runningString << endl;
                                }
                                else if (!currCell->clicked) {
                                    currCell->clicked = true;
                                    currCell->character.setFillColor(sf::Color::Magenta);
                                    runningString += currCell->value;
                                    cout << "Word: " << runningString << endl;
                                }

                            }
                        }
                    }


            }

            window.clear(sf::Color::White);


                window.draw(check);
                for (int i = 0; i < search.rows; i++) {
                    for (int j = 0; j < search.cols; j++) {
                        window.draw(search.board[i][j]->outline);
                        window.draw(search.board[i][j]->character);
                    }
                }


            window.display();
        }
    }
}

int main() {
    SearchBoard search = welcomeWindow();
    gameWindow(search);

    return 0;
}
