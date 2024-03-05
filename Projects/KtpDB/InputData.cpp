#include "InputData.h"

#include "DataKtp.h"

#include <iostream>
#include <stdexcept>

void
get_input(std::string& str, const std::string& prompt)
{
	while (true) {
		std::cout << prompt;
		std::cout.flush();
		getline(std::cin, str);

		if (!str.empty())
			break;
	}
}

void
get_input(int& inum, const std::string& prompt)
{
	while (true) {
		std::string buffer;
		std::cout << prompt;
		std::cout.flush();
		getline(std::cin, buffer);

		try {
			inum = std::stoi(buffer);
		} catch (std::invalid_argument) {
			continue;
		}

		break;
	}
	std::cin.clear();
}

void
get_input(long int& lnum, const std::string& prompt)
{
	while (true) {
		std::string buffer;
		std::cout << prompt;
		std::cout.flush();
		getline(std::cin, buffer);

		try {
			lnum = std::stol(buffer);
		} catch (std::invalid_argument) {
			continue;
		}

		break;
	}
	std::cin.clear();
}

bool
yesno_prompt(const std::string& prompt, const char& true_char,
             const char& false_char)
{
	while (true) {
		std::string jwb;
		std::cout << prompt;
		std::cout.flush();
		getline(std::cin, jwb);

		if (jwb.empty())
			continue;

		if (tolower(jwb.at(0)) == true_char) {
			return true;
		} else if (tolower(jwb.at(0)) == false_char) {
			return false;
		} else
			continue;
	}
}

void
input_data(DataKtp& data_ktp)
{
	input_nik(data_ktp.nik);
	input_nama(data_ktp.nama);
	input_kelamin(data_ktp.kelamin);
	input_alamat(data_ktp.alamat.alamat_asli);
	input_rt(data_ktp.alamat.rt);
	input_rw(data_ktp.alamat.rw);
	input_kelurahan_desa(data_ktp.alamat.kelurahan_desa);
	input_kecamatan(data_ktp.alamat.kecamatan);
	input_tempat_lahir(data_ktp.tempat_tgl_lahir.tempat_lahir);
	input_tanggal_lahir(data_ktp.tempat_tgl_lahir.hari);
	input_bulan_lahir(data_ktp.tempat_tgl_lahir.bulan);
	input_tahun_lahir(data_ktp.tempat_tgl_lahir.tahun);
	input_agama(data_ktp.agama);
	input_kewarganegaraan(data_ktp.kewarganegaraan);
	input_pekerjaan(data_ktp.pekerjaan);
	input_status_nikah(data_ktp.sudah_kawin);
}
