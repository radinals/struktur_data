#pragma once

#include "Prompt.h"
#include <string>
#include <vector>

#define _BASESIZE 10

typedef struct DataTmptTglLahir {
        std::string tempat_lahir;
        int hari;
        int bulan;
        int tahun;
} DataTmptTglLahir;

typedef struct DataAlamat {
        std::string alamat_asli;
        int rt;
        int rw;
        std::string kelurahan_desa;
        std::string kecamatan;
} DataAlamat;

typedef struct DataKtp {
        long int nik;
        std::string nama;
        DataTmptTglLahir tempat_tgl_lahir;
        std::string kelamin;
        DataAlamat alamat;
        std::string agama;
        bool sudah_kawin;
        std::string pekerjaan;
        std::string kewarganegaraan;
} DataKtp;

extern DataKtp* Database;
extern size_t DatabaseSize;
extern size_t DatabaseLen;

void add_new(const DataKtp& dataktp);
void input_new_data();
void input_data(DataKtp& data_ktp);

void delete_at(size_t index);
DataKtp* data_at(size_t index);

void init_database();
void grow_database();
void shrink_database(size_t mod);
void set_database_size(size_t size);

void print_all_data();
void print_data_at(size_t index);
void print_data_at_indexes(const std::vector<size_t>& indexes);
void edit_data_at(MemberName member, size_t index);
void check_database_size();
