#include "Players.h"

#include <fstream>
#include <cassert>

Players::Players(const char* fileName)
{
	if (fileName == nullptr || *fileName == '\0') {
		throw std::invalid_argument("file name is not valid");
	}

	this->fileName = new char[strlen(fileName) + 1];
	strcpy_s(this->fileName, strlen(fileName) + 1, fileName);

	readPlayers();
}

Players::Players(const Players& other) {
	copyFrom(other);
}

Players& Players::operator=(const Players& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Players::~Players() {
	writePlayers();
	free();
}

const Player* Players::getPlayers() const {
	return players;
}

size_t Players::getPlayersCount() const {
	return size;
}

void Players::printPlayers() const {
	for (int i = 0; i < size; i++) {
		std::cout << players[i].name << '\n';
	}
	std::cout << std::endl;
}

void Players::addPlayer(const Player& player) {
	if (size == capacity) {
		resize();
	}

	players[size++] = player;
}

void Players::writePlayersToFile(const char* fileName) {
	std::ofstream ofile(fileName);
	if (!ofile.is_open()) {
		throw std::exception("file could not be opened");
	}

	for (int i = 0; i < size; i++) {
		ofile << players[i].id << ", " << players[i].name << '\n';
	}

	ofile.close();
}

void Players::readPlayers() {
	std::ifstream ifile(fileName, std::ios::binary);
	if (!ifile.is_open()) {
		return;
	}

	ifile.read(reinterpret_cast<char*>(&size), sizeof(size));
	capacity = size < 8 ? 8 : size;
	players = new Player[capacity];
	ifile.read(reinterpret_cast<char*>(players), static_cast<long long>(size) * sizeof(Player));

	ifile.close();
}

void Players::writePlayers() {
	std::ofstream ofile(fileName, std::ios::binary);
	if (!ofile.is_open()) {
		throw std::exception("file could not be opened");
	}

	ofile.write(reinterpret_cast<const char*>(&size), sizeof(size));
	ofile.write(reinterpret_cast<const char*>(players), static_cast<long long>(size) * sizeof(Player));

	ofile.close();
}

void Players::resize() {
	size_t newCapacity = capacity < 8 ? 8 : capacity * 2;
	Player* newPlayers = new Player[newCapacity];
	for (int i = 0; i < size; i++) {
		newPlayers[i] = players[i];
	}

	delete[] players;
	players = newPlayers;
	capacity = newCapacity;
}

void Players::free() {
	delete[] players;
	players = nullptr;
	size = capacity = 0;
	delete[] fileName;
	fileName = nullptr;
}

void Players::copyFrom(const Players& other) {
	if (other.capacity > 0) {
		players = new Player[other.capacity];
		assert(other.size <= other.capacity);
		for (int i = 0; i < other.size; i++) {
			players[i] = other.players[i];
		}

		size = other.size;
		capacity = other.capacity;
	}

	fileName = new char[strlen(other.fileName) + 1];
	strcpy_s(fileName, strlen(other.fileName) + 1, other.fileName);
}
