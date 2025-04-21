#include <cstdlib>
#include "datasetmake.h"

template<typename T>
void generateReverseSortedArray(T* arr, int size) {
	for (int i = 0; i < size; i++) {
		arr[i] = size - i;
	}
}

template<typename T>
void generatePartialySortedArray(T* arr, int size, double percent) {
	int sortedSize = static_cast<int>(size * percent);
	for (int i = 0; i < sortedSize; i++) {
		arr[i] = i + 1;
	}
	for (int i = sortedSize; i < size; i++) {
		arr[i] = (sortedSize + 1 + (rand() % (size - sortedSize + 1)));
	}
}

template<typename T>
void generateRandomArray(T* arr, int size) {
	for (int i = 0; i < size; i++) {
		arr[i] = rand() % size + 1;
	}
}