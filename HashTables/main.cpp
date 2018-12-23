#include "ChainHashing.h"
#include "ChainHashingOnStdList.h"
#include "DoubleHashing.h"
#include "CuckooHashing.h"

#include <ctime>
#include <vector>


size_t GenerateRandomNumber(std::mt19937& generator)
{
	std::uniform_int_distribution<size_t> distribution(0, 1000);
	return distribution(generator);
}

void MainCuckoo(std::vector<int> key, int size, int n, CuckooHash* &hf)
{
	bool flag;
	for (int i = 0, cnt = 0; i < size; i++)
	{
		flag = hf->InsertItemIterative(key[i], 0, cnt, n);
		if (flag == false)
		{
			hf->ReHash();
			i = -1;
		}
	}
}

int main()
{
	std::mt19937 gen(time(0));
	std::normal_distribution<> dist(30, 4);
	std::random_device random_device;
	std::mt19937 generator(random_device());
	

	int size = 10;
	int data_count = 10;
	std::vector<int> TestVector(data_count);
	int n = floor(3 * log(size));

	for (int i = 0; i < data_count; i++)
	{
		TestVector[i] = GenerateRandomNumber(generator);
	}

	/* // Обычный метод цепочек
	
	ChainHashing ChainHashingTable(10000, 5);

	for (int i = 0; i < data_count; i++)
	{
		ChainHashingTable.Place(Node(TestVector[i], -1));
	}

	std::cout << "Chain hashing :" << std::endl;

	if (data_count < 101)
	{
		ChainHashingTable.Print();
	}

	std::cout << std::endl; */


	 // Метод Цепочек на std::list
	/*ChainHashingOnStdList ChainHashingOnStdListTable(10000, 5);

	for (int i = 0; i < data_count; i++)
	{
		TestVector[i] = GenerateRandomNumber(generator);
	}

	// Вставка
	for (int i = 0; i < data_count; i++)
	{
		ChainHashingOnStdListTable.InsertItem(TestVector[i]);
	}

	std::cout << "Chain hashing on std::list :" << std::endl;

	if (data_count < 101)
	{
		ChainHashingOnStdListTable.Print();
	}


	// Поиск
	for (int i = 0; i < data_count; i++)
	{
		ChainHashingOnStdListTable.FindItem(TestVector[i]);
	}

	// Удаление
	for (int i = 0; i < data_count; i++)
	{
		ChainHashingOnStdListTable.RemoveItem(TestVector[i]);
	}

	std::cout << std::endl;

	if (data_count < 101)
	{
		ChainHashingOnStdListTable.Print();
	} */

	/*// Двойное хеширование

	DoubleHash DoubleHashingTable(10000, 5);

	for (int i = 0; i < data_count; i++)
	{
		TestVector[i] = GenerateRandomNumber(generator);
	}

	// Вставка
	for (int i = 0; i < data_count; i++)
	{
		DoubleHashingTable.InsertItem(TestVector[i]);
	}

	std::cout << "Double Hashing :" << std::endl;

	
	std::cout << std::endl;
	
	// Поиск

	for (int i = 0; i < data_count; i++)
	{
		DoubleHashingTable.FindItem(TestVector[i]);
	}

	if (data_count < 101)
	{
		DoubleHashingTable.Print();
	}  

	// Удаление

	for (int i = 0; i < data_count; i++)
	{
		DoubleHashingTable.RemoveItem(TestVector[i]);
	}

	std::cout << std::endl;

	if (data_count < 101)
	{
		DoubleHashingTable.Print();
	} */

	// Метод Кукушки

	CuckooHash *CuckooHashingTable;
	CuckooHashingTable = new CuckooHash(5, size);

	MainCuckoo(TestVector, data_count, n, CuckooHashingTable);

	// Вставка
	for (int i = 0; i < data_count; i++) 
	{
		CuckooHashingTable->InsertItemIterative(TestVector[i], 0, 0, n);
	}

	if (data_count < 101)
	{
		CuckooHashingTable->Print();
	}

	// Поиск

	for (int i = 0; i < data_count; i++)
	{
		CuckooHashingTable->FindItem(TestVector[i]);
	}

	// Удаление

	for (int i = 0; i < data_count; i++)
	{
		CuckooHashingTable->DeleteItem(TestVector[i]);
	}

	if (data_count < 101)
	{
		CuckooHashingTable->Print();
	}

	std::cout << std::endl; 
	
	
	return 0;
}