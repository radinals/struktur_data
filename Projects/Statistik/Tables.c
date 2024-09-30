/*
 * Tables.c
 * Stores, Retrieve and renders a table
*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "Tables.h"
#include <math.h>
#include <stdio.h>
#include <assert.h>

struct KelasData {
    int no;
    int frek_abs;
    double mid;
    int selang_min, selang_max;
    double batas_min, batas_max;
};

struct TabelFrekuensi {
    struct KelasData** data_tabel;
    int n;
};

static void swap_array_item(int from, int to, int array[]);
static int linearFind(int n, int sz, const int array[] );

struct TabelFrekuensi* createTabel(int len_data_mentah, const int data_mentah[], float presisi) {

    int rank;
    int dmin;
    int dmax;
    int jmlh_kelas;
    int lebar_kelas;

    struct TabelFrekuensi* tabel; tabel = NULL;

    dmin = data_mentah[0];
    dmax = data_mentah[len_data_mentah-1];
    rank = getRank(dmin, dmax);

    jmlh_kelas = getJumlahKelas(len_data_mentah);
    lebar_kelas = getLebarKelas(rank, jmlh_kelas);

    tabel = malloc(sizeof(struct TabelFrekuensi));
    tabel->data_tabel = malloc(sizeof(struct KelasData*) * jmlh_kelas);
    tabel->n = jmlh_kelas;

    {
        int smin = dmin;
        int smax = (smin + lebar_kelas) - 1;

        for(int i = 0; i < jmlh_kelas; i++) {
            struct KelasData* kelas;

            int freq = countFrek(smin,smax, lebar_kelas,len_data_mentah, data_mentah);

            kelas = createKelas(i+1, freq, smin, smax, (float)smin - presisi, (float)smax - presisi);

            tabel->data_tabel[i] = kelas;

            smin += lebar_kelas;
            smax = (smin + lebar_kelas) - 1;
        }
    }

    return tabel;
}


struct KelasData* createKelas(int n, int frek_abs, int selang_min,
                              int selang_max, double batas_min,
                              double batas_max)
{
    struct KelasData* new_kelas;

    new_kelas = malloc(sizeof(struct KelasData));

    new_kelas->no = n;    
    new_kelas->frek_abs = frek_abs;
    new_kelas->selang_min = selang_min;
    new_kelas->selang_max = selang_max;
    new_kelas->batas_min = batas_min;
    new_kelas->batas_max = batas_max;
    new_kelas->mid = ((selang_max - selang_min) * 0.5) + (float)selang_min;

    return new_kelas;
}


int getMinSelangKelas(const struct KelasData* kelas) {
    if (kelas) {
        return kelas->selang_min;
    }

    return -1;
}

int getMaxSelangKelas(const struct KelasData* kelas) {

    if (kelas) {
        return kelas->selang_max;
    }
    return -1;
}

double getMinBatasKelas(const struct KelasData* kelas) {
    if (kelas) {
        return kelas->selang_min;
    }
    return -1;
}

double getMaxBatasKelas(const struct KelasData* kelas) {

    if (kelas) {
        return kelas->selang_max;
    }
    return -1;
}

int getAbsFrekuensiKelas(const struct KelasData* kelas) {
    if (kelas) {
        return kelas->frek_abs;
    }
    return -1;
}

double getPercFrekuensiKelas(const struct KelasData* kelas, const struct TabelFrekuensi* tabel) {

    int total_frek;
    int frek_abs;

    total_frek = getTotalFrek(tabel);
    frek_abs = getAbsFrekuensiKelas(kelas);

    return ((double)frek_abs / (double)total_frek) / 0.01;
}

int getTotalFrek(const struct TabelFrekuensi* tabel) {
    
    if (tabel) {
        int total;

        total = 0;

        for (int i = 0; i < tabel->n; i++) {
            total += getAbsFrekuensiKelas(&*tabel->data_tabel[i]);
        }

        return total;
    }

    return 0;
}
struct KelasData* getNKelas(struct TabelFrekuensi* tabel, int n) {
    
    if (tabel && n < tabel->n) {
        return &*tabel->data_tabel[n];
    }

    return NULL;
}

void printData(const struct TabelFrekuensi * tabel) {
    printf("+--------------------------+\n");
    printf("|TABEL DISTRIBUSI FREKUENSI|\n");
    printf("+----+--------+--------+--------+--------+--------+----------+----------+\n");
    printf("| NO |   LL   |   UU   |   LCB  |   UCB  |   MID  | FREQ_ABS | FREQ_PRC |\n");
    printf("+----+--------+--------+--------+--------+--------+----------+----------+\n");
    for(int i = 0; i < tabel->n; i++) {
        struct KelasData* kelas;
        kelas = tabel->data_tabel[i];

        printf("|%4.3d|%8.d|%8.d|%8.2F|%8.2F|%8.2F|%10.d|%10.2f|\n",
               kelas->no, kelas->selang_min,
               kelas->selang_max, kelas->batas_min,
               kelas->batas_max,kelas->mid,
               kelas->frek_abs,getPercFrekuensiKelas(kelas, tabel));
    }
    printf("+-------------------------------------------------+----------+----------+\n");
    printf("|                                                 | T:%3d    |          |\n",getTotalFrek(tabel));
    printf("+-------------------------------------------------+----------+----------+\n");
}


int countFrek(int min, int max,
              int lebar_kelas, int arr_len,
              const int arr[]) {
    int count; count=0;
    int index;


    index = linearFind(min, arr_len,arr);
    while(index < 0) {
        min++;
        index = linearFind(min, arr_len,arr);
    }


    if (index < 0) {
        return -1;
    }

    while (arr[index] <= max && index < arr_len) {
        count++;
        index++;
    }

    return count;
}


void bubbleSort(int arr_len, int arr[], int decending) {
	// shift the biggest number increasingly to the right
	for (int n = 0; n < arr_len; n++) {
		// element at array_size-n is always the biggest,
		// array_size- n - 1 to optimize
		for (int i = 0; i < arr_len - n - 1; i++) {
			// the current one is bigger than the one in the right
			// swap the current to the right
			if (decending) {
				if (arr[i] < arr[i + 1]) {
					swap_array_item(i, i + 1, arr);
                }
			} else {
				if (arr[i] > arr[i + 1]) {
					swap_array_item(i, i + 1, arr);
                }
			}
		}
	}
}

int getRank(int min, int max) {
    return max - min;
}

int getJumlahKelas(int jmlh_data) {
    return ceil(1 + (3.3 * (log10(jmlh_data))));
}

int getLebarKelas(int rank, int jmlh_kelas) {
    return ceil((double)rank / jmlh_kelas);
}

static void
swap_array_item(int from, int to, int array[])
{
	int tmp = array[to];
	array[to] = array[from];
	array[from] = tmp;
}

static int linearFind(int n, int sz, const int array[] ) {
    for(int i = 0; i < sz; i++ ) {
        if (array[i] == n) {
            return i;
        }
    }

    return -1;
}

int* generateAbsFrekArray(const struct TabelFrekuensi*tabel) {
    int* array = malloc(sizeof(int) * tabel->n );

    for (int i = 0 ; i < tabel->n; i++) {
        array[i] = tabel->data_tabel[i]->frek_abs;
    }

    return array;
}

void generateHistogram(const struct TabelFrekuensi* tabel) {

    int* frek_array = generateAbsFrekArray(tabel);

    printf("|---------|\n");
    printf("|HISTOGRAM|\n");
    printf("|---------|\n");

    for (int i = 0;  i < tabel->n; i++) {
        struct KelasData* kelas;
        kelas = tabel->data_tabel[i];
        printf("| %d - %d | ", kelas->selang_min, kelas->selang_max);
        for (int j = 0; j < frek_array[i]; j++) {
            printf(">");
        }
        printf(" (%d)\n", frek_array[i]);
    }

    printf("|---------|\n");

    free(frek_array);
}

void destroyTabel(struct TabelFrekuensi* tabel) {
    free(tabel->data_tabel);
    free(tabel);
}
