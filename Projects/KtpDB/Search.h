#pragma once

#include "Database.h"
#include "Prompt.h"
#include "vector"

#include <cstddef>

size_t sequential_search(UserCmd* cmd, size_t start = 0);
std::vector<size_t> sequential_search_all(UserCmd* cmd);
