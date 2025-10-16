//
// Created by anakin on 10/15/2025.
//
#include "csv_parser.h"
#include <fstream>
#include <iostream>

using namespace std;

std::vector<Row> loadCSV(const std::string& fileName) {
    vector<Row> data;
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
        return data;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        vector<string> attributes;
        string field;
        //Had to code it like this instead of using string stream b/c
        //raw csv file has commas for things like airport name and carriers
        bool insideQuotes = false;
        for (char c : line) {
            //Flips insideQuotes so that airport name/carriers are properly added w/ quotes
            if (c == '"') {
                insideQuotes = !insideQuotes;
            }
            //once we hit a comma delimiter, add field to attributes vector
            //and clear field for next attribute
            else if (c == ',' && !insideQuotes) {
                attributes.push_back(field);
                field.clear();
            }
            else {
                field += c;
            }
        }
        attributes.push_back(field); //add very last attribute to vector

        //skips over incomplete rows just in case the csv file is messed up
        if (attributes.size() < 24) continue;

        //initialize Row struct and push into data vector
        //attributes index number corresponds to column in csv file
        Row row;
        row.airportCode = attributes[0];
        row.airportName = attributes[1];
        row.month = stoi(attributes[3]);
        row.year = stoi(attributes[5]);
        row.flightsDelayed = stoi(attributes[14]);
        row.flightsTotal = stoi(attributes[17]);
        row.minutesCarrier = stoi(attributes[18]);
        row.minutesLateAC = stoi(attributes[19]);
        row.minutesNAS = stoi(attributes[20]);
        row.minutesSecurity = stoi(attributes[21]);
        row.minutesTotal = stoi(attributes[22]);
        row.minutesWeather = stoi(attributes[23]);

        data.push_back(row);
    }

    file.close();
    cout << "Loaded " << data.size() << " rows from " << fileName << endl;
    return data;
}