#include "DoubleHashing.h"

DoubleHash::DoubleHash()
{
	hash_table = new int[table_size];
	isDeleted = new bool[table_size];
	current_size = 0;

	for (int i = 0; i < table_size; i++)
	{
		hash_table[i] = -1;
		isDeleted[i] = true;
	}
}

void DoubleHash::insert(int key)
{
	if (isFull())
	{
		return;
	}

	int index = hash_function1(key);

	
	if (hash_table[index] != -1)
	{
		int index1 = hash_function2(key);
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
		}
	}
	else {
		hash_table[index] = key;
		isDeleted[index] = false;
		current_size++;
	}

}

int DoubleHash::search(int key)
{
	int x = hash_function1(key); // x == index
	int y = hash_function2(key);

	for (int i = 0; i < table_size; i++)
	{
		if ((hash_table[x] != -1) && (!isDeleted[x]))
		{
			if (hash_table[x] == key)
			{
				return x;
			}
		}

		x = (x + y) % 10;

	}

	return -1;
}

void DoubleHash::remove(int key)
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

		x = (x + y) % 10;

	}

}

std::ostream & operator<<(std::ostream & os, const DoubleHash & dh)
{
	for (int i = 0; i < table_size; i++)
	{
		if ((dh.hash_table[i] != -1) && (!dh.isDeleted[i]))
		{
			os << i << " ---> " << dh.hash_table[i] << std::endl;
		}
		else {

			os << i << std::endl;
		}
	}

	return os;
}






