#include "Tables.h"

#include <assert.h>
#include <stdio.h>

int
main(int argc, char* argv[])
{
	int data[30] = {162, 164, 160, 168, 165, 180, 167, 173, 175, 179,
	                175, 177, 170, 169, 162, 179, 179, 177, 164, 164,
	                160, 175, 174, 172, 165, 164, 163, 177, 180, 166};

	bubbleSort(30, data, 0);


	struct TabelFrekuensi* tabel;
	tabel = createTabel(30, data, 0.5);

	printf("Data Mentah: {\n ");
	for (int i = 0; i < 30; i++) {
		printf("%d, ", data[i]);
		if (i != 0 && i % 10 == 0)
			printf("\n ");
	}
	printf("\n}\n");

	printData(tabel);

	generateHistogram(tabel);

	destroyTabel(tabel);

	return 0;
}
