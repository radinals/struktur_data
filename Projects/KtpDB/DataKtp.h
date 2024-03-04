#pragma once

#include <string>

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
