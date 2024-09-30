#include "Tables.h"
#include <stdio.h>
#include <assert.h>


int main(int argc, char *argv[])
{
    int data[30] = {
        30, 30, 35, 38, 39, 40, 40, 42,
        54, 54, 55, 56, 58, 60, 60, 65,
        42, 45, 46, 47, 48, 50, 50,
        66, 67, 68, 68, 70, 75, 80 
    };

    bubbleSort(30, data,0);

    assert(data[0] == 30);

    struct TabelFrekuensi* tabel;
    tabel = createTabel(30, data, 0.5);

    printf("Data Mentah: {\n ");
    for(int i = 0; i < 30; i++) {
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
