#include "DataKtp.h"
#include "Database.h"

#include <cstddef>
#include <iostream>
#include <list>
#include <stdexcept>

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
print_data_at_indexes(const std::list<size_t>& indexes)
{
	if (indexes.empty())
		return;

	for (const size_t& index : indexes) print_data_at(index);

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
