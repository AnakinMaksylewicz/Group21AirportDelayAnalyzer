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
    data = generateSyntheticData(data, 15000);
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
    Menu menu;
    if (!menu.init())
        return -1;

    while (window.isOpen()) {
        int result = menu.run(window);
        if (result == 0)
            window.close();
        else if (result == 1) {
            sf::RenderWindow sub(sf::VideoMode(600, 400), "Window 1");
            while (sub.isOpen()) {
                sf::Event e;
                while (sub.pollEvent(e))
                    if (e.type == sf::Event::Closed) sub.close();
                sub.clear(sf::Color::Blue);
                sub.display();
            }
        } else if (result == 2) {
            sf::RenderWindow sub(sf::VideoMode(600, 400), "Window 2");
            while (sub.isOpen()) {
                sf::Event e;
                while (sub.pollEvent(e))
                    if (e.type == sf::Event::Closed) sub.close();
                sub.clear(sf::Color::Green);
                sub.display();
            }
        }
    }
    return 0;
}
