#include "ChainHashing.h"

void ChainHash::insert(int key)
{
	int index = hash_function(key);
	hash_table[index].push_back(key);
}

void ChainHash::remove(int key)
{
	int index = hash_function(key);

	std::list<int>::iterator it;

	for (it = hash_table[index].begin(); it != hash_table[index].end(); it++)
	{
		if (*it == key)
		{
			break;
		}
	}

	if (it != hash_table[index].end())
	{
		hash_table[index].erase(it);
	}
}

std::ostream & operator<<(std::ostream & os, const ChainHash & ch)
{
	for (int i = 0; i < ch.bucket; i++)
	{
		os << i;
		for (auto x : ch.hash_table[i])
		{
			os << " ---> " << x;
		}

		os << std::endl;
	}
	return os;
}
