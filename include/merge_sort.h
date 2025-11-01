//
// Created by anakin on 10/15/2025.
//

#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <vector>
#include "csv_parser.h"

//declare a general compare function that takes 2 Row objects
//and returns a boolean so that we don't need to redefine a merge
//sort for each metric we will be comparing by
using compareFunction = bool(*)(const Row&, const Row&);

void mergeSort(std::vector<Row>& data, compareFunction comp);

#endif //MERGE_SORT_H
