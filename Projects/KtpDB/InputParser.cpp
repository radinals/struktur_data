#include "InputParser.h"

#include "StrUtils.h"
#include "UserCmd.h"

#include <stdexcept>

void
parse_input(UserCmd& cmd, const std::string& str)
{
	if (str.empty()) {
		throw std::invalid_argument("ERR: No command found");
	}

	bool command_type_found = false;
	bool command_scope_found = false;
	bool target_type_found = false;
	bool index_found = false;

	for (std::string token : split_str(str, ' ')) {

		if (command_type_found && command_scope_found &&
		    target_type_found) {

			if (!index_found)
				index_found = true;

			if (!cmd.str.empty())
				cmd.str += " ";

			cmd.str += token;

			continue;
		}

		if (!command_type_found) {
			if (token == "ADD") {
				cmd.type = CMDTYPE_Add;
				cmd.target_type = Target_None;

				command_type_found = true;
				command_scope_found = true;
				index_found = true;
				target_type_found = true;
				break;

			} else if (token == "LIST") {
				cmd.type = CMDTYPE_List;
				cmd.target_type = Target_None;

				command_type_found = true;
				command_scope_found = true;
				index_found = true;
				target_type_found = true;
				break;

			} else if (token == "QUIT") {
				cmd.type = CMDTYPE_Quit;
				cmd.target_type = Target_None;

				command_type_found = true;
				command_scope_found = true;
				index_found = true;
				target_type_found = true;
				break;

			} else if (token == "HELP") {
				cmd.type = CMDTYPE_Help;
				cmd.target_type = Target_None;

				command_type_found = true;
				command_scope_found = true;
				index_found = true;
				target_type_found = true;
				break;

			} else if (token == "SEARCH") {
				cmd.type = CMDTYPE_Search;
				command_type_found = true;
			} else if (token == "EDIT") {
				cmd.type = CMDTYPE_Modify;
				command_type_found = true;
			} else if (token == "DELETE") {
				cmd.type = CMDTYPE_Delete;
				command_type_found = true;
			}

			if (command_type_found)
				continue;
		}

		if (!command_scope_found) {
			if (token == "ALL") {
				cmd.scope = CS_All;
				command_scope_found = true;
			} else if (token == "FIRST") {
				cmd.scope = CS_First;
				command_scope_found = true;
			}

			if (command_scope_found)
				continue;
		}

		if (!target_type_found) {
			if (token == "NIK") {
				cmd.member = MEM_NIK;
				cmd.target_type = Target_member;
				target_type_found = true;
			} else if (token == "NAMA") {
				cmd.member = MEM_Nama;
				cmd.target_type = Target_member;
				target_type_found = true;
			} else if (token == "TEMPAT_LAHIR") {
				cmd.member = MEM_TempatLahir;
				cmd.target_type = Target_member;
				target_type_found = true;
			} else if (token == "TANGGAL_LAHIR") {
				cmd.member = MEM_TanggalLahir;
				cmd.target_type = Target_member;
				target_type_found = true;
			} else if (token == "KELAMIN") {
				cmd.member = MEM_Kelamin;
				cmd.target_type = Target_member;
				target_type_found = true;
			} else if (token == "ALAMAT") {
				cmd.member = MEM_Alamat;
				cmd.target_type = Target_member;
				target_type_found = true;
			} else if (token == "RT") {
				cmd.member = MEM_RT;
				cmd.target_type = Target_member;
				target_type_found = true;
			} else if (token == "RW") {
				cmd.member = MEM_RW;
				cmd.target_type = Target_member;
				target_type_found = true;
			} else if (token == "KELURAHAN_DESA") {
				cmd.member = MEM_KelurahanDesa;
				cmd.target_type = Target_member;
				target_type_found = true;
			} else if (token == "KECAMATAN") {
				cmd.member = MEM_Kecamatan;
				cmd.target_type = Target_member;
				target_type_found = true;
			} else if (token == "AGAMA") {
				cmd.member = MEM_Agama;
				cmd.target_type = Target_member;
				target_type_found = true;
			} else if (token == "SUDAH_KAWIN") {
				cmd.member = MEM_SudahKawin;
				cmd.target_type = Target_member;
				target_type_found = true;
				index_found = true;
				break;
			} else if (token == "BELUM_KAWIN") {
				cmd.member = MEM_BelumKawin;
				cmd.target_type = Target_member;
				target_type_found = true;
				index_found = true;
				break;
			} else if (token == "PEKERJAAN") {
				cmd.member = MEM_Pekerjaan;
				cmd.target_type = Target_member;
				target_type_found = true;
			} else if (token == "KEWARGANEGARAAN") {
				cmd.member = MEM_Kewarganegaraan;
				cmd.target_type = Target_member;
				target_type_found = true;
			}
			if (target_type_found)
				continue;
		}

		if (token.at(0) == '#' && !index_found && command_type_found) {

			if (!target_type_found)
				cmd.target_type = Target_index;

			if (cmd.type == CMDTYPE_Delete &&
			    cmd.target_type == Target_index)
				break;

			if ((cmd.type == CMDTYPE_Search ||
			     cmd.type == CMDTYPE_Modify) &&
			    command_scope_found)
				break;

			remove_all_char(token, '#');
			cmd.str += token;

			index_found = true;
			target_type_found = true;

			command_scope_found = true;

			break;
		}
	}

	if (!command_type_found || !target_type_found || !command_scope_found ||
	    !index_found) {
		throw std::invalid_argument("ERR: No command found");
	}

	get_arg(cmd);
}

void
get_arg(UserCmd& cmd)
{

	if (cmd.target_type == Target_None)
		return;
	if (cmd.target_type == Target_index ||
	    (cmd.type == CMDTYPE_Modify && cmd.target_type == Target_member))
		cmd.inum = std::stoi(cmd.str.c_str());
	else if (cmd.target_type == Target_member) {
		switch (cmd.member) {
			// clang-format off
		case MEM_Pekerjaan: case MEM_Kewarganegaraan:
		case MEM_KelurahanDesa: case MEM_Agama:
		case MEM_Alamat: case MEM_Kecamatan:
		case MEM_TanggalLahir: case MEM_TempatLahir: case MEM_Nama:
		case MEM_Kelamin: case MEM_SudahKawin: case MEM_BelumKawin:
			break;
			// clang-format on
		case MEM_NIK:
			cmd.lnum = std::stol(cmd.str.c_str());
			break;

		case MEM_RT:
		case MEM_RW:
			cmd.inum = std::stoi(cmd.str.c_str());
			break;

		default:
			break;
		}
	}
}
