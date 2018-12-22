#include "ChainHashing.h"
#include "ChainHashingOnStdList.h"
#include "DoubleHashing.h"

#include <ctime>
#include <vector>


size_t GenerateRandomNumber(std::mt19937& generator)
{
	std::uniform_int_distribution<size_t> distribution(0, 40000);
	return distribution(generator);
}


int main()
{
	std::random_device random_device;
	std::mt19937 generator(random_device());
	

	int size = 200;
	int data_count = 10000;
	std::vector<int> TestVector(data_count);

	// Обычный метод цепочек
	
	ChainHashing ChainHashingTable(10000, 5);
	
	for (int i = 0; i < data_count; i++)
	{
		TestVector[i] = GenerateRandomNumber(generator);
	}


	for (int i = 0; i < data_count; i++)
	{
		ChainHashingTable.Place(Node(TestVector[i], -1));
	}

	std::cout << "Chain hashing :" << std::endl;

	if (data_count < 31)
	{
		ChainHashingTable.Print();
	}

	std::cout << std::endl;


	// Метод Цепочек на std::list
	ChainHashingOnStdList ChainHashingOnStdListTable(10000, 5);

	for (int i = 0; i < data_count; i++)
	{
		TestVector[i] = GenerateRandomNumber(generator);
	}

	for (int i = 0; i < data_count; i++)
	{
		ChainHashingOnStdListTable.InsertItem(TestVector[i]);
	}

	std::cout << "Chain hashing on std::list :" << std::endl;

	if (data_count < 31)
	{
		ChainHashingOnStdListTable.Print();
	}

	ChainHashingOnStdListTable.RemoveItem(12);

	std::cout << std::endl;

	if (ChainHashingOnStdListTable.FindItem(4))
	{
		std::cout << "YES" << std::endl;
	}

	std::cout << std::endl;

	// Двойное хеширование

	DoubleHash DoubleHashingTable(10000, 5);

	for (int i = 0; i < data_count; i++)
	{
		TestVector[i] = GenerateRandomNumber(generator);
	}

	for (int i = 0; i < data_count; i++)
	{
		DoubleHashingTable.InsertItem(TestVector[i]);
	}

	std::cout << "Double Hashing :" << std::endl;

	if (data_count < 101)
	{
		DoubleHashingTable.Print();
	} 

	
	return 0;
}