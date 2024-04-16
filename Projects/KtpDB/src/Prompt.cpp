#include "Prompt.h"

#include "InputParser.h"

#include <iostream>

UserCmd
prompt_user()
{
	UserCmd cmd;
	std::string user_input = "";

	std::cout << "CMD: ";

	getline(std::cin, user_input);

	parse_input(cmd, user_input);

	return cmd;
}
