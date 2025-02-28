#pragma once
#ifndef  InsertBufferedArray_h
#define InsertBufferedArray_h

#include "DynamicArray.h"





template <class T>
class BufferedArray : public DynamicArray<T>
{

private:

	int state;


public:


	BufferedArray(const int nmb, const T* array) : DynamicArray<T>::DynamicArray(nmb, array)
	{
		state = 0;
	}


	virtual bool insertE(const int, const T&) override;
};




template<class T>
bool BufferedArray<T>::insertE(const int position, const T& element)
{
	if ((position >= DynamicArray<T>::index) && (position < DynamicArray<T>::capacity))
	{

		DynamicArray other(*this);


		DynamicArray<T>::index = 0;
		DynamicArray<T>::nmb = 0;
		DynamicArray<T>::capacity++;
		delete[] DynamicArray<T>::collection;


		DynamicArray<T>::collection = new(T[DynamicArray<T>::capacity]);
		DynamicArray<T>::collection[position] = element;


		for (int i = 0; i < DynamicArray<T>::index; i++)
		{
			if (i == position)
			{
				DynamicArray<T>::nmb++;
				DynamicArray<T>::index++;

				state++;
			}

			else
				DynamicArray<T>::collection[DynamicArray<T>::index++] = DynamicArray<T>::collection[i];
		}


		return true;
	}


	return false;
}


#endif // ! InsertBufferedArray_h
