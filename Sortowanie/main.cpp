#include <iostream>
#include <chrono>
#include <fstream>


#include "quicksort.h"
#include "mergesort.h"
#include "introsort.h"
#include "datasetmake.h"

using namespace std;

int main() {
	// Ustawienie ziarna generatora liczb losowych
	srand(time(NULL));

	// Rozmiary tablic do posortowania
	const int tabSizes[] = { 100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000 };

	const int tabSizesAmount = sizeof(tabSizes) / sizeof(tabSizes[0]); // Obliczenie liczby rozmiarów tablic

	int tabSize = tabSizes[0]; // Ustawienie domyœlnego rozmiaru tablicy

	// Liczba iteracji dla ka¿dego rozmiaru
	const int iterations = 1;

	// Procent posortowania dla tablic czêœciowo posortowanych
	const double percentages[] = { 0.25, 0.5, 0.75, 0.95, 0.99, 0.997 };

	const int percentagesAmout = sizeof(percentages) / sizeof(percentages[0]); // Obliczenie liczby procentów

	double percent = percentages[0]; // Ustawienie domyœlnego procentu dla tablic czêœciowo posortowanych

	// Typy tablic do testowania
	const string arrayTypes[] = {
		"random",
		"reversed",
		"partially_sorted"
	};

	const int arrayTypesAmount = sizeof(arrayTypes) / sizeof(arrayTypes[0]); // Obliczenie liczby typów tablic

	string arrayType = arrayTypes[0]; // Ustawienie domyœlnego typu tablicy

	// Pliki do zapisu wyników
	const string sortingResultsFiles[] = {
		"mergesort_results.csv",
		"quicksort_results.csv",
		"introsort_results.csv"
	};

	const int sortingResultsFilesAmount = sizeof(sortingResultsFiles) / sizeof(sortingResultsFiles[0]); // Obliczenie liczby plików

	long long sortTimes[tabSizesAmount + arrayTypesAmount + percentagesAmout - 1][iterations];
	// cykl dla rozmiarów [random, reversed, partialy_sorted_1, ... partialy_sorted_n] | [iteracje]

	ofstream file;

	for (int i = 0; i < sortingResultsFilesAmount; i++) {

		file.open(sortingResultsFiles[i], ios::app);

		if (!file.is_open()) {
			cerr << "Nie mo¿na otworzyæ pliku: " << sortingResultsFiles[i] << endl;
			return 1;
		}

		for (int j = 0; j < tabSizesAmount; j++) {
			file << "Iteracja,Rozmiar tablicy : " << tabSizes[j];
			file << ",Random time,Reversed time";
			for (int k = 0; k < percentagesAmout; k++) {
				file << ",Partially sorted time of % pre-sorted ( " << percentages[k] << " )";
			}
			file << ",";
		}
		file << endl;

		switch (i) {
		case 0: // Mergesort

			for (int j = 0; j < tabSizesAmount; j++) {
				tabSize = tabSizes[j];
				int* arr = new int[tabSize];

				for (int k = 0; k < arrayTypesAmount; k++) {
					switch (k) {
					case 0: // Random
						arrayType = arrayTypes[k];
						for (int l = 0; l < iterations; l++) {
							generateRandomArray(arr, tabSize);
							auto start = chrono::high_resolution_clock::now();
							mergeSort(arr, 0, tabSize - 1);
							auto end = chrono::high_resolution_clock::now();
							sortTimes[(j * (arrayTypesAmount + percentagesAmout - 1)) + k][l] = chrono::duration_cast<chrono::microseconds>(end - start).count();
						}
						break;

					case 1: // Reversed
						arrayType = arrayTypes[k];
						for (int l = 0; l < iterations; l++) {
							generateReverseSortedArray(arr, tabSize);
							auto start = chrono::high_resolution_clock::now();
							mergeSort(arr, 0, tabSize - 1);
							auto end = chrono::high_resolution_clock::now();
							sortTimes[(j * (arrayTypesAmount + percentagesAmout - 1)) + k][l] = chrono::duration_cast<chrono::microseconds>(end - start).count();
						}
						break;

					case 2: // Partially sorted
						arrayType = arrayTypes[k];
						for (int l = 0; l < percentagesAmout; l++) {
							percent = percentages[l];
							for (int m = 0; m < iterations; m++) {
								generatePartialySortedArray(arr, tabSize, percent);
								auto start = chrono::high_resolution_clock::now();
								mergeSort(arr, 0, tabSize - 1);
								auto end = chrono::high_resolution_clock::now();
								sortTimes[(j * (arrayTypesAmount + percentagesAmout - 1)) + k + l][m] = chrono::duration_cast<chrono::microseconds>(end - start).count();
							}
						}
						break;

					default:
						break;

					}
				}

				delete[] arr; // Zwolnienie pamiêci po tablicy

			}

			break;

		case 1: // Quicksort

			for (int j = 0; j < tabSizesAmount; j++) {
				tabSize = tabSizes[j];
				int* arr = new int[tabSize];

				for (int k = 0; k < arrayTypesAmount; k++) {
					switch (k) {
					case 0: // Random
						arrayType = arrayTypes[k];
						for (int l = 0; l < iterations; l++) {
							generateRandomArray(arr, tabSize);
							auto start = chrono::high_resolution_clock::now();
							quickSort(arr, 0, tabSize - 1);
							auto end = chrono::high_resolution_clock::now();
							sortTimes[(j * (arrayTypesAmount + percentagesAmout - 1)) + k][l] = chrono::duration_cast<chrono::microseconds>(end - start).count();
						}
						break;

					case 1: // Reversed
						arrayType = arrayTypes[k];
						for (int l = 0; l < iterations; l++) {
							generateReverseSortedArray(arr, tabSize);
							auto start = chrono::high_resolution_clock::now();
							quickSort(arr, 0, tabSize - 1);
							auto end = chrono::high_resolution_clock::now();
							sortTimes[(j * (arrayTypesAmount + percentagesAmout - 1)) + k][l] = chrono::duration_cast<chrono::microseconds>(end - start).count();
						}
						break;

					case 2: // Partially sorted
						arrayType = arrayTypes[k];
						for (int l = 0; l < percentagesAmout; l++) {
							percent = percentages[l];
							for (int m = 0; m < iterations; m++) {
								generatePartialySortedArray(arr, tabSize, percent);
								auto start = chrono::high_resolution_clock::now();
								quickSort(arr, 0, tabSize - 1);
								auto end = chrono::high_resolution_clock::now();
								sortTimes[(j * (arrayTypesAmount + percentagesAmout - 1)) + k + l][m] = chrono::duration_cast<chrono::microseconds>(end - start).count();
							}
						}
						break;

					default:
						break;

					}
				}

				delete[] arr; // Zwolnienie pamiêci po tablicy

			}

			break;

		case 2: // Introsort

			for (int j = 0; j < tabSizesAmount; j++) {
				tabSize = tabSizes[j];
				int* arr = new int[tabSize];

				for (int k = 0; k < arrayTypesAmount; k++) {
					switch (k) {
					case 0: // Random
						arrayType = arrayTypes[k];
						for (int l = 0; l < iterations; l++) {
							generateRandomArray(arr, tabSize);
							auto start = chrono::high_resolution_clock::now();
							introsort(arr, 0, tabSize - 1);
							auto end = chrono::high_resolution_clock::now();
							sortTimes[(j * (arrayTypesAmount + percentagesAmout - 1)) + k][l] = chrono::duration_cast<chrono::microseconds>(end - start).count();
						}
						break;

					case 1: // Reversed
						arrayType = arrayTypes[k];
						for (int l = 0; l < iterations; l++) {
							generateReverseSortedArray(arr, tabSize);
							auto start = chrono::high_resolution_clock::now();
							introsort(arr, 0, tabSize - 1);
							auto end = chrono::high_resolution_clock::now();
							sortTimes[(j * (arrayTypesAmount + percentagesAmout - 1)) + k][l] = chrono::duration_cast<chrono::microseconds>(end - start).count();
						}
						break;

					case 2: // Partially sorted
						arrayType = arrayTypes[k];
						for (int l = 0; l < percentagesAmout; l++) {
							percent = percentages[l];
							for (int m = 0; m < iterations; m++) {
								generatePartialySortedArray(arr, tabSize, percent);
								auto start = chrono::high_resolution_clock::now();
								introsort(arr, 0, tabSize - 1);
								auto end = chrono::high_resolution_clock::now();
								sortTimes[(j * (arrayTypesAmount + percentagesAmout - 1)) + k + l][m] = chrono::duration_cast<chrono::microseconds>(end - start).count();
							}
						}
						break;

					default:
						break;

					}
				}

				delete[] arr; // Zwolnienie pamiêci po tablicy

			}

			break;

		default:
			break;

		}

		for (int j = 0; j < iterations; j++) {
			for (int k = 0; k < tabSizesAmount; k++) {
				file << j + 1 << "," << tabSizes[k] << "," << sortTimes[(k * (arrayTypesAmount + percentagesAmout - 1))][j] << "," << sortTimes[(k * (arrayTypesAmount + percentagesAmout - 1)) + 1][j];
				for (int l = 0; l < percentagesAmout; l++) {
					file << "," << sortTimes[(k * (arrayTypesAmount + percentagesAmout - 1)) + 2 + l][j];
				}
				file << endl;
			}

		}

		file.close();

	}

	return 0;
}