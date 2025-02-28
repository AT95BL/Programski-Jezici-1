#include <iostream>
using namespace std;





class A
{
	const int maxE;
	int numE, * p;

public:

	A(int inMax = 10, int inNum = 0) : maxE(inMax)
	{
		p = new int[inMax];
		//maxE = inMax;					// maxE je konstantan atribut. Constructor ga mora inicijalizovati upotrebom inicijalizatora , tj. operatora ':' i para zagrada kao u komentaru kod 'linije 15'. Dakle ovu naredbu treba obrisati i ukinuti komentar sa 'linije 15' i program ce raditi kako treba.
		numE = inNum;
	}

	void f(const A& x)
	{
		x.p[0] = 0;
	}
};





int main()
{
	A o;

	A* po = &o;
	A& uo = o;

	return 0;
}