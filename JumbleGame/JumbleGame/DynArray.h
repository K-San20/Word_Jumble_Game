#ifndef _DYN_ARRAY_H_
#define _DYN_ARRAY_H_

template<typename Type>
class DynArray
{
	Type* arr;
	unsigned int Size;
	unsigned int Capacity;

public:
	DynArray();
	~DynArray();
	DynArray(const DynArray<Type>& obj);
	DynArray<Type>& operator=(const DynArray<Type>& obj);
	Type& operator[](const unsigned int index);
	const Type& operator[](const unsigned int index) const;
	unsigned int size() const;
	unsigned int capacity() const;
	void clear();
	void append(const Type& item);
	void reserve(const unsigned int& newCap = 0);
};
template<typename Type>
DynArray<Type>::DynArray()
{
	arr = new Type[1];
	Size = 0;
	Capacity = 0;
}
template<typename Type>
DynArray<Type>::~DynArray()
{
	clear();
	delete[] arr;
}
template<typename Type>
DynArray<Type>::DynArray(const DynArray<Type>& obj)
{
	Size = obj.Size;
	Capacity = obj.Capacity;
	Type* holder = new Type[Capacity];
	for (unsigned int i = 0; i < Size; i++)
		holder[i] = obj.arr[i];
	arr = new Type[Capacity];
	for (unsigned int i = 0; i < Size; i++)
		arr[i] = holder[i];
	delete[] holder;
}
template<typename Type>
DynArray<Type>& DynArray<Type>::operator=(const DynArray<Type>& obj)
{
	if (this != &obj)
	{
		delete[] arr;
		Size = obj.Size;
		Capacity = obj.Capacity;
		Type* holder = new Type[Capacity];
		for (unsigned int i = 0; i < Size; i++)
			holder[i] = obj.arr[i];
		arr = new Type[Capacity];
		for (unsigned int i = 0; i < Size; i++)
			arr[i] = holder[i];
		delete[] holder;

	}
	return *this;
}
template<typename Type>
Type& DynArray<Type>::operator[](const unsigned int index)
{
	return arr[index];
}
template<typename Type>
const Type& DynArray<Type>::operator[](const unsigned int index) const
{
	return arr[index];
}
template<typename Type>
unsigned int DynArray<Type>::size() const
{
	return Size;
}
template<typename Type>
unsigned int DynArray<Type>::capacity() const
{
	return Capacity;
}
template<typename Type>
void DynArray<Type>::clear()
{
	if (Capacity != 0)
	{
		delete[] arr;
		Size = 0;
		Capacity = 0;
		arr = new Type[1];
	}
}
template<typename Type>
void DynArray<Type>::append(const Type& item)
{
	if (Capacity == 0)
	{
		arr[0] = item;
		Size++;
		Capacity++;
	}
	else if (Size == Capacity)
	{
		reserve();
		arr[Size] = item;
		Size++;
	}
	else
	{
		arr[Size] = item;
		Size++;
	}
}
template<typename Type>
void DynArray<Type>::reserve(const unsigned int& newCap = 0)
{
	if (newCap == 0)
	{
		if (Capacity == 0)
			Capacity++;
		else
		{
			Capacity = Capacity * 2;
			Type* holder = new Type[Capacity];
			for (unsigned int i = 0; i < Size; i++)
				holder[i] = arr[i];
			delete[] arr;
			//arr = new Type[Capacity];
			arr = holder;
			//delete[] holder;
		}
	}
	else if (!(newCap <= Size))
	{
		Capacity = newCap;
		Type* holder = new Type[Capacity];
		for (unsigned int i = 0; i < Size; i++)
			holder[i] = arr[i];
		delete[] arr;
		//arr = new Type[Capacity];
		arr = holder;
		//delete[] holder;
	}
}
#endif