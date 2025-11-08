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
    string getLabel() {return label.getString();}
};

//parent class for general screen, different screens requiring different buttons will inherit from this
class Screen {
protected:
    const sf::Font& font;
    vector<Button> buttons;
    sf::Text titleText;
    sf::Color backgroundColor;
public:
    Screen(const sf::Font& f, const string& title, sf::Color background = sf::Color(54, 186, 216));
    virtual void draw(sf::RenderWindow &window);
    //initialize resources
    virtual bool init();
    //returns ints to register selected button
    virtual int run(sf::RenderWindow &window);

};

//initial year month menu
class Menu : public Screen {
    public:
    Menu(const sf::Font& f) : Screen(f, "Flight Delay Analyzer") {}
    bool init() override;
};

//year/month selection
class TimeSelection : public Screen {
    vector<string> options;
    string selectedOption;
public:
    TimeSelection(const sf::Font& f, const vector<string>& options, const string& title);
    bool init() override;
    string Selection(sf::RenderWindow& window);
};

#endif //SFML_MENU_H
