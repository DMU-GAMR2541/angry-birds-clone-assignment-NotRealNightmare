#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class UI {
private:
    sf::Texture te_Texture;
    sf::Sprite sp_Sprite;
    sf::Text gameOverText;
    sf::Font font;
    sf::Text pigCountText;
    sf::Text pressEnterText;

public:
    UI() = default;

    UI(std::string str_sprite, float xPos, float yPos) {
        if (!te_Texture.loadFromFile(str_sprite)) {
            std::cout << "Error loading UI texture" << std::endl;
        }
        sp_Sprite = sf::Sprite(te_Texture);
        sp_Sprite.setPosition(xPos, yPos);

        float scaleX = 800.0f / te_Texture.getSize().x;
        float scaleY = 600.0f / te_Texture.getSize().y;
        sp_Sprite.setScale(scaleX, scaleY);

        if (!font.loadFromFile("../assets/fonts/angry-birds.ttf")) {
            std::cout << "Error loading font" << std::endl;
        }

        pigCountText.setFont(font);
        pigCountText.setCharacterSize(30);
        pigCountText.setFillColor(sf::Color::White);
        pigCountText.setOutlineColor(sf::Color::Black);
        pigCountText.setOutlineThickness(2.0f);
        pigCountText.setPosition(10.0f, 10.0f);

        gameOverText.setFont(font);
        gameOverText.setString("You Win!");
        gameOverText.setCharacterSize(60);
        gameOverText.setFillColor(sf::Color::Yellow);
        gameOverText.setOutlineColor(sf::Color::Black);
        gameOverText.setOutlineThickness(3.0f);
        gameOverText.setPosition(300.0f, 300.0f);

        pressEnterText.setFont(font);
        pressEnterText.setString("Press Enter to Start");
        pressEnterText.setCharacterSize(40);
        pressEnterText.setFillColor(sf::Color::White);
        pressEnterText.setOutlineColor(sf::Color::Black);
        pressEnterText.setOutlineThickness(2.0f);
        pressEnterText.setPosition(250.0f, 500.0f);
    }

    ~UI() = default;

    void updatePigCount(int count) {
        pigCountText.setString("Pigs: " + std::to_string(count));
    }

    void render(sf::RenderWindow& window) {
        window.draw(sp_Sprite);
        window.draw(pressEnterText);
    }

    void renderHUD(sf::RenderWindow& window) {
        window.draw(pigCountText);
    }

    void renderWin(sf::RenderWindow& window) {
        window.draw(gameOverText);
    }

};