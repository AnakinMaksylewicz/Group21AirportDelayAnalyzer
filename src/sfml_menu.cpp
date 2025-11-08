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

    //center the labels within respective button
    sf::FloatRect bounds = label.getGlobalBounds();
    label.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    label.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
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

//screen implementations
Screen::Screen(const sf::Font& f, const std::string& title, sf::Color background) : font(f), backgroundColor(background) {

    titleText.setFont(font);
    titleText.setString(title);
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color::White);

    //center the title text
    sf::FloatRect bounds = titleText.getGlobalBounds();
    titleText.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    titleText.setPosition(400,100);
}

bool Screen::init() {return true;}

int Screen::run(sf::RenderWindow& window) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {return -1;}
            //handling button return logic
            for (int i = 0; i < buttons.size(); ++i) {
                if (buttons[i].isClicked(window, event)) {
                    return i;
                }
            }
        }
        // hover effect
        for (auto& button : buttons) {
            button.update(window);
        }
        draw(window);
    }
    return -1;
}

void Screen::draw(sf::RenderWindow& window) {
    window.clear(backgroundColor);
    window.draw(titleText);
    for (auto& button : buttons) {
        button.draw(window);
    }
    window.display();
}

//initial year month menu
bool Menu::init() {
    //create buttons
    buttons.emplace_back("Option 1", font,  sf::Vector2f(200,60),sf::Vector2f(300,250), 30);
    buttons.emplace_back("Option 2", font,  sf::Vector2f(200,60),sf::Vector2f(300,340), 30);
    buttons.emplace_back("Exit", font,  sf::Vector2f(200,60),sf::Vector2f(300,430), 30);
    return true;
}

//month/year selection
TimeSelection::TimeSelection(const sf::Font& f, const vector<string> &options, const string &title) : Screen(f, title), options(options) {}

bool TimeSelection::init() {

    //respective button sizes in each display type
    //display each month
    if (options.size() == 12) { //months display
        for (int i = 0; i < options.size(); ++i) {
            float startingY = 150;
            float startingX = 175;
            float xSpace = 250;
            float ySpace = 65;
            //half of the months in the year
            int half = 6;
            //if col is 0, 1st column, if 1, 2nd column
            int col = i/half;
            int row = i%half;

            buttons.emplace_back(options[i],font, sf::Vector2f(200, 50),sf::Vector2f(startingX + col * xSpace,
                startingY + row * ySpace), 26);
        }
    }
    else { //years display, has to be altered because there are more buttons
        for (int i = 0; i < options.size(); ++i) {
            float startingY = 150;
            float startingX = 175;
            float xSpace = 250;
            float ySpace = 40;
            //half of the years in the available years
            int half = 11;
            //if col is 0, 1st column, if 1, 2nd column
            int col = i/half;
            int row = i%half;

            buttons.emplace_back(options[i],font, sf::Vector2f(200, 35),sf::Vector2f(startingX + col * xSpace,
                startingY + row * ySpace), 30);
        }
    }
    return true;
}

string TimeSelection::Selection(sf::RenderWindow& window) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            //account for exit
            if (event.type == sf::Event::Closed) {return "";}
            //return label of clicked button as a string
            for (int i = 0; i < buttons.size(); ++i) {
                if (buttons[i].isClicked(window, event)) {
                    return buttons[i].getLabel();
                }
            }
        }
        // hover effect
        for (auto& button : buttons) {
            button.update(window);
        }
        draw(window);
    }
    return "";
}
