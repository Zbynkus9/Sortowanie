#pragma once

using namespace std;

template<typename T>
void merge(T* arr, int left, int mid, int right) {

	int n1 = mid - left + 1;
	int n2 = right - mid;

	// Tymczasowe tablice pomocnicze
	// tablica L[left...mid]
	T* L = new T[n1];
	// tablica R[mid+1...right]
	T* R = new T[n2];

	// Kopiowanie danych do tymczasowych tablic L[] i R[]
	for (int i = 0; i < n1; i++)
		L[i] = arr[left + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[mid + 1 + j];

	int i = 0, j = 0, k = left;

	// £¹czenie tymczasowych tablic z powrotem do arr[left..right]
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	// Kopiowanie pozosta³ych elementów L[], jeœli jakieœ pozosta³y
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	// Kopiowanie pozosta³ych elementów R[], jeœli jakieœ pozosta³y
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}

	// Zwolnienie pamiêci tymczasowych tablic
	delete[] L;
	delete[] R;
}

template<typename T>
void mergeSort(T* arr, int left, int right) {

	// Jesli tablica ma 1 element, jest ju¿ posortowana
	if (left >= right) return;

	int mid = left + (right - left) / 2;

	// Sortowanie pierwszej i drugiej po³owy
	mergeSort(arr, left, mid);
	mergeSort(arr, mid + 1, right);

	// £¹czenie posortowanych po³ówek
	merge(arr, left, mid, right);
}