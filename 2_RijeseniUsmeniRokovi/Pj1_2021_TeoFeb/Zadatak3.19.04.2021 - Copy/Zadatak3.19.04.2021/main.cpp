#include <iostream>
using namespace std;





int dat;	// Globalna promjenjiva. Ako se eksplicitno ne inicijalizuje prilikom definisanja, ista ima pocetnu vrijednost jednaku nuli.





class A
{
	int pod;		// 'private' data member -atribut,podatak_clan...

public:

	A() : pod(dat++) { pod++; }
	
	~A(){ dat--;	cout << "*"; }

	A& operator++(){ cout << "a" << pod--; return *this; }

	A operator++(int){ cout << "b" << pod++; return *this; }

	A& operator--(){ cout << "c" << ++pod; return *this; }

	A operator--(int){ cout << "d" << --pod; return *this; }
};





int main()
{
	A y;		

	++--y++;

	cout << endl;

	return 0;
}
/*
	1.

	Poziva se Constructor klase 'A'  i u skladu sa definicijom istog
	'A() : pod(dat++) { pod++; }'
	atribut 'pod' objekta 'y' dobija vrijednost 0, zatim  globalna promjenjiva'dat' dobija vrijednost 1
	i na kraju atribut 'pod' objekta 'y' dobija vrijednost '1'.
	Pazi, 'pod i dat' su integer-i, a svaka primjena prefiksnog ++ nad integer-om vuce bocni efekat.

	2.

	Idemo u naredbu ++--y++ koja je ako se malo bolje pogleda oblika ++(--(y++)); te stim u vezi imamo sljedece stavke.

	3.

	Postfiksno ima prioritet u odnosu na prefiksno te stim u vezi prethodna naredna je <=> sa naredbom ++--(y++)
	sto znaci da se poziva ova metoda 'A operator++(int){ cout << "b" << pod++; return *this; }'.
	Ta metoda odmah ispisuje "b1" , zatim inkrementira pod, a na kraju vraca rezultat.
	Za razumijevanje ispisa trik je shvatiti razliku kada metoda/funkcija vraca referencu na objekat ,a kada vraca objekat !

	Ova metoda kao rezultat vraca '*this' -sadrzaj tekuceg objekta, a to je objekat 'y', a vraca ga kao objekat.
	Dakle pri napustanju ove metode -kada ista vrati rezultat, kreira se objekat klase 'A' i sadrzaj tog objekta
	se kopira u objekat 'y'. Taj novokreirani, nama na oko nevidljivi objekat je prisutan sve dok naredba traje !

	4. 
	
	Zbog 3. 2. postaje ++(--y) te stim u vezi poziva se ova metoda
	'A& operator--(){ cout << "c" << ++pod; return *this; }' koja odmah ispisuje tekst "c3" te takvim inkrementovanim ovo 'pod' i ostavlja.
	Ta metoda vraca '*this' ali rezultat vraca kao referencu. 
	Sta to znaci (konkretno na tekucem primjeru) ?
	Metoda sadrzaj tekuceg objekta '*this' vraca kao referencu 'A&', ne kreira se novi objekat klase 'A' pri napustanju metode
	vec vraca se postojeci-koji je u ovom slucaju i tekuci objekat. Odnosno pri skidanju ove metode sa stack okvira f-je main
	desava se 'y = y' dok je kod prethodne metode bio slucaj 'y = (NekiObjekatKlaseA = *this).

	5.

	Zbog 4. 2. posatje ++y te stim u vezi poziva se ova metoda
	'A& operator++(){ cout << "a" << pod--; return *this; }' koja ispisuje "a3", zatim dekrementira 'pod'
	i vraca rezultat ,a posto joj je povratni tip referenca sve je isto kao u tacki 4. 
	Dakle kada se sa stack okvira f-je main skine ova metoda ostaje (u pozivaocu -u main-u) jos ovo 'y'.

	Za sada nas ispis izgleda ovako "b1c3a3", kada se terminira naredna linije 41 , nama na oko nevidljivi objekat
	se unistava -poziva se Destructor klase 'A' za isti te stim u vezi imamo ispis

	"b1c3a3*".

	6.

	Zbog cout u kombinaciji sa endl presli smo u novi red, nakon toga napusta se f-ja main te stim u vezi poziva se 
	Destructr klase 'A' za objekat 'y' i u novom redu je ispisana jos jedna *.

	
	U PJ C++, veliki dio posla se obavlja komunicirajuci preko referenci.


*/