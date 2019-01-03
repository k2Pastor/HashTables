#include "ChainHashing.h"
#include "ChainHashingOnStdList.h"
#include "DoubleHashing.h"
#include "CuckooHashing.h"

#include <ctime>
#include <vector>
#include <chrono>


size_t GenerateRandomNumber(std::mt19937& generator)
{
	std::normal_distribution<double> distribution(0, 75000);
	return static_cast<size_t>(distribution(generator));
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
	std::ios::sync_with_stdio(false);
	std::mt19937 gen(time(0));
	
	std::random_device random_device;
	std::mt19937 generator(random_device());
	

	int size = 500000;
	int data_count = 500000;
	std::vector<int> TestVector(data_count);
	int n = floor(3 * log(size));

	for (int i = 0; i < data_count; i++)
	{
		TestVector[i] = GenerateRandomNumber(generator);
	}

	 // Обычный метод цепочек
	
/*	ChainHashing ChainHashingTable(500000, 5);

	auto start = std::chrono::steady_clock::now();
	for (int i = 0; i < data_count; i++)
	{
		ChainHashingTable.Place(Node(TestVector[i], -1));
	}
	auto end = std::chrono::steady_clock::now();
	std::cout << "Chain hashing :" << std::chrono::duration<double, std::milli>(end - start).count() << ";";
	std::cout << std::endl;

	if (data_count < 101)
	{
		ChainHashingTable.Print();
	}

	std::cout << std::endl;


	 // Метод Цепочек на std::list
	ChainHashingOnStdList ChainHashingOnStdListTable(500000, 5);

	for (int i = 0; i < data_count; i++)
	{
		TestVector[i] = GenerateRandomNumber(generator);
	}

	// Вставка
	start = std::chrono::steady_clock::now();
	for (int i = 0; i < data_count; i++)
	{
		ChainHashingOnStdListTable.InsertItem(TestVector[i]);
	}
	end = std::chrono::steady_clock::now();
	std::cout << "Chain hashing on std::list: "<< std::chrono::duration<double, std::milli>(end - start).count() << ";";

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
	}  
	//std::cout << "SAASAT" << std::endl; */
	// Двойное хеширование

	DoubleHash DoubleHashingTable(1000000, 5);
	//std::cout << "SAASAT11" << std::endl;

	// Вставка
	auto start = std::chrono::steady_clock::now();
	for (int i = 0; i < data_count; i++)
	{
		//if (i % 1000 == 0) {
			//std::cout << i << std::endl;

		//}
		DoubleHashingTable.InsertItem(TestVector[i]);
	}
	//std::cout << "SAASAT234" << std::endl;

	auto end = std::chrono::steady_clock::now();
	std::cout << "Double hashing: " << std::chrono::duration<double, std::milli>(end - start).count() << ";";

	 // Поиск

	for (int i = 0; i < data_count; i++)
	{
		DoubleHashingTable.FindItem(TestVector[i]);
	}

	if (data_count < 31)
	{
		DoubleHashingTable.Print();
	}  

	// Удаление

	for (int i = 0; i < data_count; i++)
	{
		DoubleHashingTable.RemoveItem(TestVector[i]);
	}

	std::cout << std::endl;

	if (data_count < 31)
	{
		DoubleHashingTable.Print();
	} 

	// Метод Кукушки

/*	CuckooHash *CuckooHashingTable;
	CuckooHashingTable = new CuckooHash(5, size);

	MainCuckoo(TestVector, data_count, n, CuckooHashingTable);

	// Вставка
	start = std::chrono::steady_clock::now();
	for (int i = 0; i < data_count; i++) 
	{
		CuckooHashingTable->InsertItemIterative(TestVector[i], 0, 0, n);
	}
	end = std::chrono::steady_clock::now();
	std::cout << std::endl;
	std::cout << "Cuckoo hashing: " << std::chrono::duration<double, std::milli>(end - start).count() << ";";
	
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

	std::cout << std::endl;  */
	
	
	return 0;
}