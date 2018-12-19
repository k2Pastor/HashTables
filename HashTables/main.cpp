#include "DoubleHashing.h"
#include "ChainHashing.h"
#include <ctime>
#include <vector>
#include <random>


size_t GenerateRandomNumber(std::mt19937& generator)
{
	std::uniform_int_distribution<size_t> distribution(0, 52224);
	return distribution(generator);
}

int main()
{



	/*double timeStart, timeEnd;
	int size;

	std::cin >> size;
	DoubleHash dh;
	std::vector<int> doubleHashVector(size);

	std::random_device random_device;
	std::mt19937 generator(random_device());

	for (int i = 0; i < size; ++i)
	{
		doubleHashVector[i] = GenerateRandomNumber(generator);
	}

	

	for (int i = 0; i < size; i++)
	{
		dh.insert(doubleHashVector[i]);
	}

	std::cout << dh << std::endl;
	std::cout << dh.search(27) << std::endl;
	std::cout << dh.search(12) << std::endl;

	std::cout << std::endl;

	dh.remove(732);
	std::cout << dh << std::endl;
	std::cout << dh.get_current_size() << std::endl;

	dh.insert(12);
	std::cout << dh << std::endl;
	return 0; 

	/*ChainHash ch(100);
	double timeStart, timeEnd;
	int size;

	std::cin >> size;

	std::vector<int> v1(size);


	for (int i = 0; i < size; i++)
	{
		v1[i] = rand() % 100;
	}


	for (int i = 0; i < size; i++)
	{
		ch.insert(v1[i]);
	}

	timeStart = clock();
	ch.remove(12);
	timeEnd = clock();

	std::cout.precision(9);
	std::cout << ch << std::endl;
	std::cout << "Time of algorithm is: " << std::fixed << (timeEnd - timeStart) / CLOCKS_PER_SEC << std::endl; */

}