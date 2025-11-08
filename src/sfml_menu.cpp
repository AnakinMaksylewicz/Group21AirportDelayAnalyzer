//
// Created by denni on 11/8/2025.
//

#include "sfml_menu.h"
#include <iostream>

//button implementations
Button::Button(const std::string& text, const sf::Font& font,sf::Vector2f size, sf::Vector2f position, int fontSize,
    sf::Color regularColor, sf::Color hoverColor) : regularColor(regularColor), hoverColor(hoverColor) {

    button.setSize(size);
    button.setPosition(position);
    button.setFillColor(regularColor);

    label.setFont(font);
    label.setCharacterSize(fontSize);
    label.setString(text);
    label.setFillColor(sf::Color::White);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(button);
    window.draw(label);
}

//returns true if mouse is within bounds of button
bool Button::isHovered(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        return true;
    }
    return false;
}

//isHovered covers the logic for being within button bounds, true if a left click is registered in button
bool Button::isClicked(sf::RenderWindow& window, const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && isHovered(window)) {
        return true;
    }
    return false;
}

//changes color on hover
void Button::update(sf::RenderWindow& window) {
    if (isHovered(window)) {
        button.setFillColor(hoverColor);
    }
    else {
        button.setFillColor(regularColor);
    }
}

//menu implementations
Menu::Menu() : backgroundColor(sf::Color(54,186, 216)) {}
bool Menu::init() {
    if (!font.loadFromFile("assets/HATTEN.TTF")) {
        std::cerr << "Failed to load font." << std::endl;
        return false;
    }

    titleText.setFont(font);
    titleText.setString("Flight Delay Analyzer");
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(sf::Vector2f(130, 80));

    //create buttons
    buttons.emplace_back("Option 1", font,  sf::Vector2f(200,60),sf::Vector2f(300,250), 30);
    buttons.emplace_back("Option 2", font,  sf::Vector2f(200,60),sf::Vector2f(300,340), 30);
    buttons.emplace_back("Exit", font,  sf::Vector2f(200,60),sf::Vector2f(300,430), 30);

    return true;
}

int Menu::run(sf::RenderWindow& window) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            //exit is our close window
            if (event.type == sf::Event::Closed) {return 0;}
            for (int i = 0; i < buttons.size(); ++i) {
                if (buttons[i].isClicked(window, event)) {
                    //first button clicked
                    if (i == 0) {return 1;}
                    //second button clicked
                    if (i == 1) {return 2;}
                    //exit clicked
                    if (i == 2) {return 0;}
                }
            }
        }
        // hover effect
        for (auto& button : buttons) {
            button.update(window);
        }
        draw(window);
    }
    return 0;
}

void Menu::draw(sf::RenderWindow& window) {
    window.clear(backgroundColor);
    window.draw(titleText);
    for (auto& button : buttons) {
        button.draw(window);
    }
    window.display();
}
