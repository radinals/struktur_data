#pragma once

#include "DataKtp.h"
#include "Prompt.h"

#include <list>

#define _BASESIZE 10

extern DataKtp* Database;
extern size_t DatabaseSize;
extern size_t DatabaseLen;

void add_new(const DataKtp& dataktp);
void input_new_data();

void delete_at(size_t index);
DataKtp* data_at(size_t index);

void init_database();
void grow_database();
void shrink_database(size_t mod);
void set_database_size(size_t size);

void edit_data_at(MemberName member, size_t index);
void check_database_size();
