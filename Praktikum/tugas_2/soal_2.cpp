#include <iostream>

void selection_sort(int arr[], size_t arr_size);
void print_array(int arr[], size_t arr_size);

int
main()
{
	size_t size = 0;

	std::cout << "Masukan Panjang Array: ";
	std::cin >> size;

	if (size <= 0)
		return -1;

	int array[size];

	for (size_t i = 0; i < size; i++) {
		std::cout << "Masukan Data Ke-" << i << ": ";
		std::cin >> array[i];
	}

	std::cout << "SEBELUM: ";
	print_array(array, size);
	std::cout << "\n";

	selection_sort(array, size);

	std::cout << "SESUDAH: ";
	print_array(array, size);
	std::cout << "\n";

	return 0;
}

void
print_array(int arr[], size_t arr_size)
{
	for (size_t i = 0; i < arr_size; i++) std::cout << arr[i] << " ";
}

void
selection_sort(int arr[], size_t arr_size)
{
	// index ke angka yg terkecil
	size_t min_index;

	// iterasikan seluruh array
	for (size_t i = 0; i < arr_size; i++) {
		min_index = i; // mulai dari i
		// array[j] -> selalu angka setelah min_index
		for (size_t j = (i + 1); j < arr_size; j++) {
			// cari angka yg lebih besar dari min_index
			if (arr[j] > arr[min_index]) // decending
				min_index = j;       // simpan index jika ketemu
		}

		// min_index != i jika ketemu angka yg lebih besar
		if (min_index != i) {
			// penukaran array[min_index] <=> array[j]
			int tmp;
			tmp = arr[min_index];
			arr[min_index] = arr[i];
			arr[i] = tmp;
		}
	}
}
