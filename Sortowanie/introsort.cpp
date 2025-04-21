#include "introsort.h"

template<typename T>
void swap(T* arr, T& a, int b) {
	T temp = *a;
	*a = arr[b];
	arr[b] = temp;
}

template<typename T>
void swap(T* arr, int a, int b) {
	T temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

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

template<typename T>
int* partition(T* arr, int left, int right) {

	int pivot = arr[right];

	int i = left - 1;

	for (int j = left; j < right; j++) {
		if (arr[j] <= pivot) {
			i++;
			swap(arr, arr[i], arr[j]);
		}
	}

	swap(arr, arr[i + 1], arr[right]);

	return (arr + i + 1);

}

template<typename T>
T* medianOfThree(T* a, T* b, T* c) {
	T* median = a;
	if (*b < *a) {
		if (*c < *b) {
			median = b;
		}
		else if (*c < *a) {
			median = c;
		}
	}
	else {
		if (*c > *b) {
			median = b;
		}
		else if (*c > *a) {
			median = c;
		}
	}
	return median;
}

template<typename T>
void introsortUtil(T* arr, int left, int right, int depthLimit) {

	int size = right - left + 1;

	if (size <= 16) {
		insertionSort(arr, left, right);
		return;
	}

	if (depthLimit == 0) {
		heapSort(arr, size, left, right);
		return;
	}

	int* pivot = medianOfThree(arr[left], arr[left + size / 2], arr[right]);

	swap(arr, *pivot, right);

	int* partitionIndex = partition(arr, left, right);

	introsortUtil(arr, left, partitionIndex - 1, depthLimit - 1);

	introsortUtil(arr, partitionIndex + 1, right, depthLimit - 1);

	return;


}

template<typename T>
void introsort(T* arr, int* begin, int* end) {
	
	int depthLimit = 2 * log(end - begin);

	introsortUtil(arr, begin, end, depthLimit);

	return;

}

template<typename T>
void heapify(T* arr, int n, int i) {

	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if (left < n && arr[left] > arr[largest]) {
		largest = left;
	}
	if (right < n && arr[right] > arr[largest]) {
		largest = right;
	}
	if (largest != i) {
		swap(arr, arr[i], arr[largest]);
		heapify(arr, n, largest);
	}

}

template<typename T>
void heapSort(T* arr, int n, int first, int last) {

	for (int i = first + n / 2 - 1; i >= first; i--) {
		heapify(arr, n, i);
	}

	for (int i = n - 1; i > first; i--) {
		swap(arr, arr[first], arr[i]);
		heapify(arr, i, first);
	}

}