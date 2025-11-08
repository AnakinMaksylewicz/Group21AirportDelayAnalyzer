//
// Created by anakin on 10/15/2025.
//
#include "data_generator.h"
#include <iostream>
#include <random>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;
//Function for generating the 100,000 data points we need as per instructions

//The way it works is that we take the vector full of rows that we loaded
//from the csv, and slightly modify each row's attributes randomly to achieve
//100,000 data points
vector<Row> generateSyntheticData(const vector<Row> &originalData, unsigned int targetSize) {
    vector<Row> extended = originalData;
    if (originalData.empty()) {
        cerr << "Empty original data" << endl;
        return extended;
    }

    //randomness generator setup stuff
    random_device rd;
    mt19937 gen(42);
    //random difference between -50% and +50% for the attributes
    //we apply this to
    uniform_real_distribution<> variation(-0.5, 0.5);
    //random int difference  to shift months
    uniform_int_distribution monthShift(-5, 5);
    //random year shift
    uniform_int_distribution yearShift(-8, 8);
    //random generator for indices for generating rows
    uniform_int_distribution randomIndex(0, static_cast<int>(originalData.size() - 1));

    //Track airport-month-year combinations to set max limit on dupes to avoid too many
    //repetitive entries
    unordered_map<string, int> dupeKeys;
    const int MAX_DUPES_PER_KEY = 2;

    //record existing combos from original data
    for (const auto& row : originalData) {
        string key = row.airportCode + "_" + to_string(row.month) + "_" + to_string(row.year);
        dupeKeys[key]++;
    }

    //loop until extended size is 100,000
    while (extended.size() < targetSize) {
        //take a random base row to modify its attributes
        const Row &base = originalData[randomIndex(gen)];

        Row copy = base; //initialize copy object so that we can append to extended

        //Slightly vary stuff
        copy.month = base.month + monthShift(gen);
        //Wrap months if they become < 1 or > 12
        if (copy.month < 1)
            copy.month += 12;
        if (copy.month > 12)
            copy.month -= 12;

        copy.year = base.year + yearShift(gen);
        //Make sure years are between 1999 and 2020 inclusive
        if (copy.year < 1999)
            copy.year = 1999 + (rand() % 3);
        if (copy.year > 2020)
            copy.year = 2018 + (rand() % 3);

        //EXTREMELY IMPORTANT: check airport, month, year, so that data doesn't repeat excessively
        string key = copy.airportCode + "_" + to_string(copy.month) + "_" + to_string(copy.year);
        if (dupeKeys[key] >= MAX_DUPES_PER_KEY) {
            continue; //Skip over rows that have reached the dupe limit
        }
        //Increase dupeKeys count by 1 to check against maximum dupe key
        dupeKeys[key]++;
        cout << "key inserted. extended size: " << extended.size() << endl;
        cout << "dupe key size: " << dupeKeys.size() << endl;
        //Lambda function for random variation for delay attributes
        auto vary = [&](int value) -> int {
            return static_cast<int>(value * (1 + variation(gen)));
        };
        //slightly vary the delay minutes for each attribute
        copy.flightsDelayed = vary(base.flightsDelayed);
        copy.flightsTotal = vary(base.flightsTotal);
        if (copy.flightsDelayed > copy.flightsTotal)
            copy.flightsDelayed = copy.flightsTotal;
        copy.minutesCarrier = vary(base.minutesCarrier);
        copy.minutesLateAC = vary(base.minutesLateAC);
        copy.minutesNAS = vary(base.minutesNAS);
        copy.minutesSecurity = vary(base.minutesSecurity);
        copy.minutesWeather = vary(base.minutesWeather);
        //recalculate total and push to extended
        copy.minutesTotal = copy.minutesCarrier + copy.minutesLateAC
                            + copy.minutesNAS + copy.minutesSecurity
                            + copy.minutesWeather;

        extended.push_back(copy);
    }
    cout << "Extended dataset from " << originalData.size() <<
            " to " << extended.size() << " rows" << endl;
    return extended;
}
