#pragma once

using namespace std;

template<typename T>
void quickSort(T* arr, int left, int right) {

	// Je�li tablica ma 1 element, jest ju� posortowana
	if (left >= right) return;

	int i = left - 1, j = right + 1;

	T pivot = arr[(left + right) / 2]; // Wybieramy ostatni element jako pivot

	while (1) {

		// Przesuwamy wska�nik left w prawo, a� znajdziemy element wi�kszy lub r�wny pivot
		while (arr[++i] < pivot);

		// Przesuwamy wska�nik right w lewo, a� znajdziemy element mniejszy lub r�wny pivot
		while (arr[--j] > pivot);

		// Zamiana element�w
		if (i <= j) {
			T temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
		// Je�li wska�niki si� skrzy�owa�y, ko�czymy
		else
			break;
	}

	// Rekurencyjne wywo�anie quickSort dla lewej i prawej cz�ci
	if (j > left) // Sprawdzamy, czy lewa cz�� ma wi�cej ni� 1 element
		quickSort(arr, left, j);
	if (i < right) // Sprawdzamy, czy prawa cz�� ma wi�cej ni� 1 element
		quickSort(arr, i, right);

}