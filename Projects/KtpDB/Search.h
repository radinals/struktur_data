#pragma once

#include "Database.h"
#include "Prompt.h"

#include <cstddef>
#include <list>

size_t sequential_search(const UserCmd& cmd, size_t start = 0);
std::list<size_t> sequential_search_all(const UserCmd& cmd);
