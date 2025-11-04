//
// File created by anakin on 10/15/2025.
// Implemented by dennis 11/3/2025
//

#include "heap_sort.h"
using namespace std;

void heapify(vector<Row>& data, int n, int i, compareFunction comp) {
    // largest initialized as root
    int largest = i;
    // left and right indexes
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // left child greater than root
    if (left < n && comp(data[largest], data[left])) {
        largest = left;
    }
    // right child greater than largest so far
    if (right < n && comp(data[largest], data[right])) {
        largest = right;
    }
    // largest is not root
    if (largest != i) {
        swap(data[largest], data[i]);
        //heapify rest of subtree
        heapify(data, n, largest, comp);
    }
}

void heapSort(std::vector<Row>& data, compareFunction comp) {
    int n = data.size();

    // build heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(data, n, i, comp);
    }
    // one by one element swaps
    for (int i = n - 1; i >= 0; i--) {
        // root -> end
        swap(data[0], data[i]);

        heapify(data, i, 0, comp);
    }
}

