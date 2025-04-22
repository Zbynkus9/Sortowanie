#pragma once
#include <cmath>

using namespace std;

template<typename T>
void swapper(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// Sortowanie przez wstawianie dla ma³ych podtablic
template<typename T>
void insertionSort(T* arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        T key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Funkcja pomocnicza do budowania kopca
template<typename T>
void heapify(T* arr, int n, int i, int offset) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[offset + left] > arr[offset + largest])
        largest = left;

    if (right < n && arr[offset + right] > arr[offset + largest])
        largest = right;

    if (largest != i) {
        swapper(arr[offset + i], arr[offset + largest]);
        heapify(arr, n, largest, offset);
    }
}

template<typename T>
void heapsort(T* arr, int begin, int end) {
    int n = end - begin + 1;
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, begin);

    for (int i = n - 1; i > 0; i--) {
        swapper(arr[begin], arr[begin + i]);
        heapify(arr, i, 0, begin);
    }
}

// Funkcja partycjonuj¹ca dla Quicksort
template<typename T>
int partition(T* arr, int low, int high) {
    T pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swapper(arr[i], arr[j]);
        }
    }
    swapper(arr[i + 1], arr[high]);
    return (i + 1);
}

// Rekurencyjna funkcja Introsort
template<typename T>
void introsortUtil(T* arr, int begin, int end, int depthLimit) {
    int size = end - begin + 1;

    if (size <= 16) {
        insertionSort(arr, begin, end);
        return;
    }

    if (depthLimit == 0) {
        heapsort(arr, begin, end);
        return;
    }

    int pivot = partition(arr, begin, end);
    introsortUtil(arr, begin, pivot - 1, depthLimit - 1);
    introsortUtil(arr, pivot + 1, end, depthLimit - 1);
}

template<typename T>
void introsort(T* arr, int n) {
    int depthLimit = 2 * static_cast<int>(log(n));
    introsortUtil(arr, 0, n - 1, depthLimit);
}