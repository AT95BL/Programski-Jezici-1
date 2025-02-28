#pragma once

/*

	Definisati šablonsku klasu Set<T> koja pravilno implementira interfejs ICollection. 
	Ova klasa treba da predstavlja dinamički alociran skup elemenata proizvoljnog tipa podatka. 
	Skup ne smije da sadrži ponovljene elemente (duplikate). 
	Omogućiti inicijalizaciju skupa inicijalizatorskom listom i inicijalizaciju praznog skupa. 
	Skup mora da bude proširiv. 
	Dva skupa se smatraju jednakim samo ako svaki element koji pripada jednom skupu pripada i drugom bez obzira na redoslijed u memoriji. 
	Korištenjem koncepata, ograničenja i statičkih pretpostavki obezbijediti ograničenja: 1) za tip T mora da postoji kopirajući konstruktor, 2) objekti tipa T se mogu ispisati i 3) dva objekta tipa T se mogu sabrati i rezultat je tipa T.
	Omogućiti korištenje iteratorske for petlje nad skupom.

*/
#ifndef Set_h
#define Set_h

#include "ICollection.h"



template <class T>
class Set : public ICollection<T>
{
	
protected:

	int index, capacity;			// 'index' nosi informaciju o prvom slobodnom mjestu u kolekciji, 'capacity' nosi informaciju o maksimalnom broju elemenata koji se mogu pohraniti u kolekciju.

	T* array{};

public:

	Set();
	Set(const int);
	Set(const int, const T*);
	Set(const Set&);
	Set(Set&&) noexcept;


	virtual bool addElement(const T&) override;

	virtual int numberOfElements() const override;


	virtual bool searchForElements(const std::function<bool(const T&)>&, std::shared_ptr<ICollection<T>>&) const override;

	virtual bool deleteElements(const std::function<bool(const T&)>&) override;

	
	virtual void printCollection() const override;


	virtual ICollection<T>* operator+=(const T&) override;

	virtual ICollection<T>* operator+(const T&) override;
	

	virtual bool filtrateElements(const std::function<bool(const T&)>&, std::shared_ptr<ICollection<T>>&) override;


	~Set();
};




// Definicija konstruktora koji podrazumjevano konstruise objekat kakav predstavlja 'prazan skup'.
template <class T>
Set<T>::Set() : index(0), capacity(0), array(nullptr) {}										// U C++ (na ispitu obavezno) koristimo 'nullptr' kao specijalnu pokazivacku vrijednost.




// Cesto koristen konstruktor gore navedene klase.
template <class T>
Set<T>::Set(const int number)																   // Kao argument prima cjelobrojne promjenjive ili konstante.
{
	index = 0;

	capacity = (number > 0) ? number : 0;

	array = new(T[capacity]);
}



// Definicija najcesce koristenog konstruktora, konstruktora koji nam se trazi u samom tekstu zadatka.
template <class T>
Set<T>::Set(const int number, const T* elements)		// Kao prvi argument prima broj elemenata nekog niza, a kao drugi argument prihvata staticki/dinamicki_alociran taj niz.
{

	capacity = number;									// Kapacitet tekuceg objekta <=> broj elemenata niza.

	array = new(T[number]);								// Dinamicka alokacija memorije, 

	for (index = 0; index < number; index++)			// Celije kolekcije tekuceg objekta popunjavamo sadrzajem celija postojeceg niza..
		array[index] = elements[index];
}




// Definicija CopyConstructor-a date klase, na ispitu se podrazumjeva da svaka klasa koja sadrzi pokazivac na dinamicki alociran memorijski blok posjeduje CopyConstructor sa mogucnostima DUBOKOG KOPIRANJA !
template <class T>
Set<T>::Set(const Set& other)
{
	capacity = other.capacity;						// Tekuci objekat ce biti istog kapaciteta kao i postojeci objekat.
	index = 0;										// Tekuci objekat je na pocetku kreiranja - prije kopiranja prazan.
	array = new (T[other.capacity]);				// Dinamicka alokacija memorije za skladistenje sadrzaja u celije kolekcije tekuceg objekta.

	if(other.index <= other.capacity)				// Nebitan uslov, zbog verzije VisualStudio-a i Warning-a morao sam da ga stavim.
	for (; index < other.index; index++)			// Pazi, petljom idemo od pocetnog elementa tekuce kolekcije do poslednjeg zauzetog mjesta. Moze se desiti da je kapacitet postojece kolekcije veci broj od broja zauzetih mjesta u kolekciji.
		array[index] = other.array[index];			// Skladistimo celiju po celiju.
}




