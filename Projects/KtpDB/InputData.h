#pragma once

#include "DataKtp.h"

#include <string>

void get_input(std::string& str, const std::string& prompt);
void get_input(int& inum, const std::string& prompt);
void get_input(long int& lnum, const std::string& prompt);
bool yesno_prompt(const std::string& prompt, const char& true_char = 'y',
                  const char& false_char = 't');
void input_data(DataKtp& data_ktp);

inline void
input_rt(int& rt)
{
	get_input(rt, "- Masukan Nomor RT Anda: ");
}
inline void
input_rw(int& rw)
{
	get_input(rw, "- Masukan Nomor RW Anda: ");
}
inline void
input_nik(long int& nik)
{
	get_input(nik, "- Masukan Nomor NIK Anda: ");
}
inline void
input_nama(std::string& nama)
{
	get_input(nama, "- Masukan Nama Anda: ");
}
inline void
input_agama(std::string& agama)
{
	get_input(agama, "- Masukan Agama Anda: ");
}
inline void
input_alamat(std::string& alamat)
{
	get_input(alamat, "- Masukan Alamat Anda: ");
}
inline void
input_bulan_lahir(int& bulan)
{
	get_input(bulan, "- Masukan Bulan Kelahiran Anda: ");
}
inline void
input_tahun_lahir(int& tahun)
{
	get_input(tahun, "- Masukan Tahun Kelahiran Anda: ");
}
inline void
input_tanggal_lahir(int& tanggal)
{
	get_input(tanggal, "- Masukan Hari Kelahiran Anda");
}
inline void
input_pekerjaan(std::string& pekerjaan)
{
	get_input(pekerjaan, "- Masukan Pekerjaan Anda: ");
}
inline void
input_kecamatan(std::string& kecamatan)
{
	get_input(kecamatan, "- Masukan Kecamatan Anda: ");
}
inline void
input_tempat_lahir(std::string& tempat_lahir)
{
	get_input(tempat_lahir, "- Masukan Tempat Kelahiran Anda: ");
}
inline void
input_kelurahan_desa(std::string& kelurahan_desa)
{
	get_input(kelurahan_desa, "- Masukan Kelurahan/Desa Anda: ");
}
inline void
input_status_nikah(bool& sudah_nikah)
{
	sudah_nikah =
	    yesno_prompt("- Apakah Anda Sudah Nikah? [Ya/Tidak]: ", 'y', 't');
}
inline void
input_kelamin(std::string& kelamin)
{
	yesno_prompt("- Apa Jenis Kelamin Anda [L/P]: ", 'l', 'p')
	    ? kelamin = "Laki-Laki"
	    : kelamin = "Peremuan";
}
inline void
input_kewarganegaraan(std::string& kewarganegaraan)
{
	yesno_prompt("- Apakah Anda Warga Negara Indonesia? [Ya/Tidak]: ", 'y',
	             't')
	    ? kewarganegaraan = "WNI"
	    : kewarganegaraan = "WNA";
}
