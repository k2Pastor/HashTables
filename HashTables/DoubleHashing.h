#pragma once

#include <iostream>
#include <random>



class DoubleHash
{
	int *hash_table;
	bool *isDeleted;
	int table_size;
	int current_size;
	int* k_independent_hash_functions1;
	int* k_independent_hash_functions2;
	int k;
	const uint64_t p = 2305843009213693951L;
	
	

public:

	

	DoubleHash(int _table_size, int _k)
	{
		std::random_device random_device;
		std::mt19937 generator(random_device());
		table_size = _table_size;
		k = _k;
		hash_table = new int[table_size];
		isDeleted = new bool[table_size];
		current_size = 0;

		for (int i = 0; i < table_size; i++)
		{
			hash_table[i] = -1;
			isDeleted[i] = true;
		}

		k_independent_hash_functions1 = new int[k];
		k_independent_hash_functions2 = new int[k];

		k_independent_hash_functions1[0] = (GenerateRandomNumber(generator) % p) + 1;
		k_independent_hash_functions2[0] = (GenerateRandomNumber(generator) % p) + 1;

		for (int i = 1; i < k; i++)
		{
			k_independent_hash_functions1[i] = (GenerateRandomNumber(generator) % p);
			k_independent_hash_functions2[i] = (GenerateRandomNumber(generator) % p);
		}

	}

	size_t GenerateRandomNumber(std::mt19937& generator)
	{
		std::uniform_int_distribution<size_t> distribution(0, (p - 1));
		return distribution(generator);
	}

	~DoubleHash()
	{
		delete[] hash_table;
		delete[] k_independent_hash_functions1;
		delete[] k_independent_hash_functions2;
	}

	int hash_function1(int key)
	{
		long long int position = 0;
		long long int result = 0, x = 1;

		for (int i = 0; i < k; i++)
		{
			result += k_independent_hash_functions1[i] * x;
			x *= key;
		}

		int moduloP = result % p;
		int moduloM = moduloP % table_size;

		return moduloM;
	}

	int hash_function2(int key)
	{
		long long int position = 0;
		long long int result = 0, x = 1;

		for (int i = 0; i < k; i++)
		{
			result += k_independent_hash_functions2[i] * x;
			x *= key;
		}

		int moduloP = result % p;
		int moduloM = moduloP % table_size;

		return moduloM;
	}

	 void  ReHash()
	{
		int old_table_size = table_size;
		std::random_device random_device;
		std::mt19937 generator(random_device());

		/*if (current_size > (0.6 * table_size))
		{
			table_size *= 2;
		} */

		//current_size = 0;
		
		// Update 
		k_independent_hash_functions1[0] = (GenerateRandomNumber(generator) % p) + 1;
		k_independent_hash_functions2[0] = (GenerateRandomNumber(generator) % p) + 1;

		for (int i = 1; i < k; i++)
		{
			k_independent_hash_functions1[i] = (GenerateRandomNumber(generator) % p);
			k_independent_hash_functions2[i] = (GenerateRandomNumber(generator) % p);
		}
		
		int *old_hash_table = hash_table;
		//hash_table = new int[table_size];

		for (int i = 0; i < old_table_size; i++)
		{
			hash_table[i] = old_hash_table[i];
		}

		

		
	}

	void InsertItem(int key)
	{
		if (isFull())
		{
			return;
		}

		if (FindItem(key))
		{
			return;
		}

		int index = abs(hash_function1(key));

		if (hash_table[index] != -1)
		{
			int index1 = abs(hash_function2(key));
			int i = 1;

			while (1)
			{
				int newIndex = (index + index1 * i) % table_size;

				if (hash_table[newIndex] == -1)
				{
					hash_table[newIndex] = key;
					isDeleted[newIndex] = false;
					current_size++;
					break;
				}
				i++;

				if (i > (table_size * 1,5))
				{
					ReHash();
					index = abs(hash_function1(key));
					index1 = abs(hash_function2(key));
				}
			}
		}
		else {
			hash_table[index] = key;
			isDeleted[index] = false;
			current_size++;
		}
	}


	bool FindItem(int key)
	{
		int x = hash_function1(key); // x == index
		int y = hash_function2(key);

		for (int i = 0; i < table_size; i++)
		{
			if ((hash_table[x] != -1) && (!isDeleted[x]))
			{
				if (hash_table[x] == key)
				{
					return true;
				}
			}

			x = (x + y) % table_size;

		}

		return false;
	}
	void RemoveItem(int key)
	{
		int x = hash_function1(key); // x == index
		int y = hash_function2(key);

		for (int i = 0; i < table_size; i++)
		{
			if ((hash_table[x] != -1) && (!isDeleted[x]))
			{
				if (hash_table[x] == key)
				{
					hash_table[x] = -1;
					isDeleted[x] = true;
					current_size--;
				}
			}

			x = (x + y) % table_size;
		}
	}


	bool isFull()
	{
		if (current_size == table_size)
		{
			return true;
		}
		else return false;
	}

	int get_current_size()
	{
		return current_size;
	}

	void Print()
	{
		for (int i = 0; i < table_size; i++)
		{
			if ((hash_table[i] != -1) && (!isDeleted[i]))
			{
				std::cout << i << " ---> " << hash_table[i] << std::endl;
			}
			else {

				std::cout << i << std::endl;
			}
		}
	}

};