#include "Database.h"

#include "Prompt.h"

#include <cctype>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <strings.h>

static void input_nik(long int& nik);
static void input_nama(std::string& nama);
static void input_kelamin(std::string& kelamin);
static void input_alamat(std::string& input_alamat);
static void input_rt(int& rt);
static void input_rw(int& rw);
static void input_kelurahan_desa(std::string& kelurahan_desa);
static void input_kecamatan(std::string& kecamatan);
static void input_tempat_lahir(std::string& tempat_lahir);
static void input_tanggal_lahir(int& tanggal);
static void input_bulan_lahir(int& bulan);
static void input_tahun_lahir(int& tahun);
static void input_agama(std::string& agama);
static void input_kewarganegaraan(std::string& kewarganegaraan);
static void input_pekerjaan(std::string& pekerjaan);
static void input_status_nikah(bool& sudah_nikah);
static DataKtp* unbound_data_at(size_t i);

void
check_database_size()
{
	if (DatabaseLen >= DatabaseSize) {
		std::cout
		    << "#> Mengecek ukuran penyimpanan...memperbesar...\n";
		grow_database();
	} else if ((DatabaseSize - DatabaseLen) > _BASESIZE &&
	           DatabaseSize - _BASESIZE > _BASESIZE) {
		std::cout
		    << "#> Mengecek ukuran penyimpanan...memperkecil...\n";
		shrink_database(_BASESIZE);
	}
}

void
add_new(const DataKtp& dataktp)
{
	check_database_size();
	DatabaseLen += 1;
	Database[DatabaseLen - 1] = dataktp;
}

void
delete_at(size_t index)
{
	if (index < 0 || index > DatabaseLen || DatabaseLen == 0)
		return;

	for (size_t i = index; i < DatabaseLen - 1; i++)
		Database[i] = Database[i + 1];

	DatabaseLen -= 1;
}

static DataKtp*
unbound_data_at(size_t index)
{
	if (index >= DatabaseSize || DatabaseLen == 0)
		return nullptr;
	else
		return &(Database[index]);
}

DataKtp*
data_at(size_t index)
{
	if (index > DatabaseLen || DatabaseLen == 0)
		return nullptr;
	else
		return &(Database[index]);
}

void
init_database()
{
	DatabaseLen = 0;
	DatabaseSize = _BASESIZE;
	set_database_size(_BASESIZE);
}

void
grow_database()
{
	size_t new_size = (DatabaseSize + _BASESIZE);
	set_database_size(new_size);
}

void
shrink_database(size_t mod)
{
	size_t new_size = (DatabaseSize - mod);

	if (new_size < 0 || new_size < DatabaseLen)
		return;

	set_database_size(new_size);
}

void
set_database_size(size_t size)
{
	DataKtp* new_database = new DataKtp[size];

	if (DatabaseLen > 0) {
		for (size_t i = 0; i < DatabaseLen; i++)
			new_database[i] = Database[i];
		delete[] Database;
		Database = nullptr;
	}

	Database = new_database;
	DatabaseSize = size;
}

void
edit_data_at(MemberName member, size_t index)
{
	DataKtp* tmp = data_at(index);

	if (tmp == nullptr) {
		std::cout << "ERROR: Tidak ada data di index " << index
		          << "!\n";
		return;
	}

	switch (member) {

	case MEM_NIK:
		input_nik(tmp->nik);
		break;
	case MEM_Nama:
		input_nama(tmp->nama);
		break;
	case MEM_TempatLahir:
		input_tempat_lahir(tmp->tempat_tgl_lahir.tempat_lahir);
		break;
	case MEM_TanggalLahir: {
		input_tanggal_lahir(tmp->tempat_tgl_lahir.hari);
		input_bulan_lahir(tmp->tempat_tgl_lahir.bulan);
		input_tahun_lahir(tmp->tempat_tgl_lahir.tahun);
	} break;
	case MEM_Kelamin:
		input_kelamin(tmp->kelamin);
		break;
	case MEM_Alamat:
		input_alamat(tmp->alamat.alamat_asli);
		break;
	case MEM_RT:
		input_rt(tmp->alamat.rt);
		break;
	case MEM_RW:
		input_rw(tmp->alamat.rw);
		break;
	case MEM_KelurahanDesa:
		input_kelurahan_desa(tmp->alamat.kelurahan_desa);
		break;
	case MEM_Kecamatan:
		input_kecamatan(tmp->alamat.kecamatan);
		break;
	case MEM_Agama:
		input_agama(tmp->agama);
		break;
	case MEM_SudahKawin:
		tmp->sudah_kawin = true;
	case MEM_BelumKawin:
		tmp->sudah_kawin = false;
		break;
	case MEM_Pekerjaan:
		input_pekerjaan(tmp->pekerjaan);
		break;
	case MEM_Kewarganegaraan:
		input_kewarganegaraan(tmp->kewarganegaraan);
		break;
	default:
		std::cout << "ERROR: Invalid Member\n";
		break;
	}
}

