//
// Created by anakin on 11/1/2025.
//
#include "compare.h"

bool compareByTotalMinutes(const Row& a, const Row& b) {
    return a.minutesTotal < b.minutesTotal;
}
bool compareByDelayRate(const Row& a, const Row& b) {
    //Delay rate = delayed flights / total flights

    //I doubt flightsTotal will ever be zero, but I added this just in case my data_generator function messes up
    double rateA = (a.flightsTotal == 0) ? 0 : (double)a.flightsDelayed / (double)a.flightsTotal;
    double rateB = (b.flightsTotal == 0) ? 0 : (double)b.flightsDelayed / (double)b.flightsTotal;
    return rateA < rateB;
}
bool compareByAvgMinutesPerDelayedFlight(const Row& a, const Row& b) {
    //Avg minutes per delayed flight = total minutes / delayed flights
    double rateA = (a.flightsDelayed == 0) ? 0 : (double)a.minutesTotal / (double)a.flightsDelayed;
    double rateB = (b.flightsDelayed == 0) ? 0 : (double)b.minutesTotal / (double)b.flightsDelayed;
    return rateA < rateB;
}
bool compareByWeatherMinutes(const Row& a, const Row& b) {
    return a.minutesWeather < b.minutesWeather;
}
bool compareByCarrierMinutes(const Row& a, const Row& b) {
    return a.minutesCarrier < b.minutesCarrier;
}
bool compareByNASMinutes(const Row& a, const Row& b) {
    return a.minutesNAS < b.minutesNAS;
}
bool compareBySecurityMinutes(const Row& a, const Row& b) {
    return a.minutesSecurity < b.minutesSecurity;
}