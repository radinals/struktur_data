#include <iostream>

int main()
{
	int array[] = {10, 20, 30 , 40, 50};
	int *ptr = NULL;

	for (int i = 0; i < (sizeof(array) / sizeof(array[0])); i++)
	{
		ptr = &array[i];
		std::cout << *ptr << "\n";
	}

	return 0;
}
