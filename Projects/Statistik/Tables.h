/*
 * Tables.h
 * Stores, Retrieve and renders a table
 */

struct KelasData;
struct TabelFrekuensi;

struct KelasData* createKelas(int, int, int, int, double, double);
struct TabelFrekuensi* createTabel(int, const int[], float);
void destroyTabel(struct TabelFrekuensi*);

struct KelasData* getNKelas(struct TabelFrekuensi*, int);

int getMinSelangKelas(const struct KelasData*);
int getMaxSelangKelas(const struct KelasData*);

double getMinBatasKelas(const struct KelasData*);
double getMaxBatasKelas(const struct KelasData*);

int getMaxAbsFrek(const struct TabelFrekuensi*);
int getMin(const struct TabelFrekuensi*);

int* generateAbsFrekArray(const struct TabelFrekuensi*);

int getTotalFrek(const struct TabelFrekuensi*);

void printData(const struct TabelFrekuensi*);

int countFrek(int, int, int, int, const int[]);
void bubbleSort(int, int[], int);

int getRank(int, int);
int getJumlahKelas(int);
int getLebarKelas(int, int);

double getMean(const struct TabelFrekuensi*);
double getVarians(double simpangan_baku);
double getSimpanganBaku(const struct TabelFrekuensi*);
double getRentang(const struct TabelFrekuensi*);
double getRentangXY(const struct TabelFrekuensi*, int, int);
double getMedian(const struct TabelFrekuensi*);
double getLetakMedian(const struct TabelFrekuensi*);

void generateHistogram(const struct TabelFrekuensi*);
