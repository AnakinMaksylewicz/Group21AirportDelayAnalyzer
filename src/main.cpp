//
// Created by anakin on 10/15/2025.
//
#include "sfml_menu.h"
#include "csv_parser.h"
#include "merge_sort.h"
#include "heap_sort.h"
#include "quick_sort.h"
#include "compare.h"
#include "menu.h"
#include "data_generator.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
using namespace std;

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
    //variables for all our selections
    string selectedMonth, selectedYear, selectedMetric, selectedAlgorithm = "";
    vector<string> months = {"January", "February", "March", "April", "May", "June",
            "July", "August", "September", "October", "November", "December"};
    vector<string> years;
    for (int i = 1999; i <= 2016; ++i) {
        years.push_back(to_string(i));
    }
    vector<string> metrics = {"Total minutes delayed", "Delay rate", "Mean minutes per delayed flight",
        "Weather", "Carrier", "NAS", "Security minutes"};
    vector<string> algorithms = {"Merge sort", "Heap sort", "Quick sort", "Compare all"};

    sf::RenderWindow window(sf::VideoMode(800, 600), "Flight Delay Analyzer");

    //load font in main so it can be used by all different screens without issue
    sf::Font font;
    if (!font.loadFromFile("assets/HATTEN.TTF")) {
        cerr << "Error loading font." << endl;
    }

    //initial year month menu
    Menu mainMenu(font);
    mainMenu.init();

    while (window.isOpen()) {
        int result = mainMenu.run(window);
        //exit
        if (result == -1 || result == 2) {
            window.close();
            break;
        }
        if (result == 0) { //month selection
            MenuSelection month(font, months, "Select a Month");
            month.init();
            selectedMonth = month.Selection(window);

            if (selectedMonth.empty()) {break;}
        }
        else if (result == 1) { //year selection
            MenuSelection year(font, years, "Select a Year");
            year.init();
            selectedYear = year.Selection(window);

            if (selectedYear.empty()) {break;}
        }
        //metric selection
        MenuSelection metric(font, metrics, "Select a Metric");
        metric.init();
        selectedMetric = metric.Selection(window);

        if (selectedMetric.empty()) {break;}
        //algorithm selection
        MenuSelection algorithm(font, algorithms, "Select an Algorithm");
        algorithm.init();
        selectedAlgorithm = algorithm.Selection(window);

        if (selectedAlgorithm.empty()) {break;}

        //display data screen
        //repurposed logic from the console display (menu.cpp) credit to peter for that
        vector<Row> filteredData;
        bool groupByMonth = !selectedMonth.empty();
        int filterMonth = 0;
        int filterYear = 0;

        bool (*comp)(const Row&, const Row&) = nullptr;

        if (selectedMetric == "Total minutes delayed") {comp = compareByTotalMinutes;}
        else if (selectedMetric == "Delay rate") {comp = compareByDelayRate;}
        else if (selectedMetric == "Mean minutes per delayed flight") {comp = compareByAvgMinutesPerDelayedFlight;}
        else if (selectedMetric == "Weather") {comp = compareByWeatherMinutes;}
        else if (selectedMetric == "Carrier") {comp = compareByCarrierMinutes;}
        else if (selectedMetric == "NAS") {comp = compareByNASMinutes;}
        else if (selectedMetric == "Security minutes") {comp = compareBySecurityMinutes;}

        //sorting and timing
        chrono::duration<double, milli> duration, duration1, duration2;
        vector<Row> data1 = data, data2 = data;

        if (selectedAlgorithm == "Merge sort") {
            auto start = chrono::high_resolution_clock::now();
            mergeSort(data, comp);
            auto end = chrono::high_resolution_clock::now();
            duration = end - start;
        }
        else if (selectedAlgorithm == "Heap sort") {
            auto start = chrono::high_resolution_clock::now();
            heapSort(data, comp);
            auto end = chrono::high_resolution_clock::now();
            duration = end - start;
        }
        else if (selectedAlgorithm == "Quick sort") {
            auto start = chrono::high_resolution_clock::now();
            quickSort(data, comp);
            auto end = chrono::high_resolution_clock::now();
            duration = end - start;
        }
        else if (selectedAlgorithm == "Compare all") {
            auto start = chrono::high_resolution_clock::now();
            mergeSort(data, comp);
            auto end = chrono::high_resolution_clock::now();
            duration = end - start;

            start = chrono::high_resolution_clock::now();
            heapSort(data1, comp);
            end = chrono::high_resolution_clock::now();
            duration1 = end - start;

            start = chrono::high_resolution_clock::now();
            quickSort(data2, comp);
            end = chrono::high_resolution_clock::now();
            duration2 = end - start;
        }

        //filter data by selected metrics
        if (groupByMonth) {
            for (int i = 0; i < months.size(); ++i) {
                if (months[i] == selectedMonth) {filterMonth = i + 1;}
            }
            for (auto& row : data) {
                if (row.month == filterMonth) {filteredData.push_back(row);}
            }
        }
        else {
            filterYear = stoi(selectedYear);
            for (auto& row : data)
                if (row.year == filterYear) {filteredData.push_back(row);}
        }

        //actual display logic
        string title;
        if (groupByMonth)
            title = "Top 20 " + selectedMetric + " - for " + selectedMonth;
        else
            title = "Top 20 " + selectedMetric + " - for " + selectedYear;

        ostringstream timeInfo;
        if (selectedAlgorithm == "Compare all") {
            timeInfo << "Merge sort Time: " << fixed << setprecision(3) << duration.count() << "ms | "
                     << "Heap sort Time: " << duration1.count() << "ms | "
                     << "Quick sort Time: " << duration2.count() << "ms";
        } else {
            timeInfo << selectedAlgorithm << " Time: "
                     << fixed << setprecision(3)
                     << duration.count() << " ms";
        }

        DisplayData display(font, title, timeInfo.str(), filteredData, selectedMetric, groupByMonth, 20);
        //new larger window to fit all data
        sf::RenderWindow dataWindow(sf::VideoMode(940, 920), "Results - Flight Delay Analyzer");
        display.run(dataWindow);
    }
    return 0;
}
