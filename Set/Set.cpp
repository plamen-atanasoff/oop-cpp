#include "Set.h"
#include <exception>
#include <iostream>

Set::Set(int n)
{
	if (n < 0) {
		throw std::exception("n is not valid");
	}

	maxEl = n;
	bucketsCount = n / bitsPerBucket + 1;
	buckets = new uint8_t[bucketsCount]{};
}

Set::Set(const Set& other)
{
	copyFrom(other);
}

Set& Set::operator=(const Set& other)
{
	if (this != &other) {
		copyFrom(other);
	}

	return *this;
}

Set::~Set()
{
	free();
}

void Set::add(int n)
{
	if (n < 0 || n > maxEl) {
		throw std::exception("n out of range");
	}

	int ind = getBucketInd(n);
	int pos = getPos(n);

	uint8_t mask = 1 << pos;
	buckets[ind] |= mask;
}

void Set::remove(int n)
{
	if (n < 0 || n > maxEl) {
		throw std::exception("n out of range");
	}

	int ind = getBucketInd(n);
	int pos = getPos(n);

	uint8_t mask = 1 << pos;
	buckets[ind] &= ~mask;
}

bool Set::exists(int n) const
{
	if (n < 0 || n > maxEl) {
		throw std::exception("n out of range");
	}

	int ind = getBucketInd(n);
	int pos = getPos(n);

	uint8_t mask = 1 << pos;

	return buckets[ind] & mask;
}

void Set::print() const
{
	std::cout << "{ ";
	for (int i = 0; i <= maxEl; i++) {
		if (exists(i)) {
			std::cout << i << ' ';
		}
	}
	std::cout << "}" << std::endl;
}

void Set::copyFrom(const Set& other)
{
	uint8_t* newBuckets = new uint8_t[other.bucketsCount]{};
	for (int i = 0; i < other.bucketsCount; i++) {
		newBuckets[i] = other.buckets[i];
	}

	delete[] buckets;
	buckets = newBuckets;
	bucketsCount = other.bucketsCount;
	maxEl = other.maxEl;
}

void Set::free()
{
	delete[] buckets;
	buckets = nullptr;
	bucketsCount = 0;
	maxEl = 0;
}

int Set::getBucketInd(int n) const
{
	return n / bitsPerBucket;
}

int Set::getPos(int n) const
{
	return n % bitsPerBucket;
}

Set setIntersection(const Set& lhs, const Set& rhs)
{
	size_t minBucketsCount = std::min(lhs.bucketsCount, rhs.bucketsCount);
	Set res(lhs.maxEl > rhs.maxEl ? lhs.maxEl : rhs.maxEl);
	for (int i = 0; i < minBucketsCount; i++) {
		res.buckets[i] = lhs.buckets[i] & rhs.buckets[i];
	}

	return res;
}

Set setUnion(const Set& lhs, const Set& rhs)
{
	size_t maxBucketsCount = std::max(lhs.bucketsCount, rhs.bucketsCount);
	size_t minBucketsCount = std::min(lhs.bucketsCount, rhs.bucketsCount);
	Set res(lhs.maxEl > rhs.maxEl ? lhs.maxEl : rhs.maxEl);
	for (int i = 0; i < minBucketsCount; i++) {
		res.buckets[i] = lhs.buckets[i] | rhs.buckets[i];
	}
	const Set& biggerSet = lhs.bucketsCount > rhs.bucketsCount ? lhs : rhs;
	for (int i = minBucketsCount; i < maxBucketsCount; i++) {
		res.buckets[i] = biggerSet.buckets[i];
	}

	return res;
}
