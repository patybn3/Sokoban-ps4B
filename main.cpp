/*
    Copyright 2023 Patricia Antlitz
*/
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Sokoban.hpp"

int main(int argc, char const *argv[]) {
    /* code */
    if (argc != 2) {
        std::cout << "Args: " << argv[0] << "level text file as level1.txt" << std::endl;
        return 1;
    }

    sf::RenderWindow window;
    Sokoban sb;
    sb.setGame(argv[1]);

    window.create(sf::VideoMode(sb.width(), sb.height()), "Sokoban");

    sf::Clock gameClock;
    bool gameWon = false;

    sf::Font font;
    if (!font.loadFromFile("Robot Crush.ttf")) {
        return 1;
    }

    sf::Text finalMessage("", font, 60);
    sf::Text timerText("", font, 30);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (!gameWon) {
                    if (event.key.code == sf::Keyboard::Up) {
                        sb.movePlayer(Direction::Up);
                    } else if (event.key.code == sf::Keyboard::Down) {
                        sb.movePlayer(Direction::Down);
                    } else if (event.key.code == sf::Keyboard::Left) {
                        sb.movePlayer(Direction::Left);
                    } else if (event.key.code == sf::Keyboard::Right) {
                        sb.movePlayer(Direction::Right);
                    }
                }
                if (event.key.code == sf::Keyboard::R) {
                    sb.setGame(argv[1]);
                    gameClock.restart();
                    gameWon = false;
                }
            }
        }

        if (!gameWon) {
            float elapsedSeconds = gameClock.getElapsedTime().asSeconds();

            int minutes = static_cast<int>(elapsedSeconds) / 60;
            int seconds = static_cast<int>(elapsedSeconds) % 60;

            std::string formattedTime = (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" +
                                        (seconds < 10 ? "0" : "") + std::to_string(seconds);

            sf::FloatRect rec = timerText.getLocalBounds();
            timerText.setOrigin(rec.left + rec.width, rec.top);
            timerText.setPosition(window.getSize().x - 20, window.getSize().y - 30);
            timerText.setString("Time: " + formattedTime);

            sb.setPoints(elapsedSeconds);

            if (sb.isWon()) {
                gameWon = true;
                finalMessage.setString("Winner! Points: " + std::to_string(sb.getPoints()));
                sf::FloatRect textRec = finalMessage.getLocalBounds();
                finalMessage.setOrigin(textRec.left + textRec.width / 2.0f,
                                        textRec.top + textRec.height / 2.0f);
                finalMessage.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

                window.clear(sf::Color(177, 120, 62));
                window.draw(sb);
                window.draw(finalMessage);
                window.display();
            } else {
                    // color matches the background image color
                window.clear(sf::Color(177, 120, 62));
                window.draw(sb);
                window.draw(timerText);
                window.display();
            }
        }
    }

    return 0;
}