static void
input_nik(long int& nik)
{
	while (true) {
		std::string buffer;
		std::cout << "Masukan NIK anda: ";
		std::cout.flush();
		getline(std::cin, buffer);

		try {
			nik = std::stol(buffer);
		} catch (std::invalid_argument) {
			continue;
		}

		break;
	}
	std::cin.clear();
}

static void
input_nama(std::string& nama)
{
	while (true) {
		std::cout << "Masukan Nama anda: ";
		std::cout.flush();
		getline(std::cin, nama);

		if (!nama.empty())
			break;
	}
}

static void
input_kelamin(std::string& kelamin)
{
	while (true) {
		std::string jwb;
		std::cout << "Apa jenis Kelamin anda (L/P): ";
		std::cout.flush();
		getline(std::cin, jwb);

		if (jwb.empty())
			continue;

		if (tolower(jwb.at(0)) == 'l') {
			kelamin = "LAKI-LAKI";
			break;
		} else if (tolower(jwb.at(0)) == 'p') {
			kelamin = "PEREMPUAN";
			break;
		} else
			continue;
	}
}

static void
input_alamat(std::string& alamat)
{
	while (true) {
		std::cout << "Masukan Alamat anda: ";
		std::cout.flush();
		getline(std::cin, alamat);

		if (!alamat.empty())
			break;
	}
}

static void
input_rt(int& rt)
{
	while (true) {
		std::string buffer;
		std::cout << "Masukan nomor RT anda: ";
		std::cout.flush();
		getline(std::cin, buffer);

		try {
			rt = std::stoi(buffer);
		} catch (std::invalid_argument) {
			continue;
		}

		break;
	}
	std::cin.clear();
}

static void
input_rw(int& rw)
{

	while (true) {
		std::string buffer;
		std::cout << "Masukan nomor RW anda: ";
		std::cout.flush();
		getline(std::cin, buffer);

		try {
			rw = std::stoi(buffer);
		} catch (std::invalid_argument) {
			continue;
		}

		break;
	}
	std::cin.clear();
}

static void
input_kelurahan_desa(std::string& kelurahan_desa)
{
	while (true) {
		std::cout << "Masukan kelurahan/desa anda: ";
		std::cout.flush();
		getline(std::cin, kelurahan_desa);

		if (!kelurahan_desa.empty())
			break;
	}
}

static void
input_kecamatan(std::string& kecamatan)
{
	while (true) {
		std::cout << "Masukan kecamatan anda: ";
		std::cout.flush();
		getline(std::cin, kecamatan);

		if (!kecamatan.empty())
			break;
	}
}

static void
input_tempat_lahir(std::string& tempat_lahir)
{
	while (true) {
		std::cout << "Masukan tempat lahir anda: ";
		std::cout.flush();
		getline(std::cin, tempat_lahir);

		if (!tempat_lahir.empty())
			break;
	}
}

static void
input_tanggal_lahir(int& tanggal)
{
	while (true) {
		std::string buffer;
		std::cout << "Masukan tanggal kelahiran anda: ";
		std::cout.flush();
		getline(std::cin, buffer);

		try {
			tanggal = std::stoi(buffer);
		} catch (std::invalid_argument) {
			continue;
		}

		break;
	}
	std::cin.clear();
}

static void
input_bulan_lahir(int& bulan)
{

	while (true) {
		std::string buffer;
		std::cout << "Masukan Bulan kelahiran anda: ";
		std::cout.flush();
		getline(std::cin, buffer);

		try {
			bulan = std::stoi(buffer);
		} catch (std::invalid_argument) {
			continue;
		}

		break;
	}
	std::cin.clear();
}

static void
input_tahun_lahir(int& tahun)
{
	while (true) {
		std::string buffer;
		std::cout << "Masukan Tahun kelahiran anda: ";
		std::cout.flush();
		getline(std::cin, buffer);

		try {
			tahun = std::stoi(buffer);
		} catch (std::invalid_argument) {
			continue;
		}

		break;
	}
	std::cin.clear();
}

