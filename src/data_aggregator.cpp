//
// Created by anakin on 11/3/2025.
//
#include "data_aggregator.h"
#include <unordered_map>
#include <string>

std::vector<Row> aggregateSortedData(std::vector <Row>& data, bool groupByMonth, bool groupByYear) {
    std::unordered_map <std::string, Row> aggregatedMap; //Map airport codes to rows
    if (groupByMonth) {
        for (const auto& row : data) {
            std::string key = row.airportCode + "_" + std::to_string(row.month);

            auto it = aggregatedMap.find(key);
            if (it == aggregatedMap.end()) { //If key not found
                aggregatedMap[key] = row;
            }
            else {
                Row& agg = it->second;
                agg.flightsDelayed += row.flightsDelayed;
                agg.flightsTotal += row.flightsTotal;
                agg.minutesCarrier += row.minutesCarrier;
                agg.minutesLateAC += row.minutesLateAC;
                agg.minutesNAS += row.minutesNAS;
                agg.minutesSecurity += row.minutesSecurity;
                agg.minutesWeather += row.minutesWeather;
                agg.minutesTotal += row.minutesTotal;
            }
        }
    }
    else if (groupByYear) {
        for (const auto& row : data) {
            std::string key = row.airportCode + "_" + std::to_string(row.year);

            auto it = aggregatedMap.find(key);
            if (it == aggregatedMap.end()) { //If key not found
                aggregatedMap[key] = row;
            }
            else { //If key found, sum values
                Row& agg = it->second;
                agg.flightsDelayed += row.flightsDelayed;
                agg.flightsTotal += row.flightsTotal;
                agg.minutesCarrier += row.minutesCarrier;
                agg.minutesLateAC += row.minutesLateAC;
                agg.minutesNAS += row.minutesNAS;
                agg.minutesSecurity += row.minutesSecurity;
                agg.minutesWeather += row.minutesWeather;
                agg.minutesTotal += row.minutesTotal;
            }
        }
    }
    //Go through aggregated map and push back to return vector
    std::vector<Row> aggregated;
    aggregated.reserve(aggregatedMap.size()); //Optimizes the below for loop by reducing mem. realloc. (thx CLion)
    for (const auto& entry : aggregatedMap) {
        aggregated.push_back(entry.second);
    }
    return aggregated;
}