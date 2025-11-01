//
// Created by anakin on 11/1/2025.
//
#include "quick_sort.h"
#include <utility> //for swap function

int partition(std::vector<Row>& data, int low, int high, compareFunction comp) {
    Row pivot = data[low]; //choose first element as pivot
    int left = low + 1;
    int right = high;
    //Loop until right passes left
    while (left <= right) {
        //Increment left until we find an element greater than the pivot
        while (left <= right && comp(data[left], pivot)) {
            left++;
        }
        //Increment left until we find an element less than the pivot
        while (left <= right && comp(pivot, data[right])) {
            right--;
        }

        if (left < right) {
            std::swap(data[left], data[right]);
            left++;
            right--;
        }
    }
    //Swap pivot with right and return data[right] for next pivot
    std::swap(data[low], data[right]);
    return right;
}

void quickSortHelper(std::vector<Row>& data, int low, int high, compareFunction comp) {
    if (low < high) {
        int pivotIndex = partition(data, low, high, comp);
        quickSortHelper(data, low, pivotIndex - 1, comp);
        quickSortHelper(data, pivotIndex + 1, high, comp);
    }
}

void quickSort(std::vector<Row>& data, compareFunction comp) {
    if (!data.empty())
        quickSortHelper(data, 0, static_cast<int>(data.size()) - 1, comp);
}