#pragma once
#include <iostream>
#include <random>

class HashFunction {
protected:

	int hash_function(int key, int flag, int _max_table_size, int* &k_independent_functions1, int* &k_independent_functions2, uint64_t _p, int k)
	{
		switch (flag)
		{
		case 1:
		{
			long long int position = 0;
			long long int result = 0, x = 1;

			for (int i = 0; i < k; i++)
			{
				result += k_independent_functions1[i] * x;
				x *= key;
			}

			int moduloP = result % _p;
			int moduloM = moduloP % _max_table_size;

			return moduloM;
		}
		case 2:
		{
			long long int position = 0;
			long long int result = 0, x = 1;

			for (int i = 0; i < k; i++)
			{
				result += k_independent_functions2[i] * x;
				x *= key;
			}

			int moduloP = result % _p;
			int moduloM = moduloP % _max_table_size;

			return moduloM;
		}

		}
	}
};
class CuckooHash : public HashFunction{
protected:
	int data_count, rehash_count, max_table_size, current;
	int **hash_table;
	int pos[2]; // Array to store possible positions for a key 
	int k;
	int* k_independent_hash_functions1;
	int* k_independent_hash_functions2;
	const uint64_t p = 2305843009213693951L;
	
public:
	
	CuckooHash(int _k = 2, int _max_table_size = 500)
	{
		std::random_device random_device;
		std::mt19937 generator(random_device());
		k = _k;
		data_count = 0;
		rehash_count = 0;
		hash_table = new int*[2];
		hash_table[0] = new int[_max_table_size];
		hash_table[1] = new int[_max_table_size];
		max_table_size = _max_table_size;

		k_independent_hash_functions1 = new int[k];
		k_independent_hash_functions2 = new int[k];

		k_independent_hash_functions1[0] = (GenerateRandomNumber(generator) % p) + 1;
		k_independent_hash_functions2[0] = (GenerateRandomNumber(generator) % p) + 1;

		for (int i = 1; i < k; i++)
		{
			k_independent_hash_functions1[i] = (GenerateRandomNumber(generator) % p);
			k_independent_hash_functions2[i] = (GenerateRandomNumber(generator) % p);
		}

		for (int i = 0; i < max_table_size; i++)
		{
			hash_table[0][i] = -1;
			hash_table[1][i] = -1;
		}

	}

	~CuckooHash()
	{
		delete[] hash_table[0];
		delete[] hash_table[1];
		delete hash_table;
		delete[] k_independent_hash_functions1;
		delete[] k_independent_hash_functions2;
	}

	size_t GenerateRandomNumber(std::mt19937& generator)
	{
		std::uniform_int_distribution<size_t> distribution(0, (p - 1));
		return distribution(generator);
	}

	

	void Clear()
	{
		delete[] hash_table[0];
		delete[] hash_table[1];
		delete hash_table;

		hash_table = new int*[2];
		hash_table[0] = new int[max_table_size];
		hash_table[1] = new int[max_table_size];

		for (int i = 0; i < max_table_size; i++)
		{
			hash_table[0][i] = -1;
			hash_table[1][i] = -1;
		}

		data_count = 0;
		current = 0;
	}

	void ReHash()
	{
		std::random_device random_device;
		std::mt19937 generator(random_device());

		data_count = 0;
		delete[] hash_table[0];
		delete[] hash_table[1];
		delete hash_table;

		hash_table = new int*[2];
		hash_table[0] = new int[max_table_size];
		hash_table[1] = new int[max_table_size];

		k_independent_hash_functions1[0] = (GenerateRandomNumber(generator) % p) + 1;
		k_independent_hash_functions2[0] = (GenerateRandomNumber(generator) % p) + 1;

		for (int i = 1; i < k; i++)
		{
			k_independent_hash_functions1[i] = (GenerateRandomNumber(generator) % p);
			k_independent_hash_functions2[i] = (GenerateRandomNumber(generator) % p);
		}

		for (int i = 0; i < max_table_size; i++)
		{
			hash_table[0][i] = -1;
			hash_table[1][i] = -1;
		}
	}

	
	int FindItem(int key)
	{
		pos[0] = (this->hash_function(key, 1, max_table_size, k_independent_hash_functions1, k_independent_hash_functions2, p, k)) % max_table_size;
		pos[1] = (this->hash_function(key, 2, max_table_size, k_independent_hash_functions1, k_independent_hash_functions2, p, k)) % max_table_size;

		if(hash_table[0][pos[0]] == key)
		{
			return pos[0];
		}
		else if (hash_table[1][pos[1]] == key)
		{
			return pos[1];
		}
		else {
			return -1;
		}
		
	}
	
	void DeleteItem(int key)
	{
		int index = FindItem(key);
		if (index == -1)
		{
			return;
		}
		else {
			if (hash_table[0][index] == key)
			{
				hash_table[0][index] = -1;
				data_count--;
			}
			else if (hash_table[1][index] == key)
			{
				hash_table[1][index] = -1;
				data_count--;
			}
		}
	} 

	

	bool InsertItemIterative(int key, int table_identificator, int flag, int n)
	{
		bool f;
		pos[0] = abs((this->hash_function(key, 1, max_table_size, k_independent_hash_functions1, k_independent_hash_functions2, p, k))) % max_table_size;
		pos[1] = abs((this->hash_function(key, 2, max_table_size, k_independent_hash_functions1, k_independent_hash_functions2, p, k))) % max_table_size;

		if (hash_table[0][pos[0]] == key || hash_table[1][pos[1]] == key)
		{
			return true;
		}

		if (hash_table[table_identificator][pos[table_identificator]] != -1)
		{
			while (true)
			{
				if (flag == n)
				{
					ReHash();
					rehash_count++;
					return false;
				}

				if (flag == 0)
				{
					data_count++;
				}

				int tmp = hash_table[table_identificator][pos[table_identificator]];
				hash_table[table_identificator][pos[table_identificator]] = key;
				table_identificator = (table_identificator + 1) % 2;
				pos[0] = abs((this->hash_function(tmp, 1, max_table_size, k_independent_hash_functions1, k_independent_hash_functions2, p, k))) % max_table_size;
				pos[1] = abs((this->hash_function(tmp, 2, max_table_size, k_independent_hash_functions1, k_independent_hash_functions2, p, k))) % max_table_size;

				if (hash_table[table_identificator][pos[table_identificator]] == -1)
				{
					hash_table[table_identificator][pos[table_identificator]] = tmp;
					break;
				}

				key = tmp;
				flag++;
			}
		}
		else {
			hash_table[table_identificator][pos[table_identificator]] = key;
			data_count++;
			return true;
		}
		
	}
		

	int get_rehash_count()
	{
		return rehash_count;
	}

	int get_data_count()
	{
		return data_count;
	}

	int GetValueInFirstTable(int pos)
	{
		return hash_table[0][pos];
	}

	int GetValueInSecondTable(int pos) 
	{
		return hash_table[1][pos];
	}

	void Print() {
		std::cout << "--------------TABLE 1----------------TABLE2------------" << '\n';
		for (int i = 0; i < max_table_size; i++)
		{
			int tmp = GetValueInFirstTable(i);
			std::cout << i << '\t' <<(hash_table[0][i]) << '\t' << hash_table[1][i] << '\n';
		}
		std::cout << "--------------------------------------------------------";
	}

};