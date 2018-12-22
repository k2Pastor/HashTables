#include "ChainHashing.h"
#include <iostream>
#include <ctime>
#include <vector>


size_t GenerateRandomNumber(std::mt19937& generator)
{
	std::uniform_int_distribution<size_t> distribution(0, 100);
	return distribution(generator);
}


int main()
{
	std::random_device random_device;
	std::mt19937 generator(random_device());
	

	int size = 200;
	int data_count = 50000;
	std::vector<int> ChainHashingVector(data_count);
	ChainHashing ChainHashingTable(1000, 5);
	
	for (int i = 0; i < data_count; i++)
	{
		ChainHashingVector[i] = GenerateRandomNumber(generator);
	}


	for (int i = 0; i < data_count; i++)
	{
		ChainHashingTable.Place(Node(ChainHashingVector[i], -1));
	}

	if (data_count < 31)
	{
		ChainHashingTable.Print();
	}
	
	return 0;
}