static void
input_agama(std::string& agama)
{
	while (true) {
		std::cout << "Masukan Agama anda: ";
		std::cout.flush();
		getline(std::cin, agama);

		if (!agama.empty())
			break;
	}
}

static void
input_kewarganegaraan(std::string& kewarganegaraan)
{

	while (true) {
		std::string jwb;
		std::cout
		    << "Apakah anda kewarganegaraan indonesia? [Y]a/[T]idak: ";
		std::cout.flush();
		getline(std::cin, jwb);

		if (jwb.empty())
			continue;

		if (tolower(jwb.at(0)) == 'y') {
			kewarganegaraan = "WNI";
			break;
		} else if (tolower(jwb.at(0) == 't')) {
			kewarganegaraan = "WNA";
			break;
		}
	}
}

static void
input_pekerjaan(std::string& pekerjaan)
{
	while (true) {
		std::cout << "Masukan pekerjaan anda: ";
		std::cout.flush();
		getline(std::cin, pekerjaan);

		if (!pekerjaan.empty())
			break;
	}
}

static void
input_status_nikah(bool& sudah_nikah)
{
	while (true) {
		std::string jwb;
		std::cout << "Apakah anda sudah kawin? [Y]a/[T]idak ";
		std::cout.flush();
		getline(std::cin, jwb);

		if (jwb.empty())
			continue;

		if (tolower(jwb.at(0)) == 'y') {
			sudah_nikah = true;
			break;
		} else if (tolower(jwb.at(0) == 't')) {
			sudah_nikah = false;
			break;
		}
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
	input_pekerjaan(data_ktp.pekerjaan);
	input_kewarganegaraan(data_ktp.kewarganegaraan);
	input_status_nikah(data_ktp.sudah_kawin);
}

void
input_new_data()
{
	check_database_size();
	DatabaseLen += 1;
	input_data(Database[DatabaseLen - 1]);
}

void
print_data_at(size_t index)
{
	DataKtp* data_ktp = data_at(index);
	if (data_ktp == nullptr)
		throw std::out_of_range("Index Invalid");

	std::cout << "INDEX DATA         : #" << index << "\n";
	std::cout << "NIK                : " << data_ktp->nik << "\n";
	std::cout << "NAMA               : " << data_ktp->nama << "\n";
	std::cout << "JENIS KELAMIN      : " << data_ktp->kelamin << "\n";
	std::cout << "TEMPAT/TGL LAHIR   : "
	          << data_ktp->tempat_tgl_lahir.tempat_lahir << ", "
	          << data_ktp->tempat_tgl_lahir.hari << "-"
	          << data_ktp->tempat_tgl_lahir.bulan << "-"
	          << data_ktp->tempat_tgl_lahir.tahun << "\n";

	std::cout << "ALAMAT             : " << data_ktp->alamat.alamat_asli
	          << "\n";
	std::cout << "   RT/RW           : " << data_ktp->alamat.rt << "/"
	          << data_ktp->alamat.rw << "\n";

	std::cout << "   KEL/DESA        : " << data_ktp->alamat.kelurahan_desa
	          << "\n";
	std::cout << "   KECAMATAN       : " << data_ktp->alamat.kecamatan
	          << "\n";
	std::cout << "AGAMA              : " << data_ktp->agama << "\n";

	if (data_ktp->sudah_kawin)
		std::cout << "STATUS PERKAWINAN  : "
		          << "SUDAH KAWIN"
		          << "\n";
	else
		std::cout << "STATUS PERKAWINAN  : "
		          << "BELUM KAWIN"
		          << "\n";

	std::cout << "PERKERJAAN         : " << data_ktp->pekerjaan << "\n";
	std::cout << "KEWARGANEGARAAN    : " << data_ktp->kewarganegaraan
	          << "\n\n";
}

void
print_data_at_indexes(const std::vector<size_t>& indexes)
{
	if (indexes.empty())
		return;

	for (const size_t& index : indexes) {
		print_data_at(index);
	}

	std::cout << "Ditemukan: " << indexes.size() << " data yang sesuai\n";
}

void
print_all_data()
{
	if (DatabaseLen == 0)
		std::cout << "ERROR: Tidak ada data KTP yang tersimpan!\n";

	for (size_t i = 0; i < DatabaseLen; i++) {
		print_data_at(i);
	}
}
