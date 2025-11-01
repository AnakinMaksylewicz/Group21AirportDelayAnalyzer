#include "menu.h"

#include <csv_parser.h>
#include <iostream>
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
    if (metric == "1") {
        cout << "Selected: Total minutes delayed\n---------------------------------------------\n";
    }
    else if (metric == "2") {
        cout << "Selected: Delay rate\n---------------------------------------------\n";
    }
    else if (metric == "3") {
        cout << "Selected: Average minutes per delayed\n---------------------------------------------\n";
    }
    else if (metric == "4") {
        cout << "Selected: Weather / Carrier / NAS / Security minutes\n---------------------------------------------\n";
    }
    cout << "Choose algorithm:\n[1] Merge sort\n[2] Heap sort\n[3] Compare both\n";
    cout << "> " << flush;
    cin >> algo;
    while (algo != "1" && algo != "2" && algo != "3") {
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
        cout << "Selected: Compare both\n---------------------------------------------\n";
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
