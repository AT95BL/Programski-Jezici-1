#pragma once
#ifndef IExtendedEnumerableCollection_h
#define IExtendedEnumerableCollection_h

#include "IEnumerableCollection.h"





template <class T>
class IExtendedEnumerableCollection : public IEnumerableCollection<T>
{

public:

	virtual T operator*(const int) const = 0;
	virtual bool operator+(const T&) = 0;


	virtual IEnumerableCollection<T>* operator*=(const int) const = 0;
	virtual IEnumerableCollection<T>* operator+=(const T&) = 0;


	virtual void indexThis(const int, const bool&) = 0;


	virtual ~IExtendedEnumerableCollection() {}
};





#endif IExtendedEnumerableCollection_h