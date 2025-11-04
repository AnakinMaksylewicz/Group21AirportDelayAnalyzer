//
// Created by anakin on 11/1/2025.
//

#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <vector>
#include "csv_parser.h"
//compare function for the same reasoning as merge_sort.h
using compareFunction = bool(*)(const Row&, const Row&);

void quickSort(std::vector<Row>& data, compareFunction comp);

#endif //QUICK_SORT_H
