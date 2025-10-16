//
// Created by anakin on 10/15/2025.
//
#include "csv_parser.h"
#include "data_generator.h"
#include "heap_sort.h"
#include "menu.h"
#include "merge_sort.h"

//main should be only a few lines, we're going to do the menu in a runMenu(data) function
int main(){
    std::string fileName = "../data/airlines.csv";
    //Load data in this line
    std::vector<Row> data = loadCSV(fileName);
    //run menu in this line, passing in the data
    return 0;
}