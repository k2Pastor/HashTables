#pragma once
#include "MyList.h"
#include <random>
#include <list>
#include <iterator>

 class ChainHashing {

public:
	MyList* mylist;
	int table_size;
	int current_size;
	int* k_independent_hash_functions;
	int k;
	const uint64_t p = 2305843009213693951L;
	

	ChainHashing(int _table_size, int _k)
	{
		
		std::random_device random_device;
		std::mt19937 generator(random_device());
		current_size = 0;
		table_size = _table_size;
		mylist = new MyList[table_size];
		k = _k;
		k_independent_hash_functions = new int[k];

		k_independent_hash_functions[0] =  (GenerateRandomNumber(generator) % p) + 1;
		
		for (int i = 1; i < k; i++)
		{
			k_independent_hash_functions[i] = (GenerateRandomNumber(generator) % p);
		}
		

	}

	size_t GenerateRandomNumber(std::mt19937& generator)
	{
		std::uniform_int_distribution<size_t> distribution(0,(p - 1));
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

	void Place(Node op)
	{
		int index = abs(hash_function(op.key));

		bool already_inserted = mylist[index].Find(op.key);

		if (already_inserted == true)
		{
			return ;
		} 

		mylist[index].Push(op);
		current_size++;
	}

	void Print()
	{
		for (int i = 0; i < table_size; i++)
		{
			std::cout << i;

			if (mylist[i].size == 0)
			{
				std::cout << "-";
			}
			else
			{

				Node *cur = mylist[i].Root;
				for (int j = 0; j < mylist[i].size; j++)
				{
					std::cout << " --> " << cur->key;
					cur = cur->next;
				}
			}
			std::cout << std::endl;
		} 
	}
};