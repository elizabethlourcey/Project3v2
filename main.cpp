#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

int main() {
    int width = 1200;
    int height = 800;
    bool game = false;
    bool choiceMode = false;
    bool hashMode = false;
    bool trieMode = false;
    //textures
    sf::Texture titleTexture;
    titleTexture.loadFromFile("../images/title.png");
    sf::Sprite title;
    title.setTexture(titleTexture);
    title.setOrigin(title.getGlobalBounds().width / 2.f, title.getGlobalBounds().height / 2.f);
    title.setPosition(width/2, height/2 - 100);

    sf::Texture choiceTexture;
    choiceTexture.loadFromFile("../images/choice.png");
    sf::Sprite choice;
    choice.setTexture(choiceTexture);
    choice.setOrigin(choice.getGlobalBounds().width / 2.f, choice.getGlobalBounds().height / 2.f);
    choice.setPosition(width/2, height/2 - 100);

    sf::Texture startTexture;
    startTexture.loadFromFile("../images/startButton.png");
    sf::Sprite start;
    start.setTexture(startTexture);
    start.setOrigin(start.getGlobalBounds().width / 2.f, start.getGlobalBounds().height / 2.f);
    start.setPosition(width/2, height/2 + 100);

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

    // welcome window
    sf::RenderWindow window(sf::VideoMode(width, height), "Word Search Solvinator");
    sf::Event event;
    while(window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mouse = sf::Mouse::getPosition(window);
                if (start.getGlobalBounds().contains(window.mapPixelToCoords(mouse))) {
                    choiceMode = true;
                }
                if (hash.getGlobalBounds().contains(window.mapPixelToCoords(mouse))) {
                    choiceMode = false;
                    game = true;
                    hashMode = true;
                    cout << "Gameplay using hash data structure" << endl;
                }
                if (trie.getGlobalBounds().contains(window.mapPixelToCoords(mouse))) {
                    choiceMode = false;
                    trieMode = true;
                    game = true;
                    cout << "Gameplay using trie data structure" << endl;
                }


            }

            window.clear(sf::Color::White);
            if (!game && !choiceMode) {
                window.draw(title);
                window.draw(start);
            }
            else if (!game && choiceMode) {
                window.draw(choice);
                window.draw(hash);
                window.draw(trie);
            }
            else if(game && hashMode) {

            }

            else if(game && trieMode) {

            }

            window.display();
        }
    }

    return 0;
}
