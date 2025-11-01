//
// Created by anakin on 11/1/2025.
//

#ifndef COMPARE_H
#define COMPARE_H

#include "csv_parser.h"

bool compareByTotalMinutes(const Row& a, const Row& b);
bool compareByDelayRate(const Row& a, const Row& b);
bool compareByAvgMinutesPerDelayedFlight(const Row& a, const Row& b);
bool compareByWeatherMinutes(const Row& a, const Row& b);
bool compareByCarrierMinutes(const Row& a, const Row& b);
bool compareByNASMinutes(const Row& a, const Row& b);
bool compareBySecurityMinutes(const Row& a, const Row& b);

#endif //COMPARE_H
