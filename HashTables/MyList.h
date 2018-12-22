#pragma once
#include "Node.h"

class MyList
{
public:

	int size;
	Node* Root;
	Node* Tail;

	MyList()
	{
		Root = NULL;
		size = 0;
	}

	~MyList()
	{
		if (Root != NULL)
		{
			delete Root;
		}
	}

	
	// Поиск элемента:
	bool Find(int _key)
	{
		if (size == 0)
		{
			return false;
		}
		else {
		Node * Current = new Node();
		Current = Root;
		
			for (int i = 0; i < size; i++)
			{
				if (Current->key == _key)
				{
					return true;
				}

				Current = Current->next;
			}
		}
	}

	int Push(Node element)
	{
		if (size == 0)
		{
			Root = new Node();
			Root->next = NULL;
			Root->previous = NULL;
			Root->key = element.key;
			Root->value = element.value;
			Tail = Root;
			size++;
		} 
		else {
			bool flag = Find(element.key);

			if (flag == true)
			{
				return 1;
			}

			Node* tmp = new Node();
			tmp->next = NULL;
			tmp->previous = Tail;
			Tail->next = tmp;
			tmp->value = element.value;
			tmp->key = element.key;
			Tail = tmp;
			size++;
			return 0;
		}
	}

	/* friend std::ostream& operator << (std::ostream& os, Node* current)
	{
		current = Root;
		for (int i = 0; i < size; i++)
		{
			os << "Key = " << current->key << " " << "Value = " << current->value;
			current = current->next;
		}
	} */

	
};
