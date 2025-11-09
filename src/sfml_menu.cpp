//
// Created by denni on 11/8/2025.
//

#include "sfml_menu.h"
#include <iostream>
#include <iomanip>

//button implementations
Button::Button(const string& text, const sf::Font& font,sf::Vector2f size, sf::Vector2f position, int fontSize,
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
Screen::Screen(const sf::Font& f, const string& title, sf::Color background) : font(f), backgroundColor(background) {

    titleText.setFont(font);
    titleText.setString(title);
    titleText.setCharacterSize(60);
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
    buttons.emplace_back("Airport - Months", font,  sf::Vector2f(250,100),sf::Vector2f(275,200), 40);
    buttons.emplace_back("Airport - Years", font,  sf::Vector2f(250,100),sf::Vector2f(275,310), 40);
    buttons.emplace_back("Exit", font,  sf::Vector2f(250,100),sf::Vector2f(275,420), 40);
    return true;
}

//month/year selection
MenuSelection::MenuSelection(const sf::Font& f, const vector<string> &options, const string &title) : Screen(f, title), options(options) {}

bool MenuSelection::init() {

    //respective button display information in each selection menu
    //differentiate which selection menu by the size of the options vector (hardcoded sizes with our values)
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
    else if (options.size() == 7) { //single column display, smaller buttons
        for (int i = 0; i < options.size(); ++i) {
            float startingY = 150;
            float startingX = 250;
            float ySpace = 55;

            int row = i;

            buttons.emplace_back(options[i],font, sf::Vector2f(300, 50),sf::Vector2f(startingX,
                startingY + row * ySpace), 26);
        }
    }
    else if (options.size() == 4) { //single column display, larger buttons
        for (int i = 0; i < options.size(); ++i) {
            float startingY = 150;
            float startingX = 250;
            float ySpace = 85;

            int row = i;

            buttons.emplace_back(options[i],font, sf::Vector2f(300, 75),sf::Vector2f(startingX,
                startingY + row * ySpace), 35);
        }
    }
    else { //years display
        for (int i = 0; i < options.size(); ++i) {
            float startingY = 150;
            float startingX = 175;
            float xSpace = 250;
            float ySpace = 40;
            //half of the years in the available years
            int half = 9;
            //if col is 0, 1st column, if 1, 2nd column
            int col = i/half;
            int row = i%half;

            buttons.emplace_back(options[i],font, sf::Vector2f(200, 35),sf::Vector2f(startingX + col * xSpace,
                startingY + row * ySpace), 30);
        }
    }
    return true;
}

string MenuSelection::Selection(sf::RenderWindow& window) {
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

//display data screen
DisplayData::DisplayData(const sf::Font& f, const string& title, const string& timeInfo, const vector<Row>& data, const string& metric,
bool groupByMonth, int n) : font(f), backgroundColor(sf::Color(54,186,216)), headerColor(sf::Color(0,35,165)),
regularColor(sf::Color(0,35,165)), highlightColor(sf::Color(250,70,22)) {
    //title formatting
    titleText.setFont(font);
    titleText.setString(title);
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::White);
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.left + titleBounds.width / 2.0f, titleBounds.top + titleBounds.height / 2.0f);
    titleText.setPosition(470, 40);

    //sort timing formatting
    timeText.setFont(font);
    timeText.setString(timeInfo);
    timeText.setCharacterSize(30);
    timeText.setFillColor(sf::Color::White);
    sf::FloatRect timeBounds = timeText.getLocalBounds();
    timeText.setOrigin(timeBounds.left + timeBounds.width / 2.0f, timeBounds.top + timeBounds.height / 2.0f);
    timeText.setPosition(470, 110);

    //table formatting
    float startingX = 30.0f;
    float startingY = 140.0f;
    float rowHeight = 36.0f;

    //widths of columns to allow data to fit within respective area
    float colWidths[] = {60, 80, 500, 120, 120};  //total = 830
    vector<string> headers = {"Rank", "Code", "Airport Name", "Context", "Value"};

    //header formatting
    sf::RectangleShape headerBox(sf::Vector2f(880, rowHeight));
    headerBox.setPosition(startingX, startingY);
    headerBox.setFillColor(headerColor);
    rowBoxes.push_back(headerBox);

    float x = startingX;
    for (int i = 0; i < headers.size(); ++i) {
        sf::Text headerText;
        headerText.setFont(font);
        headerText.setCharacterSize(20);
        headerText.setFillColor(sf::Color::White);
        headerText.setString(headers[i]);
        headerText.setPosition(x + 10, startingY + 6);
        //separate logic for final header title, to make it right aligned
        if (headers[i] == "Value") {
            sf::FloatRect bounds = headerText.getLocalBounds();
            headerText.setPosition(x + colWidths[i] - bounds.width - 10, startingY + 6);
        }
        rowTexts.push_back(headerText);
        x += colWidths[i];
    }

    //data row formatting
    int visibleRows = min(n, static_cast<int>(data.size()));
    string months[12] = {"January","February","March","April","May","June", "July","August","September","October","November","December"};

    float y = startingY + rowHeight;
    for (int i = 0; i < visibleRows; ++i) {
        const Row& row = data[data.size() - 1 - i];
        sf::RectangleShape box(sf::Vector2f(880, rowHeight));
        box.setPosition(startingX, y);
        //logic to have alternating colors per row, for visibility
        box.setFillColor(i % 2 == 0 ? sf::Color(230,240,250) : sf::Color(210,225,240));
        rowBoxes.push_back(box);

        double val = 0.0;
        if      (metric == "Total minutes delayed") {val = row.minutesTotal;}
        else if (metric == "Delay rate") {val = (row.flightsTotal == 0 ? 0.0 : 100.0 * (double)row.flightsDelayed / row.flightsTotal);}
        else if (metric == "Mean minutes per delayed flight") {val = (row.flightsDelayed == 0 ? 0.0 : (double)row.minutesTotal / row.flightsDelayed);}
        else if (metric == "Weather") {val = row.minutesWeather;}
        else if (metric == "Carrier") {val = row.minutesCarrier;}
        else if (metric == "NAS") {val = row.minutesNAS;}
        else if (metric == "Security minutes") {val = row.minutesSecurity;}

        string context = groupByMonth ? to_string(row.year) : months[row.month - 1];
        ostringstream valueStr;
        valueStr << fixed << setprecision(2) << val;

        //data text formatting
        vector<string> fields = {to_string(i + 1), row.airportCode, row.airportName, context, valueStr.str()};
        float xPos = startingX;
        for (int j = 0; j < fields.size(); ++j) {
            sf::Text cell;
            cell.setFont(font);
            cell.setCharacterSize(20);
            //highlight first column orange, otherwise black
            cell.setFillColor((j == 0) ? highlightColor : sf::Color::Black);
            cell.setString(fields[j]);

            //align final column to right side
            if (j == 4) {
                sf::FloatRect bounds = cell.getLocalBounds();
                cell.setPosition(xPos + colWidths[j] - bounds.width - 10, y + 5);
            }
            else {
                cell.setPosition(xPos + 10, y + 5);
            }
            rowTexts.push_back(cell);
            xPos += colWidths[j];
        }
        y += rowHeight;
    }
}

void DisplayData::draw(sf::RenderWindow& window) {
    window.clear(backgroundColor);
    window.draw(titleText);
    window.draw(timeText);
    for (auto& box : rowBoxes) {window.draw(box);}
    for (auto& text : rowTexts) {window.draw(text);}
    window.display();
}

bool DisplayData::run(sf::RenderWindow& window) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false;
            }
        }
        draw(window);
    }
    return true;
}