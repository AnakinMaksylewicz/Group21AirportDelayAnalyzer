#include "menu.h"
#include "csv_parser.h"
#include "merge_sort.h"
#include "heap_sort.h"
#include "quick_sort.h"
#include "compare.h"

#include <iostream>
#include <chrono>
#include <locale>
#include <ostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

bool isInteger(const std::string& s) {
    if (s.empty()) return false;

    size_t i = 0;
    if (s[0] == '+') i = 1;
    if (i == s.size()) return false;

    for (; i < s.size(); ++i)
        if (!std::isdigit(s[i])) return false;

    return true;
}


int runMenu(vector<Row> data) {
    string mode;
    string metric;
    string algo;
    string n;
    bool groupByMonth = false, groupByYear = false;
    //map for selecting months and then converting them to numbers (will be used to filter)
    unordered_map<string, int> monthMap = {
        {"january", 1}, {"february", 2}, {"march", 3}, {"april", 4},
        {"may", 5}, {"june", 6}, {"july", 7}, {"august", 8},
        {"september", 9}, {"october", 10}, {"november", 11}, {"december", 12},
        {"jan", 1}, {"feb", 2}, {"mar", 3}, {"apr", 4},
        {"jun", 6}, {"jul", 7}, {"aug", 8}, {"sep", 9},
        {"oct", 10}, {"nov", 11}, {"dec", 12}
    };

    string monthInput;
    int filterYear = 0;
    int filterMonth = 0;
    cout << "Choose mode:\n[1] Airport-Month\n[2] Airport-Year\n[3] Exit\n";
    cout << "> " << flush;
    cin >> mode;
    while (mode != "1" && mode != "2" && mode != "3") {
        cout << "Please enter a valid option.\n> " << flush;
        cin >> mode;
    }
    if (mode == "1") {
        cout << "Selected: Airport-Month\n---------------------------------------------\n";
        groupByMonth = true;
        cout << "Enter the month name (e.g., January or Jan):\n> " << flush;
        cin >> monthInput;

        //convert to lowercase for easier lookup
        for (auto& c : monthInput) c = tolower(c);

        auto it = monthMap.find(monthInput);
        while (it == monthMap.end()) {
            cout << "Invalid month. Please enter a valid month name:\n> " << flush;
            cin >> monthInput;
            for (auto& c : monthInput) c = tolower(c);
            it = monthMap.find(monthInput);
        }
        filterMonth = it->second;
    }
    else if (mode == "2") {
        cout << "Selected: Airport-Year\n---------------------------------------------\n";
        groupByYear = true;
        cout << "Enter year (1999 - 2016):\n> " << flush;

        while (true) {
            if (!(cin >> filterYear)) {
                //handle non-integer inputs
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a numeric year (1999 - 2016):\n> " << flush;
                continue;
            }

            if (filterYear >= 1999 && filterYear <= 2016)
                break;

            cout << "Invalid year. Enter a year between 1999 and 2016 (inclusive):\n> " << flush;
        }
    }
    else if (mode == "3") {
        return 1;
    }
    cout << "Choose metric:\n[1] Total minutes delayed\n[2] Delay rate\n[3] Average minutes per delayed flight\n[4] Weather\n[5] Carrier\n[6] NAS\n[7] Security minutes\n";
    cout << "> " << flush;
    cin >> metric;
    while (metric != "1" && metric != "2" && metric != "3" && metric != "4" && metric != "5" && metric != "6" && metric != "7") {
        cout << "Please enter a valid option.\n> " << flush;
        cin >> metric;
    }

    bool(*comp)(const Row&, const Row&);

    if (metric == "1") {
        cout << "Selected: Total minutes delayed\n---------------------------------------------\n";
        comp = compareByTotalMinutes;
    }
    else if (metric == "2") {
        cout << "Selected: Delay rate\n---------------------------------------------\n";
        comp = compareByDelayRate;
    }
    else if (metric == "3") {
        cout << "Selected: Average minutes per delayed flight\n---------------------------------------------\n";
        comp = compareByAvgMinutesPerDelayedFlight;
    }
    else if (metric == "4") {
        cout << "Selected: Weather\n---------------------------------------------\n";
        comp = compareByWeatherMinutes;
    }
    else if (metric == "5") {
        cout << "Selected: Carrier\n---------------------------------------------\n";
        comp = compareByCarrierMinutes;
    }
    else if (metric == "6") {
        cout << "Selected: NAS\n---------------------------------------------\n";
        comp = compareByNASMinutes;
    }
    else if (metric == "7") {
        cout << "Selected: Security Minutes\n---------------------------------------------\n";
        comp = compareBySecurityMinutes;
    }
    cout << "Choose algorithm:\n[1] Merge sort\n[2] Heap sort\n[3] Quick sort\n[4] Compare all\n";
    cout << "> " << flush;
    cin >> algo;
    while (algo != "1" && algo != "2" && algo != "3" && algo != "4") {
        cout << "Please enter a valid option.\n> " << flush;
        cin >> algo;
    }

    if (algo == "1") {
        cout << "Selected: Merge sort\n---------------------------------------------\n";
    }
    else if (algo == "2") {
        cout << "Selected: Heap sort\n---------------------------------------------\n";
    }
    else if (algo == "3") {
        cout << "Selected: Quick sort\n---------------------------------------------\n";
    }
    else if (algo == "4") {
        cout << "Selected: Compare all\n---------------------------------------------\n" ;
    }
    cout << "Enter Top-N to display.\n";
    cout << "> " << flush;
    cin >> n;
    while (!isInteger(n)) {
        cout << "Please enter a valid integer.\n> " << flush;
        cin >> n;
    }
    int k = stoi(n);
    cout << "---------------------------------------------\n";
    chrono::duration<double, milli> duration;
    chrono::duration<double, milli> duration1;
    chrono::duration<double, milli> duration2;
    if (algo == "1"){
        auto start = chrono::high_resolution_clock::now();
        mergeSort(data, comp);
        auto end = chrono::high_resolution_clock::now();
        duration = end - start;
    }
    else if (algo == "2"){
        auto start = chrono::high_resolution_clock::now();
        heapSort(data, comp);
        auto end = chrono::high_resolution_clock::now();
        duration = end - start;
    }
    else if (algo == "3"){
        auto start = chrono::high_resolution_clock::now();
        quickSort(data, comp);
        auto end = chrono::high_resolution_clock::now();
        duration = end - start;
    }
    else {
        vector<Row> data1 = data;
        vector<Row> data2 = data;
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
    // Output
    if (algo == "4"){
        cout << "Times to execute:\n";
        cout << "Merge sort: " << duration.count() << "ms\n";
        cout << "Heap sort: " << duration1.count() << "ms\n";
        cout << "Quick sort: " << duration2.count() << "ms\n";
        cout << "---------------------------------------------\n";
    }
    else {
        cout << "Time to execute: " << duration.count() << "ms\n";
        cout << "---------------------------------------------\n";
    }

    vector<Row> filtered;

    if (groupByMonth) {
        for (const auto& row : data) if (row.month == filterMonth) filtered.push_back(row);
    }
    else {
        for (const auto& row : data) if (row.year == filterYear) filtered.push_back(row);
    }
    auto metricName = (metric == "1" ? "Total Minutes Delayed" :
                          (metric == "2" ? "Delay Rate" :
                          (metric == "3" ? "Avg Minutes per Delay" :
                          (metric == "4" ? "Weather Minutes" :
                          (metric == "5" ? "Carrier Minutes" :
                          (metric == "6" ? "NAS Minutes" : "Security Minutes"))))));
    //Month name array for display,
    string monthName[12] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
    if (groupByMonth)
        cout << "Top " << k << " by " << metricName << " (Month = " << monthName[filterMonth - 1] << " across ALL years)\n";
    else
        cout << "Top " << k << " by " << metricName << " (Year = " << filterYear << " across ALL months)\n";
    int j = 1;
    for (int i = static_cast<int>(filtered.size()) - 1; i >= static_cast<int>(filtered.size()) - k && i >= 0; i--) {
        const Row& row = filtered[i];
        cout << "[" << j << "] " << row.airportCode << " " << row.airportName;
        if (groupByMonth) {
            //show year context if we're displaying by month
            cout << " " << row.year << ", ";
        } else {
            //show month context if we're displaying by year
            cout << " " << monthName[row.month - 1] << ", ";
        }

        if      (metric == "1") cout << row.minutesTotal << " minutes delayed\n";
        else if (metric == "2") cout << (row.flightsTotal == 0 ? 0.0 : 100.0 * (double)row.flightsDelayed / (double)row.flightsTotal) << "% delay rate\n";
        else if (metric == "3") cout << (row.flightsDelayed == 0 ? 0.0 : (double)row.minutesTotal / (double)row.flightsDelayed) << " min per delayed flight\n";
        else if (metric == "4") cout << row.minutesWeather  << " weather minutes\n";
        else if (metric == "5") cout << row.minutesCarrier  << " carrier minutes\n";
        else if (metric == "6") cout << row.minutesNAS      << " NAS minutes\n";
        else
            cout << row.minutesSecurity << " security minutes\n";
        j++;
    }

    cout << "---------------------------------------------\n";
    return 0;

}



