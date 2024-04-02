#pragma once

#include <fstream>

#include "Utils.h"
#include "Players.h"

class Controller {
public:
	Controller(const char* fileName);
	~Controller();

	void execute(Command command);
private:
	Players players;
	int idGenerator = 0;
	char fileName[32]{};

	static constexpr const char* PLAYERS_FILE_NAME = "players.dat";
	static constexpr const char* CARDS_FILE_NAME = "cards.dat";
	static constexpr const char* DECKS_FILE_NAME = "decks.dat";

	static constexpr int FILE_NAME_MAX_SIZE = 32;
};