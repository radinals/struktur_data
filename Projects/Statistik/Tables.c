/*
 * Tables.c
 * Stores, Retrieve and renders a table
 */

#include "Tables.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct KelasData {
	int no;
	int frek_abs;
	double mid;
	int selang_min, selang_max;
	double batas_min, batas_max;
} KelasData;

typedef struct TabelFrekuensi {
	KelasData** data_tabel;
	int size;
	int total_data;
	double median;
	double mean;
	double varians;
	double simpangan_baku;
	double rentang;
} TabelFrekuensi;

static void swap_array_item(int, int, int[]);
static int linearFind(int, int, const int[]);
static double truncateDecimal(double);

TabelFrekuensi*
createTabel(int len_data_mentah, const int data_mentah[], float presisi)
{

	int rank;
	int dmin;
	int dmax;
	int jmlh_kelas;
	int lebar_kelas;

	TabelFrekuensi* tabel;
	tabel = NULL;

	dmin = data_mentah[0];
	dmax = data_mentah[len_data_mentah - 1];
	rank = getRank(dmin, dmax);

	jmlh_kelas = getJumlahKelas(len_data_mentah);
	lebar_kelas = getLebarKelas(rank, jmlh_kelas);

	tabel = (TabelFrekuensi*)malloc(sizeof(TabelFrekuensi));
	tabel->data_tabel = (KelasData**)calloc(jmlh_kelas, sizeof(KelasData*));
	tabel->size = jmlh_kelas;
	tabel->total_data = len_data_mentah;

	{
		int smin = dmin;
		int smax = (smin + lebar_kelas) - 1;

		for (int i = 0; i < jmlh_kelas; i++) {
			KelasData* kelas;

			int freq = countFrek(smin, smax, lebar_kelas,
			                     len_data_mentah, data_mentah);

			kelas = createKelas(i + 1, freq, smin, smax,
			                    (float)smin - presisi,
			                    (float)smax + presisi);

			tabel->data_tabel[i] = kelas;

			smin += lebar_kelas;
			smax = (smin + lebar_kelas) - 1;
		}
	}

	tabel->mean = getMean(tabel);
	tabel->simpangan_baku = getSimpanganBaku(tabel);
	tabel->varians = getVarians(tabel->simpangan_baku);
	tabel->rentang = data_mentah[len_data_mentah - 1] - data_mentah[0];
	tabel->median = getMedian(tabel);

	return tabel;
}

KelasData*
createKelas(int n, int frek_abs, int selang_min, int selang_max,
            double batas_min, double batas_max)
{
	KelasData* new_kelas;

	new_kelas = (KelasData*)malloc(sizeof(KelasData));

	new_kelas->no = n;
	new_kelas->frek_abs = frek_abs;
	new_kelas->selang_min = selang_min;
	new_kelas->selang_max = selang_max;
	new_kelas->batas_min = batas_min;
	new_kelas->batas_max = batas_max;
	new_kelas->mid = ((selang_max - selang_min) * 0.5) + (float)selang_min;

	return new_kelas;
}

double
getSimpanganBaku(const TabelFrekuensi* tabel)
{
	double simpangan_baku;
	double total;

	total = 0;
	for (int i = 0; i < tabel->size; i++) {
		const KelasData* kelas = tabel->data_tabel[i];
		total += kelas->frek_abs * (pow((kelas->mid - tabel->mean), 2));
	}

	simpangan_baku = sqrt((total / (tabel->total_data - 1)));

	return simpangan_baku;
}

double
getVarians(double simpangan_baku)
{
	return pow(simpangan_baku, 2);
}

double
getRentangXY(const TabelFrekuensi* tabel, int X, int Y)
{
	const double batas_min = tabel->data_tabel[X]->selang_min;
	const double batas_max = tabel->data_tabel[Y]->selang_max;
	printf("%f - %f\n", batas_max, batas_min);
	return batas_max - batas_min;
}

double
getRentang(const TabelFrekuensi* tabel)
{
	return getRentangXY(tabel, 0, tabel->size - 1);
}