// Definicija MoveConstructor-a, kao argument obavezno-bez-izuzetaka prihvata Non-const-rvalue objekat klase Set<T>.
template <class T>
Set<T>::Set(Set&& other) noexcept
{
	index = other.index;
	capacity = other.capacity;
	array = other.array;

	other.index = other.capacity = 0;
	other.array = nullptr;
}




// Definicija metode za klasicno dodavanje elemenata (Objekat + ime metode + element).
template <class T>
bool Set<T>::addElement(const T& element)
{
	for (int i = 0; i < this->index; i++)			// Ako pri prolasku kroz kolekciju 
		if (this->array[i] == element)				// utvrdimo da element 'element' vec postoji u datoj kolekciji 
			return false;							// samo izadjemo iz metode. Nema potrebe/smisla da se neki element skupa zapisuje vise puta.

	if (this->index < this->capacity)				// Ako prethodni uslov nije zadovoljen ('element' je element kakav ne postoji u datoj kolekciji) i u kolekciji ima mjesta
	{
		this->array[this->index++] = element;		// tada dodamo element na kraj kolekcije, pomjerimo indeks za jedno mjesto kako bih mogli kasnije dodavati jos elemenata, a  ne pisati preko istih ! 

		return true;
	}

	return false;
}





template <class T>
int Set<T>::numberOfElements() const
{
	return this->index;				// 'index' je informacija o prvom slobodnom mjestu u kolekciji, indeksiranje kolekcije ide od nule, tako da index iako pokazuje na slobodno mjesto, njegova vrijednost jeste broj zauzetih celija kolekcije.
}




template <class T>
bool Set<T>::searchForElements(const std::function<bool(const T&)>& doSomething, std::shared_ptr<ICollection<T>>& ptr) const
{
	int nmbE = 0;				

	for (int i = 0; i < this->index; i++)
		if (doSomething(this->array[i]))
			nmbE++;								// Ukupan broj elemenata koji zadovoljavaju neki zadati funkcijski uslov.			


	if (!nmbE)
		return false;


	T* arrayE = new(T[nmbE]);

	for(int i = 0, j = 0; i < this->index; i++)
		if (doSomething(this->array[i]))
		{
			arrayE[j] = this->array[i];
			j++;
		}


	ptr = std::make_shared<Set>(nmbE, arrayE);

	delete[] arrayE;

	return true;
}
/*
	Koncept prethodne metode:
	-Prvo provjerimo da li u nasoj kolekciji ima elemenata koji ispunjavaju neki zadati funkcijski uslov.
	-Ako ih nema , kontrolna promjenjiva (nmbE) je ostala jednaku 0 pa to signalizira da treba samo napustiti metodu.
	-U suprotnom gore prethodnoj tacki, trebamo te elemente iz kolekcije pohraniti u pomocni niz, pa kreirati objekat klase set pomocnu konstruktora
	 koji kao argument prihvata broj takvih elemenata (nmbE) i niz (arrayE) u koji su pohranjeni isti.
	-Pametni pokazivac, poziva konstruktor i obavlja posao vezan za prethodnu crtu.

	-Metoda kao paramatar prihvata jos i referencu na pametni pokazivac.
	 Razlog je taj sto kreiramo objekat u dinamickoj zoni memorije, i adresu tog objekta skladistimo u pametni pokazivac.
	 Naime rad sa obicnim pokazivacem zahtijeva eksplicitno pozivanje operatora delete[].
	 Zasto da radimo dupli posao kada C++ ima(skoro pa ima) garbage collection (kao u Java, C#) poznat kao pametni pokazivaci.
	 
	 Kod ovakvih metoda, koje kao rezultat vracaju objekte sa heap memorije postoji opasnost da se spontamo
	 za klasne objekte sa heap-a pozove Destructor tako da onaj pokazivac koji prima rezultat pokazuje 
	 na neinteligentan memorijski blok !
	 Do tog error-a bih doslo da nema parametra std::shared_ptr<ICollection<T>> i umjesto bool da metoda vrati 'ptr' !
*/




