#include <iostream>
using namespace std;

class KD {

public: KD(int);
	   ~KD();

private: int data;
};

KD::KD(int x) { data = x; cout << data; }

KD::~KD() { cout << data; }

void create(void)
{
	KD kd5(1); static KD kd6(2);
}

KD kd1(3);

int main()
{
	KD kd2(4); create(); KD kd4(5);

	return 0;
}
/*

	Pretprocesor se ukljucuje prije kompajlera...
	Prolazi kroz sve linije izvornog koda, ' #include <>,"" ' zamjenjuje sa izvornim kodom ukljucenih biblioteka
	#define makroe  zamjenjuje konkretnim vrijednostima...

	1.
	Prije poziva glavne funkcije 'main()' PRVO se definisu globalni objekti, a u ovom slucaju to je objekat
	'kd1' -te se za isti poziva Constructor klase 'KD' sto znaci da se na standardni izlaz ispisuje "3".
	Taj objekat zivi sve dok barem jedan proces naseg programa se nalazi u RUN stanju.
	Sada kada su svi globalni objekti definisani , kreira se stack okvir funkcije main().
	Za stack okvir funkcije 'main()' idemo redom:

	2.
	Kreira se (definise se) objekat 'kd2' te se za isti automatski naravno poziva Constructor klase 'KD' 
	sto znaci da ce se u skladu sa definicijom te konstruktorske metode na standardni izlaz ispisati "4".

	3.
	Na vrh stack okvira funkcije 'main()' stavlja_se/kreira_se stack okvir funkcije 'create()' jer 'main()'  istu sada poziva.
	Sada se trenutno nalazimo u tom stack okviru. 
	Dakle kreira se LOKALNI objekat 'kd5' klase 'KD' te se zbog poziva Constructor-a i vec pomenutog mehanizma ispisuje "1".
	Zatim se kreira STATICKI objekat 'kd6' klase 'KD te se zbog poziva Constructor-a i vec pomenutog mehanizna ispisuje "2".
	Napusta se funkcija 'create()', njen stack okvir se skida sa vrha stack okvira funkcije 'main()' sto znaci da se za lokalni
	objekat 'kd5' te funkcije poziva Destructor klase 'KD' i u skladu sa definicijom istog ispisuje se "1".
	Medjutim STATICKI objekat 'kd6' -ima staticki zivotni vijek sto znaci da se za isti JOS ne poziva Destructor odgovarajuce klase.
	Sada je stack okvir funkcije 'create()' skinut sa vrha stack okvira funkcije 'main()' a mi vodimo racuna o objektu 'kd6' koji je jos
	uvijek inteligentan komad memorije jer za isti nije pozvan odgovarajuci Destructor.

	4.
	Vraceni smo u stack okvir pozivajuce funkcije, a to je funkcija 'main()' te je sljedeca naredba kreiranje objekta 'kd4'
	klase 'KD' sto znaci da se poziva Constructor klase 'KD' za taj objekat i ispisuje se "5".
	Dosli smo do naredbe return 0; sto znaci da napustamo 'main()' funkciju, skidamo njen stack() okvir i prema tome
	za objekte koji zive u tom stack segmentu se poziva Destructor klase 'KD'.

	Prvo se poziva Destructor za objekat 'kd4' (Last In First Out -za stack) te se ispisuje "5".
	Zatim se poziva Destuctor za objekat 'kd2' jer on je takodje lokalni objekat koji zivi u tom stack okviru sto ispisuje "4".
	Poziva se Destructor za objekat 'kd6' jer 'main() -pozivaoc vodi racuna o istom' pa tek onda za 'kd1' sto ispisuje "23" te je rezultat 

	"3412155423"

	Ovo je tip zadatka koji testira prepoznavanje zivotnog vijeka objekta(LOKALNI,STATICKI,DINAMICKI),
	testira prepoznavanje pozivanja Constructor/Destructor-a narocito prilikom ulaska/napustanja funkcija
	odnosno stavljanja/skidanja STACK okvira drugih funkcija na vrh stack okvira funkcije 'main().
*/
