#include <iostream>

int main()
{
	int data = 100;
	int* ptr_1 = &data;
	int* ptr_2 = ptr_1;
	int** ptr_ke_ptr_1 = &ptr_1;

	std::cout << "data= "   << data << "\n";
	std::cout << "&data = " << &data << "\n";
	std::cout << "\n";
	std::cout << "ptr_1 = "  << ptr_1 << "\n";
	std::cout << "*ptr_1 = " << *ptr_1 << "\n";
	std::cout << "\n";
	std::cout << "ptr_2 = "  << ptr_2 << "\n";
	std::cout << "*ptr_2 = " << *ptr_2 << "\n";
	std::cout << "\n";
	std::cout << "ptr_ke_ptr_1 = "   << ptr_ke_ptr_1 << "\n";
	std::cout << "*ptr_ke_ptr_1 = "  << *ptr_ke_ptr_1<< "\n";
	std::cout << "**ptr_ke_ptr_1 = " << **ptr_ke_ptr_1<< "\n";

	return 0;
}
