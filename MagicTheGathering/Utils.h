#pragma once

struct Player {
	char name[128]{};
	int id = -1;

	Player() = default;
	Player(const char* name, size_t id) {
		if (*name == '\0') {
			throw std::invalid_argument("name cannot be empty");
		}

		strcpy_s(this->name, name);
		this->id = id;
	}
};

enum class Command {
	cp,

	commandsCount
};

void getPlayerName(char* buffer, size_t bufferSize);