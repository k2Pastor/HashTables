#pragma once

#include <iostream>

#define table_size 17
#define prime 7 // простое число, которое должно быть меньше table_size


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
		return (key % table_size);
	}

	int hash_function2(int key)
	{
		return (prime - (key % prime));
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

	// Output:

	friend std::ostream& operator << (std::ostream& os, const DoubleHash& dh);

};