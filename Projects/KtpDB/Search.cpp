#include "Search.h"

#include "Database.h"
#include "Prompt.h"

#include <cstddef>
#include <list>
#include <stdexcept>
#include <string>
#include <strings.h>

size_t
sequential_search(const UserCmd& cmd, size_t start)
{
	bool found = false;
	for (size_t i = start; i < DatabaseLen; i++) {

		DataKtp* data = data_at(i);

		if (data == nullptr)
			continue;

		switch (cmd.member) {
		case MEM_NIK:
			found = (data->nik == cmd.lnum);
			break;
		case MEM_TempatLahir:
			found =
			    (data->tempat_tgl_lahir.tempat_lahir == cmd.str);
			break;
		case MEM_Nama:
			found = (data->nama == cmd.str);
			break;

		case MEM_Kelamin:
			found = (data->kelamin == cmd.str);
			break;
		case MEM_TanggalLahir: {
			std::string str_tanggal;
			// clang-format off
			str_tanggal += std::to_string(data->tempat_tgl_lahir.hari);
			str_tanggal += "-";
			str_tanggal += std::to_string(data->tempat_tgl_lahir.bulan);
			str_tanggal += "-";
			str_tanggal += std::to_string(data->tempat_tgl_lahir.tahun);
			// clang-format on
			found = (str_tanggal == cmd.str);
		} break;
		case MEM_Alamat:
			found = (data->alamat.alamat_asli == cmd.str);
			break;
		case MEM_RT:
			found = (data->alamat.rt == cmd.inum);
			break;
		case MEM_RW:
			found = (data->alamat.rw == cmd.inum);
			break;
		case MEM_KelurahanDesa:
			found = (data->alamat.kelurahan_desa == cmd.str);
			break;
		case MEM_Kecamatan:
			found = (data->alamat.kecamatan == cmd.str);
			break;
		case MEM_SudahKawin:
			found = (data->sudah_kawin);
			break;
		case MEM_BelumKawin:
			found = (!data->sudah_kawin);
			break;
		case MEM_Pekerjaan:
			found = (data->pekerjaan == cmd.str);
			break;
		case MEM_Kewarganegaraan:
			found = (data->kewarganegaraan == cmd.str);
			break;
		case MEM_Agama:
			found = (data->agama == cmd.str);
			break;
		}

		if (found)
			return i;
	}

	throw std::out_of_range("Data Not Found\n");
}

std::list<size_t>
sequential_search_all(const UserCmd& cmd)
{
	std::list<size_t> indexes;
	size_t index = 0;

	while (true) {
		try {
			index = sequential_search(cmd, index);
		} catch (std::out_of_range) {
			break;
		}

		indexes.push_back(index);
		index++;
	}

	if (indexes.empty())
		throw std::out_of_range("Data Not Found\n");
	else
		return indexes;
}
