#pragma once

#include <iostream>
#include <list>
#include <iterator>

class ChainHash
{
	int bucket; // ¹ of bucket
	std::list<int>* hash_table;

public:
	// Constructor:
	ChainHash(int _bucket)
	{
		bucket = _bucket;
		hash_table = new std::list<int>[bucket];
	}

	// Destructor:
	~ChainHash()
	{
		delete[] hash_table;
	}

	// Hash-functions:
	int hash_function(int x)
	{
		return x % bucket;
	}
	
	// Operations: 
	void insert(int key);
	void remove(int key);

	// Output:
	friend std::ostream& operator << (std::ostream& os, const ChainHash& ch);
};
