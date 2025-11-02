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


void runMenu(vector<Row> data) {
    string mode;
    string metric;
    string algo;
    string n;
    cout << "---------------------------------------------\nFLIGHT DELAY ANALYZER\n---------------------------------------------\n";
    cout << "Loading dataset...\n";
    cout << "Successfully loaded dataset.\n";
    cout << "---------------------------------------------\n";
    cout << "Choose mode:\n[1] Airport-Month\n[2] Airport-Year\n";
    cout << "> " << flush;
    cin >> mode;
    while (mode != "1" && mode != "2") {
        cout << "Please enter a valid option.\n> " << flush;
        cin >> mode;
    }
    if (mode == "1") {
        cout << "Selected: Airport-Month\n---------------------------------------------\n";
    }
    else if (mode == "2") {
        cout << "Selected: Airport-Year\n---------------------------------------------\n";
    }
    cout << "Choose metric:\n[1] Total minutes delayed\n[2] Delay rate\n[3] Average minutes per delayed flight\n[4] Weather / Carrier / NAS / Security minutes\n";
    cout << "> " << flush;
    cin >> metric;
    while (metric != "1" && metric != "2" && metric != "3" && metric != "4") {
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
        cout << "Selected: Average minutes per delayed\n---------------------------------------------\n";
        comp = compareByAvgMinutesPerDelayedFlight;
    }
    else if (metric == "4") {
        cout << "Selected: Weather\n---------------------------------------------\n";
        comp = compareByWeather;
    }
    else if (metric == "5") {
        cout << "Selected: Carrier\n---------------------------------------------\n";
        comp = compareByCarrier;
    }
    else if (metric == "6") {
        cout << "Selected: NAS\n---------------------------------------------\n";
        comp = compareByNAS;
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
    //TODO: Add the quick sort option and change last option to "Compare all"
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
        cout << "Selected: Compare all\n---------------------------------------------\n" 
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
    // Call Algorithm and Output
    for (int i = 1; i <= k; i++) {
        // cout data[i]
    }
}
