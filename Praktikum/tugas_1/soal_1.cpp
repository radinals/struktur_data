#include <iostream>

int main()
{
	int angka[] = {0, 1, 2, 3, 4, 5, 6};
	for(int i = 0; i < (sizeof(angka) / sizeof(angka[0])); i++) {
		int* angka_ptr = &angka[i];
		std::cout << "angka[" << i << "] ("
			<< angka_ptr << ") : " <<  *angka_ptr << "\n";
	}
	return 0;
}
