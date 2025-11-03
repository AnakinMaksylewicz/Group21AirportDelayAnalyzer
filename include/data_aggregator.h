//
// Created by anakin on 11/3/2025.
//

#ifndef DATA_AGGREGATOR_H
#define DATA_AGGREGATOR_H

#include "csv_parser.h"
#include <vector>

std::vector<Row> aggregateSortedData(std::vector <Row>& data, bool groupByMonth, bool groupByYear);

#endif //DATA_AGGREGATOR_H
