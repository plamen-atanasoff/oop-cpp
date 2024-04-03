#pragma once

#include <iostream>

#include "Utils.h"

class Players {
public:
	Players(const char* fileName);
	Players(const Players& other);
	Players& operator=(const Players& other);
	~Players();

	const Player* getPlayers() const;
	size_t getPlayersCount() const;
	void printPlayers() const;

	void addPlayer(const Player& player);
	void writePlayersToFile(const char* fileName);
private:
	void readPlayers();
	void writePlayers();
	void resize();
	void free();
	void copyFrom(const Players& other);

	Player* players = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	char* fileName = nullptr;
};