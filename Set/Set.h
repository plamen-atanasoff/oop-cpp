#pragma once
#include <cstdint>

class Set {
public:
	Set(int n);
	Set(const Set& other);
	Set& operator=(const Set& other);
	~Set();

	void add(int n);
	void remove(int n);
	bool exists(int n) const;

	void print() const;
private:
	uint8_t* buckets = nullptr;
	size_t bucketsCount = 0;
	int maxEl = 0;
	static constexpr size_t bitsPerBucket = sizeof(uint8_t) * 8;
	
	void copyFrom(const Set& other);
	void free();

	int getBucketInd(int n) const;
	int getPos(int n) const;

	friend Set setIntersection(const Set& lhs, const Set& rhs);
	friend Set setUnion(const Set& lhs, const Set& rhs);
};

Set setIntersection(const Set& lhs, const Set& rhs);
Set setUnion(const Set& lhs, const Set& rhs);