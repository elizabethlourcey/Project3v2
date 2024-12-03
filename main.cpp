#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

int main() {
    int width = 1200;
    int height = 800;
    bool game = false;
    //textures
    sf::Texture titleTexture;
    titleTexture.loadFromFile("../images/title.png");
    sf::Sprite title;
    title.setTexture(titleTexture);
    title.setOrigin(title.getGlobalBounds().width / 2.f, title.getGlobalBounds().height / 2.f);
    title.setPosition(width/2, height/2 - 100);

    sf::Texture startTexture;
    startTexture.loadFromFile("../images/startButton.png");
    sf::Sprite start;
    start.setTexture(startTexture);
    start.setOrigin(start.getGlobalBounds().width / 2.f, start.getGlobalBounds().height / 2.f);
    start.setPosition(width/2, height/2 + 100);

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
                    game = true;
                }

            }

            window.clear(sf::Color::White);
            if (!game) {
                window.draw(title);
                window.draw(start);
            }
            else {
              // draw upload v. generate
            }

            window.display();
        }
    }

    return 0;
}
