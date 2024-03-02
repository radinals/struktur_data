#pragma once

#include <list>
#include <string>

std::list<std::string> split_str(const std::string& str, const char delim);
bool str_is_all_digit(const std::string& str);
void remove_all_char(std::string& str, char ch);
