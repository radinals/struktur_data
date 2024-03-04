#include "Database.h"

#include "DataKtp.h"
#include "InputData.h"
#include "UserCmd.h"

#include <iostream>

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

void
input_new_data()
{
	check_database_size();
	DatabaseLen += 1;
	input_data(Database[DatabaseLen - 1]);
}
