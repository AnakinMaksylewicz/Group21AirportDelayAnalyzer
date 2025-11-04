//
// Created by anakin on 11/1/2025.
//
#include "compare.h"

bool compareByTotalMinutes(const Row& a, const Row& b) {
    //These are all "tie breaker" conditionals I implemented because
    //quick sort was breaking without them
    if (a.minutesTotal == b.minutesTotal)
        return a.airportCode < b.airportCode;
    return a.minutesTotal < b.minutesTotal;
}
bool compareByDelayRate(const Row& a, const Row& b) {
    //Delay rate = delayed flights / total flights

    //I doubt flightsTotal will ever be zero, but I added this just in case my data_generator function messes up
    double rateA = (a.flightsTotal == 0) ? 0 : (double)a.flightsDelayed / (double)a.flightsTotal;
    double rateB = (b.flightsTotal == 0) ? 0 : (double)b.flightsDelayed / (double)b.flightsTotal;
    if (rateA == rateB)
        return a.airportCode < b.airportCode;
    return rateA < rateB;
}
bool compareByAvgMinutesPerDelayedFlight(const Row& a, const Row& b) {
    //Avg minutes per delayed flight = total minutes / delayed flights
    double rateA = (a.flightsDelayed == 0) ? 0 : (double)a.minutesTotal / (double)a.flightsDelayed;
    double rateB = (b.flightsDelayed == 0) ? 0 : (double)b.minutesTotal / (double)b.flightsDelayed;
    if (rateA == rateB)
        return a.airportCode < b.airportCode;
    return rateA < rateB;
}
bool compareByWeatherMinutes(const Row& a, const Row& b) {
    if (a.minutesWeather == b.minutesWeather)
        return a.airportCode <= b.airportCode;
    return a.minutesWeather < b.minutesWeather;
}
bool compareByCarrierMinutes(const Row& a, const Row& b) {
    if (a.minutesCarrier == b.minutesCarrier)
        return a.airportCode < b.airportCode;
    return a.minutesCarrier < b.minutesCarrier;
}
bool compareByNASMinutes(const Row& a, const Row& b) {
    if (a.minutesNAS == b.minutesNAS)
        return a.airportCode < b.airportCode;
    return a.minutesNAS < b.minutesNAS;
}
bool compareBySecurityMinutes(const Row& a, const Row& b) {
    if (a.minutesSecurity == b.minutesSecurity)
        return a.airportCode < b.airportCode;
    return a.minutesSecurity < b.minutesSecurity;
}