#pragma once

#include <string>

typedef enum {
	CMDTYPE_List,
	CMDTYPE_Search,
	CMDTYPE_Delete,
	CMDTYPE_Modify,
	CMDTYPE_Add,
	CMDTYPE_Quit,
	CMDTYPE_Help,
} CommandType;

typedef enum {
	Target_None,
	Target_member,
	Target_index,
} CmdTargetType;

typedef enum {
	MEM_NIK,
	MEM_Nama,
	MEM_TempatLahir,
	MEM_TanggalLahir,
	MEM_Kelamin,
	MEM_Alamat,
	MEM_RT,
	MEM_RW,
	MEM_KelurahanDesa,
	MEM_Kecamatan,
	MEM_Agama,
	MEM_SudahKawin,
	MEM_BelumKawin,
	MEM_Pekerjaan,
	MEM_Kewarganegaraan,
} MemberName;

typedef enum {
	CS_All,
	CS_First,
} CmdScope;

typedef struct UserCmd {
	CommandType type;
	CmdScope scope;
	CmdTargetType target_type;
	std::string id;
	MemberName member;
	std::string str;
	long int lnum;
	int inum;
} UserCmd;
