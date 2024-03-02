#include "Prompt.h"

#include "StrUtils.h"

#include <iostream>
#include <stdexcept>
#include <string>

UserCmd
prompt_user()
{
	UserCmd user_cmd;
	std::string user_input = "";

	std::cout << "CMD: ";

	getline(std::cin, user_input);

	parse_input(user_cmd, user_input);

	return user_cmd;
}

void
parse_input(UserCmd& user_cmd, const std::string& str)
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

			if (!user_cmd.str.empty())
				user_cmd.str += " ";

			user_cmd.str += token;

			continue;
		}

		if (!command_type_found) {
			if (token == "ADD") {
				user_cmd.type = CMDTYPE_Add;
				user_cmd.target_type = Target_None;

				command_type_found = true;
				command_scope_found = true;
				index_found = true;
				target_type_found = true;
				break;

			} else if (token == "LIST") {
				user_cmd.type = CMDTYPE_List;
				user_cmd.target_type = Target_None;

				command_type_found = true;
				command_scope_found = true;
				index_found = true;
				target_type_found = true;
				break;

			} else if (token == "QUIT") {
				user_cmd.type = CMDTYPE_Quit;
				user_cmd.target_type = Target_None;

				command_type_found = true;
				command_scope_found = true;
				index_found = true;
				target_type_found = true;
				break;

			} else if (token == "HELP") {
				user_cmd.type = CMDTYPE_Help;
				user_cmd.target_type = Target_None;

				command_type_found = true;
				command_scope_found = true;
				index_found = true;
				target_type_found = true;
				break;

			} else if (token == "SEARCH") {
				user_cmd.type = CMDTYPE_Search;
				command_type_found = true;
			} else if (token == "EDIT") {
				user_cmd.type = CMDTYPE_Modify;
				command_type_found = true;
			} else if (token == "DELETE") {
				user_cmd.type = CMDTYPE_Delete;
				command_type_found = true;
			}

			if (command_type_found)
				continue;
		}

		if (!command_scope_found) {
			if (token == "ALL") {
				user_cmd.scope = CS_All;
				command_scope_found = true;
			} else if (token == "FIRST") {
				user_cmd.scope = CS_First;
				command_scope_found = true;
			}

			if (command_scope_found)
				continue;
		}

		if (!target_type_found) {
			if (token == "NIK") {
				user_cmd.member = MEM_NIK;
				user_cmd.target_type = Target_member;
				target_type_found = true;
			} else if (token == "NAMA") {
				user_cmd.member = MEM_Nama;
				user_cmd.target_type = Target_member;
				target_type_found = true;
			} else if (token == "TEMPAT_LAHIR") {
				user_cmd.member = MEM_TempatLahir;
				user_cmd.target_type = Target_member;
				target_type_found = true;
			} else if (token == "TANGGAL_LAHIR") {
				user_cmd.member = MEM_TanggalLahir;
				user_cmd.target_type = Target_member;
				target_type_found = true;
			} else if (token == "KELAMIN") {
				user_cmd.member = MEM_Kelamin;
				user_cmd.target_type = Target_member;
				target_type_found = true;
			} else if (token == "ALAMAT") {
				user_cmd.member = MEM_Alamat;
				user_cmd.target_type = Target_member;
				target_type_found = true;
			} else if (token == "RT") {
				user_cmd.member = MEM_RT;
				user_cmd.target_type = Target_member;
				target_type_found = true;
			} else if (token == "RW") {
				user_cmd.member = MEM_RW;
				user_cmd.target_type = Target_member;
				target_type_found = true;
			} else if (token == "KELURAHAN_DESA") {
				user_cmd.member = MEM_KelurahanDesa;
				user_cmd.target_type = Target_member;
				target_type_found = true;
			} else if (token == "KECAMATAN") {
				user_cmd.member = MEM_Kecamatan;
				user_cmd.target_type = Target_member;
				target_type_found = true;
			} else if (token == "AGAMA") {
				user_cmd.member = MEM_Agama;
				user_cmd.target_type = Target_member;
				target_type_found = true;
			} else if (token == "SUDAH_KAWIN") {
				user_cmd.member = MEM_SudahKawin;
				user_cmd.target_type = Target_member;
				target_type_found = true;
				index_found = true;
				break;
			} else if (token == "BELUM_KAWIN") {
				user_cmd.member = MEM_BelumKawin;
				user_cmd.target_type = Target_member;
				target_type_found = true;
				index_found = true;
				break;
			} else if (token == "PEKERJAAN") {
				user_cmd.member = MEM_Pekerjaan;
				user_cmd.target_type = Target_member;
				target_type_found = true;
			} else if (token == "KEWARGANEGARAAN") {
				user_cmd.member = MEM_Kewarganegaraan;
				user_cmd.target_type = Target_member;
				target_type_found = true;
			}
			if (target_type_found)
				continue;
		}

		if (token.at(0) == '#' && !index_found && command_type_found) {

			if (!target_type_found)
				user_cmd.target_type = Target_index;

			if (user_cmd.type == CMDTYPE_Delete &&
			    user_cmd.target_type == Target_index)
				break;

			if ((user_cmd.type == CMDTYPE_Search ||
			     user_cmd.type == CMDTYPE_Modify) &&
			    command_scope_found)
				break;

			remove_all_char(token, '#');
			user_cmd.str += token;

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

	get_arg(user_cmd);
}

void
get_arg(UserCmd& user_cmd)
{

	if (user_cmd.target_type == Target_None)
		return;
	if (user_cmd.target_type == Target_index ||
	    (user_cmd.type == CMDTYPE_Modify &&
	     user_cmd.target_type == Target_member))
		user_cmd.inum = std::stoi(user_cmd.str.c_str());
	else if (user_cmd.target_type == Target_member) {
		switch (user_cmd.member) {
			// clang-format off
		case MEM_Pekerjaan: case MEM_Kewarganegaraan:
		case MEM_KelurahanDesa: case MEM_Agama:
		case MEM_Alamat: case MEM_Kecamatan:
		case MEM_TempatLahir: case MEM_Nama:
		case MEM_TanggalLahir: case MEM_Kelamin:
		case MEM_SudahKawin: case MEM_BelumKawin:
			break;
			// clang-format on

		case MEM_NIK:
			user_cmd.lnum = std::stol(user_cmd.str.c_str());
			break;

		case MEM_RT:
		case MEM_RW:
			user_cmd.inum = std::stoi(user_cmd.str.c_str());
			break;

		default:
			break;
		}
	}
}
