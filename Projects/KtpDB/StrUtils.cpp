#include "StrUtils.h"
#include <cctype>

std::list<std::string>
split_str(const std::string& str, const char delim)
{
	std::list<std::string> splits;
	std::string split;

	for (const char& c : str) {
		if (c != delim) {
			split += c;
		} else {
			splits.push_back(split);
			split = "";
		}
	}

	splits.push_back(split);

	return splits;
}

bool
str_is_all_digit(const std::string& str)
{
	for (const char& chr : str)
		if (!isdigit(chr))
			return false;
	return true;
}

void
remove_all_char(std::string& str, char ch)
{
	std::string tmp = str;
	str = "";

	for (size_t i = 0; i < tmp.size(); ++i)
		if (tmp[i] != ch)
			str += tmp[i];
}
