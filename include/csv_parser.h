//
// Created by anakin on 10/15/2025.
//

#ifndef CSV_PARSER_H
#define CSV_PARSER_H
#include <string>
#include <vector>

//Row struct for storing attributes from each row of csv file into
//one object
struct Row {
    //identifiers
    std::string airportCode; //airport code, e.g. ATL
    std::string airportName; //obvious

    //time info
    int year; //time.year in the csv file
    int month; //time.month in the csv file

    //Flight counts
    int flightsTotal;
    int flightsDelayed;

    //Minutes delayed by cause, refer to CSV documentation
    //https://corgis-edu.github.io/corgis/csv/airlines/
    //for the meaning of each
    int minutesCarrier;
    int minutesWeather;
    int minutesNAS;
    int minutesLateAC;
    int minutesSecurity;

    int minutesTotal; //total minutes delayed
};

//function for loading CSV file
std::vector<Row> loadCSV(const std::string& fileName);

#endif //CSV_PARSER_H
