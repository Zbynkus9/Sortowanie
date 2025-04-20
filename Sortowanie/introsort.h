#pragma once

template<typename T>
void swap(T& a, T& b);

template<typename T>
void insertionSort(T* arr, int left, int right);

template<typename T>
int* partition(T* arr, int left, int right);

template<typename T>
int* medianOfThree(int* a, int* b, int* c);

template<typename T>
void introsortUtil(T* arr, int left, int right, int depthLimit);

template<typename T>
void introsort(T* arr, int* begin, int* end);

template<typename T>
void heapify(T* arr, int n, int i);

template<typename T>
void heapSort(T* arr, int n);