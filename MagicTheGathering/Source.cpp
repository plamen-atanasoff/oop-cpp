#include <iostream>

#include "Controller.h"
#include "Utils.h"

constexpr size_t BUFFER_SIZE = 1024;
constexpr const char* FILE_NAME = "data.dat";
Command getCommand(const char* command);

int main() {
	Controller ctr(FILE_NAME);

	char command[BUFFER_SIZE]{};
	try {
		while (true) {
			std::cin.getline(command, BUFFER_SIZE);

			if (strcmp(command, "exit") == 0) {
				break;
			}

			ctr.execute(getCommand(command));
		}
	}
	catch (std::invalid_argument& e) {
		std::cout << e.what() << std::endl;

		return 1;
	}
}

Command getCommand(const char* command) {
	if (strcmp(command, "cp") == 0) {
		return Command::cp;
	}
	else {
		throw std::invalid_argument("unknown enumerator name");
	}
}