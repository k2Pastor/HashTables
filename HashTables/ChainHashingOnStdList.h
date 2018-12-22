#pragma once

#include <list>
#include <iterator>
#include <random>
#include <iostream>

class ChainHashingOnStdList{

public:

	std::list<int> *hash_table;
	int table_size;
	int current_size;
	int* k_independent_hash_functions;
	int k;
	const uint64_t p = 2305843009213693951L;


	ChainHashingOnStdList(int _table_size, int _k)
	{

		std::random_device random_device;
		std::mt19937 generator(random_device());
		current_size = 0;
		table_size = _table_size;
		hash_table = new std::list<int>[table_size];
		k = _k;
		k_independent_hash_functions = new int[k];

		k_independent_hash_functions[0] = (GenerateRandomNumber(generator) % p) + 1;

		for (int i = 1; i < k; i++)
		{
			k_independent_hash_functions[i] = (GenerateRandomNumber(generator) % p);
		}


	}

	size_t GenerateRandomNumber(std::mt19937& generator)
	{
		std::uniform_int_distribution<size_t> distribution(0, (p - 1));
		return distribution(generator);
	}

	int hash_function(int key)
	{
		long long int position = 0;
		long long int result = 0, x = 1;

		for (int i = 0; i < k; i++)
		{
			result += k_independent_hash_functions[i] * x;
			x *= key;
		}

		int moduloP = result % p;
		int moduloM = moduloP % table_size;

		return moduloM;
	}

	bool isFull()
	{
		if (current_size == table_size)
		{
			return true;
		}
		else return false;
	}

	bool isEmpty()
	{
		if (current_size == 0)
		{
			return true;
		}
		else return false;
	}

	void InsertItem(int key)
	{
		int index = abs(hash_function(key));
		hash_table[index].push_back(key);

	}

	void RemoveItem(int key)
	{
		int index = abs(hash_function(key));
		std::list <int> ::iterator i;
		for (i = hash_table[index].begin(); i != hash_table[index].end(); i++)
		{
			if (*i == key)
				break;
		}

		if (i != hash_table[index].end())
		{
			hash_table[index].erase(i);
		}
	}

	bool FindItem(int key)
	{
		int index = abs(hash_function(key));
		std::list <int> ::iterator i;
		for (i = hash_table[index].begin(); i != hash_table[index].end(); i++)
		{
			if (*i == key)
				return true;
			else return false;
		}
	}

	void Print()
	{
		for (int i = 0; i < table_size; i++)
		{
			std::cout << i;
			for (auto x : hash_table[i])
				std::cout << " --> " << x;
			std::cout << std::endl;
		}
	}
};