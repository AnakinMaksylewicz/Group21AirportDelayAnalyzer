//
// Created by anakin on 10/15/2025.
//
#include "data_generator.h"
#include <iostream>
#include <random>
using namespace std;
//Function for generating the 100,000 rows we need as per instructions

//The way it works is that we take the vector full of rows that we loaded
//from the csv, and slightly modify each row's attributes randomly to achieve
//100,000 rows
vector<Row> generateSyntheticData(const vector<Row> &originalData, unsigned int targetSize) {
    vector<Row> extended = originalData;
    if (originalData.empty()) {
        cerr << "Empty original data" << endl;
        return extended;
    }

    //randomness generator setup stuff
    random_device rd;
    mt19937 gen(rd());
    //random difference between -15% and +15% for the attributes
    //we apply this to
    uniform_real_distribution<> variation(-0.15, 0.15);
    //random int difference between -11 and 11 to shift months
    uniform_int_distribution monthShift(-11, 11);
    //random 5 year shift
    uniform_int_distribution yearShift(-5, 5);

    //loop until extended size is 100,000
    while (extended.size() < targetSize) {
        //take a base row to modify its attributes, use modulo so that
        //once we hit the end of originalData, it wraps around
        const Row &base = originalData[extended.size() % originalData.size()];

        Row copy = base; //initialize copy object so that we can append to extended

        //Slightly vary stuff
        copy.month = base.month + monthShift(gen);
        //Wrap months if they become < 1 or > 12
        if (copy.month < 1)
            copy.month += 12;
        if (copy.month > 12)
            copy.month -= 12;
        copy.year = base.year + yearShift(gen);

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
