#include "Controller.h"

#include "Utils.h"
#include "Players.h"

Controller::Controller(const char* fileName) : players(PLAYERS_FILE_NAME) {
	if (fileName == nullptr || *fileName == '\0' || strlen(fileName) >= FILE_NAME_MAX_SIZE) {
		throw std::invalid_argument("file name is not valid");
	}

	strcpy_s(this->fileName, FILE_NAME_MAX_SIZE, fileName);

	std::ifstream ifile(fileName, std::ios::binary);
	if (!ifile.is_open()) {
		return;
	}

	ifile.read(reinterpret_cast<char*>(&idGenerator), sizeof(idGenerator));

	ifile.close();

	players.printPlayers();
}

Controller::~Controller() {
	std::ofstream ofile(fileName, std::ios::binary);
	if (!ofile.is_open()) {
		return;
	}

	ofile.write(reinterpret_cast<const char*>(&idGenerator), sizeof(idGenerator));

	ofile.close();
}

void Controller::execute(Command command) {
	char buffer[1024];
	switch (command) {
	case Command::cp: {
		getPlayerName(buffer, 1024);
		Player player(buffer, idGenerator++);

		players.addPlayer(player);
		players.printPlayers();
	}

	}
}

void getPlayerName(char* buffer, size_t bufferSize) {
	do {
		std::cout << "Enter player name: ";
		std::cin.getline(buffer, bufferSize);
	} while (*buffer == '\0');
}