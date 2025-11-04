//
// Created by anakin on 10/15/2025.
//

#include "merge_sort.h"

void merge(std::vector<Row>& data, int left, int mid, int right, compareFunction comp) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    //Initialize vector for left half and right half, populate with left half values
    //and right half values respectively
    std::vector<Row> L(n1);
    std::vector<Row> R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = data[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = data[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;
    //Compare and insert into data in order
    while (i < n1 && j < n2) {
        if (comp(L[i], R[j])) //If left < right, we insert and increment data and left array by 1
            data[k++] = L[i++];
        else
            data[k++] = R[j++];
    }

    //Copy remaining elements
    while (i < n1)
        data[k++] = L[i++];
    while (j < n2)
        data[k++] = R[j++];
}

void mergeSortHelper(std::vector<Row>& data, int left, int right, compareFunction comp) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(data, left, mid, comp);
        mergeSortHelper(data, mid + 1, right, comp);
        merge(data, left, mid, right, comp);
    }
}

void mergeSort(std::vector<Row>& data, compareFunction comp) {
    if(!data.empty())
        mergeSortHelper(data, 0, static_cast<int>(data.size()) - 1, comp);
}