template<class T>
bool Set<T>::deleteElements(const std::function<bool(const T&)>& doSomething)
{
	int nmbE = 0;

	for (int i = 0; i < this->index; i++)
		if (doSomething(this->array[i]))
		{
			nmbE++;

			break;
		}


	if (!nmbE)
		return false;


	Set storage(*this);								// Poziv CopyConstructor-a. SVE KLASE KOJE POSJEDUJU POKAZIVAC NA DINAMICKI ALOCIRAN MEMORIJSKI BLOK TREBA DA IMAJU ODGOVARAJUCI COPYCONSTRUCTOR !

	this->index = 0;								// Iznova cemo popunjavati kolekciju tekuceg objekta.
	delete[] this->array;
	this->array = new(T[this->capacity]);			// U zadatku nije trazeno, i zbog operator+= nisam eksperimentisao sa this->capacity. Ostavio sam this->capacity takav kakav jeste.

	if (storage.index <= storage.capacity) // Bezvezan i nebitan uslov, stavio sam ga da izbjegnem po meni bespotreban Warning.
	for (int i = 0; i < storage.index; i++)
		if (!doSomething(storage.array[i]))			// Oni elementi koji NE ispunjavaju neki funkcjijski uslov ostaju u kolekciji.
			this->array[this->index++] = storage.array[i];	// Pazi this->array[this->index++] po potrebi inkrementiram this->index dok i prolazi kroz staru kolekciju koja je iskopirana u skladiste 'storage'.

	return true;									// Za 'storage' se poziva Destructor.
}





template<class T>
void Set<T>::printCollection() const
{
	for (int i = 0; i < this->index; i++)
		std::cout << this->array[i] << std::endl;
}





template <class T>
ICollection<T>* Set<T>::operator+=(const T& element)
{
	for (int i = 0; i < this->index; i++)							
		if (this->array[i] == element)							// Ako u kolekciji postoji element 'element' 
			return this;										// preskoci dodavanje istog.


	if (this->index < this->capacity)							// Ako u kolekciji ima mjesta
		this->array[this->index++] = element;					// na kraj te kolekcije dodaj 'element' <=> this->addElement(element) stim da to trosi memorijski-vremenske resurse.


	else														// Moramo prosiriti kolekciju.
	{
		Set storage(*this);										// Skladistenje stare kolekcije.

		this->capacity *= 2;									// Kapacitet tekuceg objekta raste.
		delete[] this->array;
		this->array = new(T[this->capacity]);					// Alokacija skladista za kolekciju tekuceg objekta.

		
		for (int i = 0; i < storage.capacity; i++)				// storage.capacity jer stara kolekcija je bila puna
			this->array[i] = storage.array[i];					// skladistimo stari sadrzaj nazad u tekuci objekat.

		this->array[this->index++] = element;					// Dodaj na kraj kolekcije.
	}														   

	return this;												// *ptr += x; *(*ptr+=x)+=y
}





template <class T>
ICollection<T>* Set<T>::operator+(const T& element)
{
	for (int i = 0; i < this->index; i++)
		if (this->array[i] == element)
			return this;

	if (this->index < this->capacity)
		this->array[this->index++] = element;
		
	return this;
}





template <class T>
bool Set<T>::filtrateElements(const std::function<bool(const T&)>& doSomething, std::shared_ptr<ICollection<T>>& ptr)
{
	int nmbE = 0;


	for (int i = 0; i < this->index; i++)
		if (doSomething(this->array[i]))
			nmbE++;


	if (!nmbE)
		return false;


	T* arrayE = new(T[nmbE]);

	for(int i = 0, j = 0; i < this->index; i++)
		if (doSomething(this->array[i]))
		{
			arrayE[j] = this->array[i];

			j++;
		}

	ptr = std::make_shared<Set> (nmbE, arrayE);

	delete[] arrayE;

	return true;
}




// Kod nasljedjivanja/izvodjenja obavezno u Base class DEFINISATI vritualDestructor na nacin kao sto je definisano u klasi ICollection. U derived class takodje napraviti/definisati Destructor.
template <class T>
Set<T>::~Set()
{
	delete[] array;
}




template <class T>
Set<T>::iterator ptrI;






#endif Set_h // Nemoj zaboraviti iteratorsku for petlju.