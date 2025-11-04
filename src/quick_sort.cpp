//
// Created by anakin on 11/1/2025.
//
#include "quick_sort.h"
#include <utility> //for swap function

/* We're using 3-way partition quick sort, since there were so many equal entries
 * in the data vector that regular quick sort was taking so long that it didn't
 * output anything
 */
void quickSortHelper(std::vector<Row>& data, int low, int high, compareFunction comp) {
    //If subarray has 0 or 1 elements, array is sorted
    if (low >= high) return;

    Row pivot = data[low]; // choose first element as pivot

    /* we will divide the array into three sections, where data[low ... lt-1]
     * will be elements less than the pivot, data[lt...gt] will be elements
     * equal to the pivot, and data[gt+1 ... high] will be elements greater
     * than the pivot */

    int lt = low; //Boundary for < pivot region
    int i  = low + 1; //Current element
    int gt = high; //Boundary for > pivot region

    while (i <= gt) {
        if (comp(data[i], pivot)) { //If element < pivot, move it to the less than pivot region
            std::swap(data[lt], data[i]);
            lt++;
            i++;
        }
        else if (comp(pivot, data[i])) { //If the element is > pivot, move it to the greater than pivot region
            std::swap(data[i], data[gt]);
            gt--;
        }
        else {
            // equal to pivot
            i++;
        }
    }

    //Sort remaining less than and greater than pivot regions
    quickSortHelper(data, low, lt - 1, comp);
    quickSortHelper(data, gt + 1, high, comp);
}

void quickSort(std::vector<Row>& data, compareFunction comp) {
    if (!data.empty())
        quickSortHelper(data, 0, static_cast<int>(data.size()) - 1, comp);
}