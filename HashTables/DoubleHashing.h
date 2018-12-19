#pragma once

#include <iostream>

const int table_size = 100;

class DoubleHash
{
	int *hash_table;
	int current_size;
	bool *isDeleted;

public:

	// Constructor:

	DoubleHash();

	// Destructor:

	~DoubleHash()
	{
		delete[] hash_table;
	}
	// Hash-functions:

	int hash_function1(int key)
	{
		return ((key % (table_size - 1)) % (table_size));
	}

	int hash_function2(int key)
	{
		return ((table_size - 1) - (key % (table_size - 1)));
	}

	// Operations: 

	void insert(int key);
	int search(int key);
	void remove(int key);


	// Other:

	bool isFull()
	{
		return (current_size == table_size);
	}

	int get_current_size()
	{
		return current_size;
	}

	void reHash()
	{
		auto old_hash_table = hash_table;
	}

	// Output:

	friend std::ostream& operator << (std::ostream& os, const DoubleHash& dh);

};












