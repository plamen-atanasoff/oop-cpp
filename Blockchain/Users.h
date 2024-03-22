#pragma once

struct User {
	unsigned id;
	char name[128];
};

struct UsersCollection
{
	User* users;
	unsigned int usersCount;
	unsigned int idCounter;

	UsersCollection()
	{
		users = nullptr;
		usersCount = 0;
		idCounter = 0;
	}

	~UsersCollection()
	{
		delete[] users;
	}

	void createUser(const char* userName);
	void removeUser(const char* name);
	int getUserIndex(const char* name) const;
	bool userNameIsUnique(const char* userName) const;
	void printUsers() const;
	void readFileUsers();
	void writeUserToBinaryFile() const;
	void writeUsersToBinaryFile() const;

	int getUserId(const char* name) const;
	void getUserName(char* userName, unsigned int id) const;
};
