#pragma once

using namespace std;

template<typename T>
void quickSort(T* arr, int left, int right) {

	// Jeœli tablica ma 1 element, jest ju¿ posortowana
	if (left >= right) return;

	int i = left - 1, j = right + 1;

	T pivot = arr[(left + right) / 2]; // Wybieramy ostatni element jako pivot

	while (1) {

		// Przesuwamy wskaŸnik left w prawo, a¿ znajdziemy element wiêkszy lub równy pivot
		while (arr[++i] < pivot);

		// Przesuwamy wskaŸnik right w lewo, a¿ znajdziemy element mniejszy lub równy pivot
		while (arr[--j] > pivot);

		// Zamiana elementów
		if (i <= j) {
			T temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
		// Jeœli wskaŸniki siê skrzy¿owa³y, koñczymy
		else
			break;
	}

	// Rekurencyjne wywo³anie quickSort dla lewej i prawej czêœci
	if (j > left) // Sprawdzamy, czy lewa czêœæ ma wiêcej ni¿ 1 element
		quickSort(arr, left, j);
	if (i < right) // Sprawdzamy, czy prawa czêœæ ma wiêcej ni¿ 1 element
		quickSort(arr, i, right);

}