#pragma once

#ifndef DynamicArray_h
#define DynamicArray_h

#include "IExtendedEnumerableCollection.h"





template <class T>
class DynamicArray : public IEnumerableCollection<T>
{

private:


	int index, capacity, nmb;
	T* collection{};

	
public:


	DynamicArray(const int, const T*);

	DynamicArray(const DynamicArray&);

	DynamicArray(const DynamicArray&& other)
	{
		index = other.index;
		nmb = other.nmb;
		capacity = other.capacity;
		collection = other.collection;

		other.index = other.nmb = other.capacity = 0;
		other.collection = nullptr;
	}


	virtual bool insertE(const int, const T&) override;
	virtual bool removeE(const int) override;
	virtual T recieveE(const int) const override;
	virtual int howMuchE() const override;


	std::shared_ptr<IEnumerableCollection<T>> filtrateCollection(const std::function<bool(const T&)>&, const std::shared_ptr<IEnumerableCollection<T>>&) const;
	std::shared_ptr<IEnumerableCollection<T>> transformers(const std::function<T(const T&)>&, const std::shared_ptr<IEnumerableCollection<T>>&) const;

	~DynamicArray() { delete[] collection; }
};





template <class T>
DynamicArray<T>::DynamicArray(const int n, const T* array)
{
	index = 0;
	nmb = 0;
	capacity = n;
	collection = new(T[n]);


	for (int i = 0; i < n; i++)
	{
		collection[i] = array[i];
		nmb++;
	}
}





template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray& other)
{
	index = other.index;
	nmb = other.nmb;
	capacity = other.capacity;
	collection = new(T[other.capacity]);


	if (index < capacity)
		for (int i = 0; i < other.index; i++)
			collection[i] = other.collection[i];
}





template <class T>
bool DynamicArray<T>::insertE(const int position, const T& element)
{
	if ((position >= this->index) && (position < this->capacity))
	{

		DynamicArray other(*this);


		this->index = 0;
		this->nmb = 0;
		this->capacity++;
		delete[] this->collection;


		this->collection = new(T[this->capacity]);
		this->collection[position] = element;


		for (int i = 0; i < other.index; i++)
		{
			if (i == position)
			{
				this->nmb++;
				this->index++;
			}

			else
				this->collection[this->index++] = other.collection[i];
		}


		return true;
	}


	return false;
}





template <class T>
bool DynamicArray<T>::removeE(const int position)
{
	if ((position >= this->index) && (position < this->capacity))
	{

		DynamicArray other(*this);


		this->index = 0;
		this->nmb = 0;
		delete[] this->collection;
		this->collection = new(T[this->capacity]);


		if(this->index < this->capacity)
			for (int i = 0; i < other.index; i++)
			{
				if (i != position)
				{
					this->collection[this->index++] = other.collection[i];
					this->nmb++;
				}
			}


		return true;
	}


	return false;
}





template <class T>
T DynamicArray<T>::recieveE(const int position) const
{
	return this->collection[position];
}





template <class T>
int DynamicArray<T>::howMuchE() const
{
	return this->nmb;
}





template <class T>
std::shared_ptr<IEnumerableCollection<T>> DynamicArray<T>::filtrateCollection(const std::function<bool(const T&)>& function,const std::shared_ptr<IEnumerableCollection<T>>& ptr) const
{
	int numberOfElements = 0;


	for (int i = 0; i < this->index; i++)
		if (function(this->collection[i]))
			numberOfElements++;


	if (!numberOfElements)
		return nullptr;


	T* array = new(T[numberOfElements]);


	for(int i = 0, j = 0; i < this->index; i++)
		if (function(this->collection[i]))
		{
			array[j] = this->collection[i];
			j++;
		}


	ptr = std::make_shared<DynamicArray> (numberOfElements, array);


	delete[] array;


	return ptr;
}





template <class T>
std::shared_ptr<IEnumerableCollection<T>> DynamicArray<T>::transformers(const std::function<T(const T&)>& function, const std::shared_ptr<IEnumerableCollection<T>>& ptr) const
{
	T* array = new(T[this->index]);

	
	for (int i = 0; i < this->index; i++)
		array[i] = function(this->collection[i]);


	ptr = std::make_shared<DynamicArray>(this->index, array);


	delete[] array;


	return ptr;
}






#endif DynamicArray_h