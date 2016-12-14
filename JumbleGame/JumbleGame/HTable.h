#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include "SLList.h"
#include <fstream>
using namespace std;

template<typename Type>
class HTable
{
	SLList<Type>* table;
	unsigned int numBuckets;
	unsigned int(*hashFunct)(const Type& val);
public:
	HTable(unsigned int numOfBuckets, unsigned int(*hFunction)(const Type &v));
	~HTable();
	HTable(const HTable<Type>& obj);
	HTable<Type>& operator=(const HTable<Type>& obj);
	void insert(const Type& v);
	bool findAndRemove(const Type& v);
	void clear();
	int find(const Type& v) const;
	void HTable<Type>::printTableData(const char* filePath = "hashdata.txt");
	SLList<Type>& operator[](unsigned int index);
};

template<typename Type>
HTable<Type>::HTable(unsigned int numOfBuckets, unsigned int(*hFunction)(const Type &v))
{
	numBuckets = numOfBuckets;
	hashFunct = hFunction;
	table = new SLList<Type>[numBuckets];
}
template<typename Type>
HTable<Type>::~HTable()
{
	for (unsigned int i = 0; i < numBuckets; i++)
	{
		table[i].clear();
	}
	delete[] table;
}
template<typename Type>
HTable<Type>::HTable(const HTable<Type>& obj)
{
	for (unsigned int i = 0; i < numBuckets; i++)
		table[i] = obj.table[i];
	numBuckets = obj.numBuckets;
	hashFunct = obj.hashFunct;
}
template<typename Type>
HTable<Type>& HTable<Type>::operator=(const HTable<Type>& obj)
{
	if (this != &obj)
	{
		delete[] table;
		table = new SLList<Type>[obj.numBuckets];
		for (unsigned int i = 0; i < obj.numBuckets; i++)
			table[i] = obj.table[i];
	}
	numBuckets = obj.numBuckets;
	hashFunct = obj.hashFunct;
	return *this;
}
template<typename Type>
void HTable<Type>::insert(const Type& v)
{
	table[hashFunct(v)].addHead(v);
}
template<typename Type>
bool HTable<Type>::findAndRemove(const Type& v)
{
	unsigned int bucketToSearch = find(v);
	if (bucketToSearch == -1)
		return false;
	else
	{
		SLLIter<Type> bucketIter(table[bucketToSearch]);
		for (bucketIter.begin(); !(bucketIter.end()); ++bucketIter)
		{
			if (v == bucketIter.current())
			{
				table[bucketToSearch].remove(bucketIter);
				return true;
			}
		}
		return false;
	}
}
template<typename Type>
void HTable<Type>::clear()
{
	for (unsigned int i = 0; i < numBuckets; i++)
	{
		table[i].clear();
	}
}
template<typename Type>
int HTable<Type>::find(const Type& v) const
{
	unsigned int bucketToSearch = hashFunct(v);
	SLLIter<Type> bucketIter(table[bucketToSearch]);
	for (bucketIter.begin(); !(bucketIter.end()); ++bucketIter)
	{
		if (v == bucketIter.current())
			return bucketToSearch;
	}
	return -1;
}
template<typename Type>
SLList<Type>& HTable<Type>::operator[](unsigned int index)
{
	return table[index];
}
template <typename Type>
void HTable<Type>::printTableData(const char* filePath = "hashdata.txt")
{
	// we're gonna need to open a file for all this data
	ofstream outFile(filePath);

	// let's make sure the file got opened
	if (outFile.is_open())
	{
		// number of empty buckets, total count of elements, index of emptiest bucket, index of fullest bucket
		unsigned int empty = 0;
		unsigned int totalCount = 0;
		unsigned int loIndex = 0;
		unsigned int hiIndex = 0;

		// loop through all the buckets
		for (unsigned int i = 0; i < numBuckets; ++i)
		{
			// add the number of elements in each bucket to the total count
			totalCount += table[i].size();
			// print the index of this bucket and its size to the file
			outFile << i << " : " << table[i].size() << '\n';

			// if this list is empty, increment the empty count
			if (table[i].size() == 0)
				++empty;

			// if this list has less elements than the lowest one recorded so far, store this as the new lowest
			if (table[i].size() < table[loIndex].size())
				loIndex = i;
			// else, if this list has more elements than the highest one recorded so far, store this as the new highest
			else if (table[i].size() > table[hiIndex].size())
				hiIndex = i;
		}

		// print the total count of items and number of buckets to the file
		outFile << '\n' << totalCount << " Total items stored in " << numBuckets << " buckets\n";
		// print the number of empty buckets
		outFile << '\n' << empty << " Buckets are empty\n\n";
		// get the number of elements in the emptiest bucket
		unsigned int Low = table[loIndex].size();
		// get the range fullest-emptiest+1
		unsigned int range = table[hiIndex].size() - Low + 1;
		// print this info to the file
		outFile << "each bucket contains between " << Low << " and " << Low + range - 1 << " items.\n\n";

		// make a new array to count how many buckets contain each number of items between the emptiest and fullest
		// and initialize each cell to 0
		unsigned int* arr = new unsigned int[range];
		for (unsigned int j = 0; j < range; ++j)
			arr[j] = 0;

		// now we go through and count how many buckets contain each number of items...
		// 3 buckets have 15 items
		// 5 buckets have 16 items
		// etc.
		for (unsigned int k = 0; k < numBuckets; ++k)
			++arr[table[k].size() - Low];

		// now print this data to the file
		for (unsigned int p = 0; p < range; ++p)
			outFile << arr[p] << " buckets have " << p + Low << " items\n";

		// delete the array we made a minute ago, we are done with it
		delete[] arr;
	}
}
#endif