double
getLetakMedian(const TabelFrekuensi* tabel)
{
	int N = tabel->total_data;
	double Nd = tabel->total_data;

	/* jika genap */
	if (N % 2 == 0 && N != 1) {
		return ((Nd / 2) + (Nd / 2) + 1) / 2;
	} else {
		return (Nd + 1) / 2;
	}
}

double
getMedian(const struct TabelFrekuensi* tabel)
{
	double letak_median;
	double L;
	int f;
	int F;
	int C;
	int n;

	letak_median = getLetakMedian(tabel);
	n = tabel->total_data;

	printf("LETAK MEDIAN: %f\n", letak_median);

	{
		L = -1;
		f = -1;
		F = -1;
		C = -1;

		int t = 0;
		for (int i = 0; i < tabel->size; i++) {
			const KelasData* kelas = tabel->data_tabel[i];
			t += kelas->frek_abs;
			if (t > letak_median && letak_median < t) {
				printf("MEDIAN DI KELAS %d\n", i);
				C = (kelas->selang_max - kelas->selang_min) + 1;
				f = kelas->frek_abs;
				printf("f: %d\n", f);
				F = t - f;
				printf("F: %d\n", F);
				L = kelas->batas_min;
				printf("L: %f\n", L);
				break;
			}
		}

		if (L < 0 || F < 0 || f < 0 || C < 0) {
			exit(EXIT_FAILURE);
		}
	}

	return L + ((double)C * truncateDecimal((((double)n * 0.5) - F) / f));
}

int
getMinSelangKelas(const KelasData* kelas)
{
	if (kelas) {
		return kelas->selang_min;
	}

	return -1;
}

int
getMaxSelangKelas(const KelasData* kelas)
{

	if (kelas) {
		return kelas->selang_max;
	}
	return -1;
}

double
getMinBatasKelas(const KelasData* kelas)
{
	if (kelas) {
		return kelas->selang_min;
	}
	return -1;
}

double
getMaxBatasKelas(const KelasData* kelas)
{

	if (kelas) {
		return kelas->selang_max;
	}
	return -1;
}

int
getAbsFrekuensiKelas(const KelasData* kelas)
{
	if (kelas) {
		return kelas->frek_abs;
	}
	return -1;
}

double
getPercFrekuensiKelas(const KelasData* kelas, const TabelFrekuensi* tabel)
{

	int total_frek;
	int frek_abs;

	total_frek = getTotalFrek(tabel);
	frek_abs = getAbsFrekuensiKelas(kelas);

	return ((double)frek_abs / (double)total_frek) / 0.01;
}

int
getTotalFrek(const TabelFrekuensi* tabel)
{

	if (tabel) {
		int total;

		total = 0;

		for (int i = 0; i < tabel->size; i++) {
			total += getAbsFrekuensiKelas(&*tabel->data_tabel[i]);
		}

		return total;
	}

	return 0;
}
KelasData*
getNKelas(TabelFrekuensi* tabel, int n)
{

	if (tabel && n < tabel->size) {
		return &*tabel->data_tabel[n];
	}

	return NULL;
}

void
printData(const TabelFrekuensi* tabel)
{
	printf("+--------------------------+\n");
	printf("|TABEL DISTRIBUSI FREKUENSI|\n");
	printf(
	    "+----+--------+--------+--------+--------+--------+----------+----------+\n");
	printf(
	    "| NO |   LL   |   UU   |   LCB  |   UCB  |   MID  | FREQ_ABS | FREQ_PRC |\n");
	printf(
	    "+----+--------+--------+--------+--------+--------+----------+----------+\n");
	for (int i = 0; i < tabel->size; i++) {
		KelasData* kelas;
		kelas = tabel->data_tabel[i];

		printf("|%4.3d|%8.d|%8.d|%8.2F|%8.2F|%8.2F|%10.d|%10.2f|\n",
		       kelas->no, kelas->selang_min, kelas->selang_max,
		       kelas->batas_min, kelas->batas_max, kelas->mid,
		       kelas->frek_abs, getPercFrekuensiKelas(kelas, tabel));
	}
	printf(
	    "+-------------------------------------------------+----------+----------+\n");
	printf(
	    "|                                                 | T:%3d    |          |\n",
	    getTotalFrek(tabel));
	printf(
	    "+-------------------------------------------------+----------+----------+\n");
	printf("Median: %f\n", tabel->median);
	printf("Mean: %f\n", tabel->mean);
	printf("Simpangan Baku: %f\n", tabel->simpangan_baku);
	printf("Varians: %f\n", tabel->varians);
	printf("Rentang: %f\n", tabel->rentang);
}

