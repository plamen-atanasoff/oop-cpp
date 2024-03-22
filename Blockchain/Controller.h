#pragma once

#include "Users.h"
#include "TBlocks.h"
#include "Coins.h"

struct Controller
{
	UsersCollection* uCollection;
	TBlocksCollection* tCollection;
	CoinsCollection* cCollection;

	Controller()
	{
		uCollection = new UsersCollection();
		tCollection = new TBlocksCollection();
		cCollection = new CoinsCollection();

		readMetaDataFile();
		tCollection->readFileTBlocks();
		readFileUsers();

		readUsersCoins(uCollection->users, uCollection->usersCount);
		readTBlocksCoins(tCollection->tBlocks, tCollection->tBlocksCount);
	}

	~Controller()
	{
		writeMetaDataFile();
		tCollection->writeFileTBlocks();

		delete uCollection;
		delete tCollection;
		delete cCollection;
	}

	void createUser(const char* userName, double investmentSum);
	void removeUser(const char* name);
	void readFileUsers();
	void makeTransaction(const char* senderName, const char* receiverName, double coinsToSend);

	void sendCoins(const char* senderName, const char* receiverName, double coins);
	void readMetaDataFile();
	void writeMetaDataFile() const;

	void readUsersCoins(User* users, unsigned int usersCount);
	void readTBlocksCoins(TransactionBlock* tBlocks, unsigned int tBlocksCount);

	void writeRichestUsers();
	void writeBiggestBlocks();

	void convertTimeToChar(char fileName[]);
	void reverseCharArray(char arr[], int size);
};
