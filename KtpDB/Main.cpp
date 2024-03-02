#include "Database.h"
#include "ExecCommand.h"
#include "Prompt.h"

#include <iostream>
#include <stdexcept>

DataKtp* Database = nullptr;
size_t DatabaseSize;
size_t DatabaseLen;

int
main()
{
	init_database();

	while (true) {
		UserCmd cmd;
		try {
			std::cout << "\n";
			cmd = prompt_user();
			std::cout << "\n";
		} catch (std::invalid_argument) {
			std::cout << "ERROR: Perintah Invalid!\n";
			continue;
		}
		exec_cmd(&cmd);
	}

	return 0;
}
