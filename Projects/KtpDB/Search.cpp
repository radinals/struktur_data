#include "Search.h"
#include "Database.h"
#include "Prompt.h"
#include "StrUtils.h"
#include <cstddef>
#include <stdexcept>
#include <string>
#include <strings.h>
#include <vector>

static bool val_in_vector(size_t val, const std::vector<size_t>& vec);

size_t
sequential_search(UserCmd* cmd, size_t start)
{
        bool found = false;
        for (size_t i = start; i < DatabaseLen; i++) {
                DataKtp* data = data_at(i);

                if (data == nullptr)
                        continue;

                switch (cmd->member) {
                case MEM_NIK:
                        found = (data->nik == cmd->lnum);
                        break;
                case MEM_TempatLahir:
                        found =
                            (data->tempat_tgl_lahir.tempat_lahir == cmd->str);
                        break;
                case MEM_Nama:
                        found = (data->nama == cmd->str);
                        break;

                case MEM_Kelamin:
                        found = (data->kelamin == cmd->str);
                        break;
                case MEM_TanggalLahir: {
                        bool hari_found = false;
                        bool bulan_found = false;
                        bool tahun_found = false;

                        int hari, bulan, tahun;
                        hari = bulan = tahun = 0;

                        for (const std::string& token :
                             split_str(cmd->str, '-')) {
                                int num = stoi(token);
                                if (bulan_found && hari_found && tahun_found)
                                        break;

                                if (num < 0)
                                        continue;

                                if (num <= 31 && !bulan_found && !hari_found) {
                                        hari = num;
                                        hari_found = true;
                                } else if (num <= 12 && !bulan_found &&
                                           hari_found) {
                                        bulan = num;
                                        bulan_found = true;
                                } else if (hari_found && bulan_found) {
                                        tahun = num;
                                        tahun_found = true;
                                }
                        }

                        found = (data->tempat_tgl_lahir.hari == hari &&
                                 data->tempat_tgl_lahir.bulan == bulan &&
                                 data->tempat_tgl_lahir.tahun == tahun);
                } break;
                case MEM_Alamat:
                        found = (data->alamat.alamat_asli == cmd->str);
                        break;
                case MEM_RT:
                        found = (data->alamat.rt == cmd->inum);
                        break;
                case MEM_RW:
                        found = (data->alamat.rw == cmd->inum);
                        break;
                case MEM_KelurahanDesa:
                        found = (data->alamat.kelurahan_desa == cmd->str);
                        break;
                case MEM_Kecamatan:
                        found = (data->alamat.kecamatan == cmd->str);
                        break;
                case MEM_SudahKawin:
                        found = (data->sudah_kawin);
                        break;
                case MEM_BelumKawin:
                        found = (!data->sudah_kawin);
                        break;
                case MEM_Pekerjaan:
                        found = (data->pekerjaan == cmd->str);
                        break;
                case MEM_Kewarganegaraan:
                        found = (data->kewarganegaraan == cmd->str);
                        break;
                case MEM_Agama:
                        found = (data->agama == cmd->str);
                        break;
                }

                if (found)
                        return i;
        }

        throw std::out_of_range("Data Not Found\n");
}

std::vector<size_t>
sequential_search_all(UserCmd* user_cmd)
{
        std::vector<size_t> indexes;
        size_t index = 0;

        while (true) {
                try {
                        index = sequential_search(user_cmd, index);

                } catch (std::out_of_range) {
                        break;
                }

                if (!val_in_vector(index, indexes))
                        indexes.push_back(index);
                else
                        index++;
        }

        if (indexes.empty())
                throw std::out_of_range("Data Not Found\n");
        else
                return indexes;
}

static bool
val_in_vector(size_t val, const std::vector<size_t>& vec)
{
        for (size_t n : vec) {
                if (n == val)
                        return true;
        }

        return false;
}
