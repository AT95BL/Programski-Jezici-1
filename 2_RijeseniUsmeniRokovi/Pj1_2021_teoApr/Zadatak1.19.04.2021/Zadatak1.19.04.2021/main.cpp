#include <iostream>
using namespace std;

// Find the output of the following code.


class A
{

public:

	virtual int p(int a, int b)
	{
		cout << "AP-"; return (a + b);
	}


	int m(int a, int b)
	{
		cout << "AM-"; return (a - b);
	}

};





class B : public A
{

public:

	int p(int a, int b)
	{
		cout << "BP-"; return (a * b);
	}

	virtual int m(int a, int b)
	{
		cout << "BM-"; return (a - b);
	}

};





int main()
{
	A* a = new B(), * b = new A();


	cout << a->m(2, b->p(3, a->p(4, b->m(5, 6))));


	return 0;
}
/*

	1. Da vidimo ko je 'a' i sta on moze. cout << a->p(5,10) << endl; cout << a->m(5,10) << endl;

	'a' je tipa pokazivac na osnovnu klasu 'A' to jest tipa 'A*'.
	'a' posjeduje adresu objekta  izvedene klase 'B' koji zivi u heap segmentu memorije
		sto znaci da je '*a' objekat osnovne klase koji je ujedno podobjekat objekta izvedene klase.

	a->p(5, 10) kao output daje BP-50 evo i zasto:

	-U klasi 'A' metoda 'int p(int a, int b)' je definisana i okarakterisana kao virtualna,
	 u klasi 'B' iako nije eksplicitno naglaseno operatorom 'override' doslo je do override-a istoimene metode
	 jer u klasi 'B' imamo metodu 'int p(int a, int b) -PovratniTipArgumentiIImenaArgumenata se podudaraju sa metodom p(...) iz 'A''.

	-Polimorfizan je svojstvo objekta izvedene klase(To je objekat klase 'B' koji je smjesten negdje na heap memory segment-u.)
	 da izvrsi operaciju na nacin svojstven izvedenoj klasi(Od tog objekta se trazi da izvrsi operaciju p(...) iz klase 'B'.)
	 na nacin prilagodjen izvedenoj klasi (Saglasno sa definicijom metode p(...) klase 'B' izvedene klase)
	 iako mu se pristupa kao objektu osnovne klase(A mi mu pristupamo preko pokazivaca osnovne klase.).

	-Prema tome svako a->p(...) iz naseg primjera aktivira POLIMORFIZAM.


	a->m(5, 10) kao output daje AM--5 evo i zasto:

	-'*a' je objekat osnovne klase koji je ujedno i podobjekat objekta izvedene klase jer u 'a' je smjestena adresa objekta
	izvedene klase -a taj objekat je smjesten negdje na heap-u...

	-U osnovnoj klasi je definisana metoda 'int m(int a, int b)' koja kao sto vidimo nije virtualna pa svaki poziv
	a->m(...) ne dovodi do polimorfizma. Prema tome a->m(...) poziva metodu m(...) iz klase 'A'.
	---------------------------------------------------------------------------------------------------------------------------------

	2. Da vidimo ko je 'b' i sta on moze.

	'b' je pokazivac na osnovnu klasu 'A' koji pokazuje na objekat osnovne klase 'A' -taj objekat se takodje
	nalazi negdje u dinamickoj zoni memorije tj.  heap memory segment-u.

	b->p(5, 10) kao output daje AP-15, b->m(5,10) kao output daje AM-- evo i zasto:

	-U klasi 'A' definisana je metoda 'p/m(...)', a '*b' je nista drugo nego objekat te klase.
	----------------------------------------------------------------------------------------------------------------------------------

	3. Poenta 'line 55' jeste razumjeti ko su 'a i b redom' te stack-hijerarhiju pozvanih funkcija/metoda kao sto je to slucaj
	   sa P2 Recursion.

	   Kreira se stack okvir funcije main,
	   zatim se kreira stack okvir metode cout,
	   zatim metoda(Idemo redom.) a->m, b->p, a->p, b->m te kako koju skidamo sa vrha stack-a tako pratimo rezultat.

	   b->m(5,6)
	   Ipisuje "AM-" i svome pozivaocu vraca 5-6 = -1.

	   a->p(4, b->m(5,6))     <=> a->p(4, -1)
	   Ispisuje "BP-" i svome pozivaocu vraca (4 * -1) = -4.

	   b->p(3, a->p(4, b->m(4,6)))    <=> b->p(3,-4)
	   Ispisuje "AP-" i svome pozivaocu vraca (3 + -4) = -1.

	   a->m(2, p(3, a->p(4, b->m(4,6))))    <=> a->m(2,-1)
	   Ispisuje "AM-" i svome pozivaocu vraca (2--1) = 3.

	   Tako da je rjesenje AM-BP-AP-AM-3.
	   --------------------------------------------------------------------------------------------------------------

	   Na ispitu kazes sebi(pojednostavis) b->m(5,6) poziva se ta i ta metoda za te i te argumente... i sa strane dopisujes
	   rezultate koje pratis.
*/