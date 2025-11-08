//
// Created by denni on 11/7/2025.
//

#ifndef SFML_MENU_H
#define SFML_MENU_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "csv_parser.h"
using namespace std;

class Button {
    sf::RectangleShape button;
    sf::Text label;
    sf::Color regularColor;
    sf::Color hoverColor;
public:
    //logic for different colors dependent on whether buttons are hovered
    Button(const std::string& text, const sf::Font& font,sf::Vector2f size, sf::Vector2f position, int fontSize,
    sf::Color regularColor = sf::Color(0, 35, 165), sf::Color hoverColor = sf::Color(250, 70, 22));
    void draw(sf::RenderWindow& window);
    bool isHovered(sf::RenderWindow& window);
    bool isClicked(sf::RenderWindow& window, const sf::Event& event);
    void update(sf::RenderWindow& window);
};

class Menu {
    sf::Font font;
    vector<Button> buttons;
    sf::Text titleText;
    sf::Color backgroundColor;
public:
    Menu();
    void draw(sf::RenderWindow &window);
    //initialize resources
    bool init();
    //returns ints to register selected button
    int run(sf::RenderWindow &window);

};
#endif //SFML_MENU_H
