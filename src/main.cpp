//
// Created by anakin on 10/15/2025.
//
#include "csv_parser.h"
#include "data_generator.h"
#include "heap_sort.h"
#include "menu.h"
#include "merge_sort.h"
#include <iostream>

//main should be only a few lines, we're going to do the menu in a runMenu(data) function
int main(){
    std::string fileName = "../data/airlines.csv";
    //Load data in this line
    std::vector<Row> data = loadCSV(fileName);
    //extend data to 100,000 datapoints as per assignment instructions (100,000 data points / 7 metrics = ~15,000 necessary rows)
    data = generateSyntheticData(data, 15000);
    std::cout << "---------------------------------------------\nFLIGHT DELAY ANALYZER\n---------------------------------------------\n";
    while (true) {
        //run menu in this line, passing in the data
        if (runMenu(data) == 1) {
            return 0;
        }
    }
}
