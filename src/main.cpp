//
// Created by anakin on 10/15/2025.
//
#include "csv_parser.h"
#include "data_generator.h"
#include "heap_sort.h"
#include "menu.h"
#include "merge_sort.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "sfml_menu.h"

//main should be only a few lines, we're going to do the menu in a runMenu(data) function
int main(){
    std::string fileName = "../data/airlines.csv";
    std::string menuOption;
    //Load data in this line
    std::vector<Row> data = loadCSV(fileName);
    //extend data to 100,000 datapoints as per assignment instructions (100,000 data points / 7 metrics = ~15,000 necessary rows)
    //data = generateSyntheticData(data, 15000);
    std::cout << "---------------------------------------------\nFLIGHT DELAY ANALYZER\n---------------------------------------------\n";

    std::cout << "Choose a menu option:\n[1] Console\n[2] SFML\n> " << std::flush;
    std::cin >> menuOption;
    while (menuOption != "1" && menuOption != "2") {
        std::cout << "Please enter a valid option.\n> " << std::flush;
        std::cin >> menuOption;
    }
    if (menuOption == "1") {
        while (true) {
            //run menu in this line, passing in the data
            if (runMenu(data) == 1) {
                return 0;
            }
        }
    }
    //sfml menu
    sf::RenderWindow window(sf::VideoMode(800, 600), "Main Menu");

    //load font in main so it can be used by all different screens without issue
    sf::Font font;
    if (!font.loadFromFile("assets/HATTEN.TTF")) {
        std::cerr << "Error loading font." << std::endl;
    }

    //initial year month menu
    Menu mainMenu(font);
    mainMenu.init();

    while (window.isOpen()) {
        int result = mainMenu.run(window);
        //exit clicked
        if (result == -1 || result == 2) {window.close();}
        //month selection
        else if (result == 0) {
            vector<string> months = {"January", "February", "March", "April", "May", "June",
            "July", "August", "September", "October", "November", "December"};
            TimeSelection month(font, months, "Select a Month");
            month.init();
            string selectedMonth = month.Selection(window);
            }
        //year selection
        else if (result == 1) {
            vector<string> years;
            for (int i = 1999; i <= 2020; ++i) {
                years.push_back(to_string(i));
            }
            TimeSelection year(font, years, "Select a Year");
            year.init();
            string selectedYear = year.Selection(window);
            }
    }
    return 0;
}
