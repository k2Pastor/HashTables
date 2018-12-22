#pragma once

#include <iostream>

class Node
{

public:
	int key;
	long int value;
	Node* previous;
	Node* next;

	Node()
	{
		key = 0;
		value = -1;
		previous = NULL;
		next = NULL;
	}

	Node(int _key, long int _value)
	{
		key = _key;
		value = _value;
	}

};