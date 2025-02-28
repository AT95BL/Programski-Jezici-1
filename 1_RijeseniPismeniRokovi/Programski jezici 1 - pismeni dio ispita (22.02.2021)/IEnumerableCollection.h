#pragma once
#ifndef IEnumerableCollection_h
#define IEnumerableCollection_h


#include <functional>
#include <memory>


template <class T>
class IEnumerableCollection
{

protected:


	virtual bool insertE(const int, const T&) = 0;

	virtual bool removeE(const int) = 0;

	virtual T recieveE(const int) = 0;

	virtual int howMuchE() = 0;


	virtual ~IEnumerableCollection() {}


};






#endif IEnumerableCollection_h