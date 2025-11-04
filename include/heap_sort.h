//
// File created by anakin on 10/15/2025.
// Implemented by dennis 11/3/2025
//

#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <vector>
#include "csv_parser.h"

//compare function for the same reasoning as merge_sort.h
using compareFunction = bool(*)(const Row&, const Row&);

void heapSort(std::vector<Row>& data, compareFunction comp);


#endif //HEAP_SORT_H
