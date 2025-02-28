#pragma once

#ifndef ICollection_h
#define ICollection_h

#include <iostream>
#include <functional>
#include <memory>
#include <iterator>

/*
	Definisati šablonski interfejs ICollection<T> kojim se predstavljaja kolekcija podataka.
	Interfejs mora da sadrži metodu za dodavanje elementa i za dobavljanje broja elemenata. 
	Interfejs mora da sadrži metode za pretragu i za uklanjanje elemenata kojima se prosljeđuje funkcijski
	objekat za odabir elementa na osnovu proizvoljnog uslova. Omogućiti proširivanje kolekcije novim
	elementom korištenjem odgovarajućeg operatora sa dodjelom koji se može ulančano pozivati, kao i
	korištenjem ekvivalentnog operatora bez dodjele i bez bočnih efekata. Pravilno specifikovati
	podrazumijevano ponašanje samo za navedene operatore za dodavanje elementa korištenjem
	metoda dostupnih u interfejsu. Dodati metodu bez bočnih efekata za filtriranje elemenata kolekcije
	koja kao rezultat vraća filtriranu kolekciju, a kao parametre prihvata potrebne funkcijske objekte. 

*/

// Interfejs samo propisuje koje metode ce se naslijediti i kasnije definisati.

template <class T>
class ICollection
{

public:

	virtual bool addElement(const T&) = 0;

	virtual int numberOfElements() const = 0;


	virtual bool searchForElements(const std::function<bool(const T&)>&, std::shared_ptr<ICollection>&) const = 0;
	
	virtual bool deleteElements(const std::function<bool(const T&)>&) = 0;


	virtual void printCollection() const = 0;


	virtual ICollection* operator+=(const T&) = 0;

	virtual ICollection* operator+(const T&) = 0;


	virtual bool filtrateElements(const std::function<bool(const T&)>&, std::shared_ptr<ICollection>&) = 0;


	virtual ~ICollection() {};
};





#endif ICollection_h