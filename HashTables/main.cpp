#include "DoubleHashing.h"
#include "ChainHashing.h"
#include <ctime>



int main()
{
	/*DoubleHash dh;
	int array[] = { 19, 27, 36, 732, 64,6,56,23,7,8,34,2,68,123,732,4,543 };
	int size = sizeof(array) / sizeof(array[0]);

	for (int i = 0; i < size; i++)
	{
	dh.insert(array[i]);
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
	return 0; */

	ChainHash ch(7);
	int array[] = { 15, 11, 27, 8, 12 };
	int size = sizeof(array) / sizeof(array[0]);
	double timeStart, timeEnd;

	for (int i = 0; i < size; i++)
	{
		ch.insert(array[i]);
	}

	timeStart = clock();
	ch.remove(12);
	timeEnd = clock();

	std::cout.precision(9);
	std::cout << ch << std::endl;
	std::cout << "Time of algorithm is: " << std::fixed << (timeEnd - timeStart) / CLOCKS_PER_SEC << std::endl;

}