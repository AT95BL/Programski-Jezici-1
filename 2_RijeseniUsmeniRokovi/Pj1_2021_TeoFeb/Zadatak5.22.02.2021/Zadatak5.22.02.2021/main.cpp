#include <iostream>
using namespace std;

class X
{

public:

	X(int i = 1) : x(i) { cout << "X"; }

protected: int x;
};


class A : virtual public X
{
public:

	A(int i = 10) : X(i) { cout << "A"; }
	void print() { cout << x << endl; }
};


class B : virtual public X
{

public:

	B(int i = 20) : X(i) { cout << "B"; }
};


class C : public A, public B
{

public:
	C(int i = 50) : X(i) { cout << "C"; }

};


int main()
{
	A a; a.print();
	C c; c.print();
	return 0;
}

/*

	Kreira se stack okvir funkcije 'main()'.
	Idemo redom.

	1. 

	'A a' kreira se objekat 'a' klase 'A' te se za isti pozivaju odgovarajuci Constructor-i i to kao i UVIJEK prvo 
	se kreira/definise podobjekat/i osnovne klase te nakon toga se kreira i objekat izvedene klase !
	Klasa 'A' je derived(izvedena) od klase 'X' tako da unutar objekta 'a' (Kao i svakog objekta klase 'A'.) 
	zivi skriveni podobjekat klase 'X'. U skladu sa C++ standardom prvo se inicijalizuje podobjekat klase 'A' tj. objekat
	klase 'X' i u ovom slucaju eksplicitno se poziva (Sa argumentom 10.) Constructor te osnovne klase 'X'.
	Vidimo da svaki poziv Constructor-a klase 'X' ispisuje "X". Sada kada je definisan podobjekat klase 'A' ,a posto osim
	njega klasa 'A' nema vise podobjekata poziva se Constructor klase 'A' i ispisuje se "A". "XA" imamo na ispisu za sada.
	'a.print()' ispisuje "10" jer 'x' iz klase 'X' je naslijedjeno iz osnovne klase,a ono je ujedno i data_member podobjekta.

	"XA10" pa
	Prelazak u novi red.

	2.

	'C c' klasa 'C' je javno izvedena iz klasa 'A i B' redom sto znaci da prije definisanja/kreiranja
	bilo kojeg objekta klase 'C' pozivaju se Constructor-i odgovarajucih osnovnih klasa.
	Zbog virtual kod izvodjenja 'A i B' od 'X' u 'C' koje je visestruko izvedena klasa ZIVI
	SAMO JEDAN PODOBJEKAT-OBJEKAT klase 'X'. Kako 'A' i 'B' podobjekti klase 'C' nisu definisani bez tog podobjekta
	prvo se definise on sto znaci da se ispisuje "X" pa redom kojim su navedene klase iz kojih se izvodi 'C' imamo
	"AB". Sada kada su svi podobjekti objekta 'c' klase 'C" definisani/kreirani poziva se Constructor te klase i ispisuje
	se "C".

	'c.print()' se odnosi na eksplicitno inicijalizovan podobjekat klase 'X' koji zivi u objektu 'c' klase 'C' te se za isti ispisuje '50'.

	"XA10"
	"XABC50"

	Za razumijevanje ovog zadatka je kljucno shvatiti koncept izvodjenja/nasljedjivanja bilo jednostrukog
	ili visestrukog sto se moze nauciti sa SLIDESHOW materials od Goran Banjac, Drazen Brdjanin.
	Iako je danas na snazi C++17 sav dio gradiva. (Osim SMART_Pointers-a i Move Semantics-a koji su iz C++11) proizilazi iz
	ANSII C++ standarda. C++ 14 pa na dalje igra ulogu kod onih koji C++ koriste pri izrai OS-a.
*/