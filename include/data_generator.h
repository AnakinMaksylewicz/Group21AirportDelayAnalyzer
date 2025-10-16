//
// Created by anakin on 10/15/2025.
//

#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H
#include "vector"
#include "csv_parser.h"

//we're going to need to extend the csv data to have 100,000 rows
//as per instructions, so this function does that
std::vector<Row> generateSyntheticData(const std::vector<Row>& originalData, unsigned int targetSize = 100000);
#endif //DATA_GENERATOR_H
