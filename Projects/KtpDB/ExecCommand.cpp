#include "ExecCommand.h"

#include "Database.h"
#include "Prompt.h"
#include "Search.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

void
exec_cmd(UserCmd* user_cmd)
{
	switch (user_cmd->type) {

	case CMDTYPE_List:
		print_all_data();
		break;

	case CMDTYPE_Search: {
		try {
			if (user_cmd->target_type == Target_member &&
			    user_cmd->scope == CS_All) {
				print_data_at_indexes(
				    sequential_search_all(user_cmd));

			} else if (user_cmd->target_type == Target_member &&
			           user_cmd->scope == CS_First) {
				print_data_at(sequential_search(user_cmd));
			} else if (user_cmd->target_type == Target_index) {
				print_data_at(user_cmd->inum);
			}
		} catch (std::out_of_range) {
			std::cout << "ERROR: Data tidak ditemukan!\n";
		}
	} break;

	case CMDTYPE_Add:
		input_new_data();
		break;

	case CMDTYPE_Delete: {
		if (user_cmd->target_type == Target_member &&
		    user_cmd->scope == CS_All) {
			for (const size_t& index :
			     sequential_search_all(user_cmd)) {
				delete_at(index);
			}

		} else if (user_cmd->target_type == Target_member &&
		           user_cmd->scope == CS_First) {
			delete_at(sequential_search(user_cmd));
		} else if (user_cmd->target_type == Target_index) {
			delete_at(user_cmd->inum);
		}
	} break;

	case CMDTYPE_Modify: {
		if (user_cmd->target_type == Target_index) {
			DataKtp* data = data_at(user_cmd->inum);
			if (data != nullptr)
				input_data(*data);
			else
				std::cout << "ERROR: Tidak ada data di index "
				          << user_cmd->inum << "!\n";
		} else if (user_cmd->target_type == Target_member) {
			edit_data_at(user_cmd->member, user_cmd->inum);
		}
	} break;

	case CMDTYPE_Help: {
		std::cout
		    << "KtpDB v0.0.1: Implementasi Database Sederhana\n"
		    << "Report Bugs to: https://github.com/radinals/struktur_data\n"
		    << "Author: RSS\n\n"
		    << "- List\n"
		    << "- Printing\n"
		    << "\tLIST                   -> Tampilkan Semua Data\n"
		    << "- Pencarian\n"
		    << "\tSEARCH #12             -> Tampilkan data di index 12.\n"
		    << "\tSEARCH ALL NAMA budi   -> Cari SEMUA data yang memiliki NAMA 'budi' dan tampilkan.\n"
		    << "\tSEARCH FIRST NAMA budi -> Tampilkan data PERTAMA yang ditemukan memiliki NAMA budi.\n"
		    << "- Deleting\n"
		    << "\tDELETE #12             -> Hapus data di index 12.\n"
		    << "\tDELETE ALL NAMA budi   -> Hapus SEMUA data yang memiliki NAMA budi\n"
		    << "\tDELETE FIRST NAMA budi -> Hapus data PERTAMA yang ditemukan memiliki NAMA budi.\n"
		    << "- EDIT\n"
		    << "\tEDIT #12               -> Re-input data index 12.\n"
		    << "\tEDIT NAMA #12          -> Edit data NAMA di index 12\n"
		    << "- ADDING\n"
		    << "\tADD                    -> (input data baru)\n"
		    << "- Informasi\n"
		    << "\tHELP                   -> Tampilkan manual ini\n";
	} break;

	case CMDTYPE_Quit:
		exit(0);
		break;

	default:
		std::cout << "ERROR: Invalid Command!\n";
	}
}
