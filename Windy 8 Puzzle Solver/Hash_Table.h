#pragma once
const int SIZE = 50;

template <typename itemType> class HashTable
{
private:
	struct node
	{
		itemType item;
		node* nextItem = nullptr;
	};

	node* table[SIZE] = { nullptr };

public:
	//Constructor
	HashTable()
	{

	}

	//Returns an index. 
	int HashFunction(int key)
	{
		return key % SIZE;
	}

	//Inserts a value into the Hash Table.
	void Insert(int key, itemType value)
	{
		int index = HashFunction(key);

		//Create a node if it does not exist.
		if (table[index] == nullptr)
		{
			table[index] = new node;
			table[index]->item = value;
			table[index]->nextItem = nullptr;
		}
		else
		{
			//Add a node with same index to beginning of the linked list.
			node* tempPtr = new node;

			tempPtr->item = value;
			tempPtr->nextItem = table[index];

			table[index] = tempPtr;
		}
	}

	//Searches for a value inside the Hash Table.
	bool Search(int key, itemType value)
	{
		int index = HashFunction(key);

		if (table[index] == nullptr)
		{
			return false;
		}
		else
		{
			node* tempPtr = table[index];

			//Search through the linked list to find the value.
			while (tempPtr != nullptr)
			{
				if (tempPtr->item == value)
				{
					return true;
				}

				tempPtr = tempPtr->nextItem;
			}
		}

		return false;
	}
};