int
countFrek(int min, int max, int lebar_kelas, int array_size, const int array[])
{
	int count;
	int index;

	count = 0;
	index = linearFind(min, array_size, array);
	while (index < 0) {
		min++;
		index = linearFind(min, array_size, array);
	}

	if (index < 0) {
		return -1;
	}

	while (index < array_size && array[index] <= max) {
		count++;
		index++;
	}

	return count;
}

void
bubbleSort(int array_size, int array[], int decending)
{
	// shift the biggest number increasingly to the right
	for (int n = 0; n < array_size; n++) {
		// element at array_size-n is always the biggest,
		// array_size- n - 1 to optimize
		for (int i = 0; i < array_size - n - 1; i++) {
			// the current one is bigger than the one in the right
			// swap the current to the right
			if (decending) {
				if (array[i] < array[i + 1]) {
					swap_array_item(i, i + 1, array);
				}
			} else {
				if (array[i] > array[i + 1]) {
					swap_array_item(i, i + 1, array);
				}
			}
		}
	}
}

int
getRank(int min, int max)
{
	return max - min;
}

int
getJumlahKelas(int jmlh_data)
{
	return ceil(1 + (3.3 * (log10(jmlh_data))));
}

int
getLebarKelas(int rank, int jmlh_kelas)
{
	return ceil((double)rank / jmlh_kelas);
}

double
getMean(const struct TabelFrekuensi* tabel)
{
	double total;

	total = 0;

	for (int i = 0; i < tabel->size; i++) {
		KelasData* kelas = tabel->data_tabel[i];
		total += (kelas->frek_abs * kelas->mid);
	}

	return (total / tabel->total_data);
}

static void
swap_array_item(int from, int to, int array[])
{
	int tmp = array[to];
	array[to] = array[from];
	array[from] = tmp;
}

static int
linearFind(int n, int size, const int array[])
{
	for (int i = 0; i < size; i++) {
		if (array[i] == n) {
			return i;
		}
	}

	return -1;
}

int*
generateAbsFrekArray(const TabelFrekuensi* tabel)
{
	int* array = (int*)malloc(sizeof(int) * tabel->size);

	for (int i = 0; i < tabel->size; i++) {
		array[i] = tabel->data_tabel[i]->frek_abs;
	}

	return array;
}

void
generateHistogram(const TabelFrekuensi* tabel)
{

	int* frek_array = generateAbsFrekArray(tabel);

	printf("|---------|\n");
	printf("|HISTOGRAM|\n");
	printf("|---------|\n");

	for (int i = 0; i < tabel->size; i++) {
		KelasData* kelas;
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

void
destroyTabel(TabelFrekuensi* tabel)
{
	for (int i = 0; i < tabel->size; i++) {
		free(tabel->data_tabel[i]);
	}
	free(tabel->data_tabel);
	free(tabel);
}

double
truncateDecimal(double n)
{
	int integer_part = (int)n;

	// Step 2: Get the two digits after the decimal point
	double fractional_part = n - integer_part; // Extract fractional part
	int two_digits_after_decimal =
	    (int)(fractional_part * 100); // Get two digits after decimal

	// Step 3: Combine them into a decimal form with two digits after
	// decimal
	return integer_part + (two_digits_after_decimal / 100.0);
}
