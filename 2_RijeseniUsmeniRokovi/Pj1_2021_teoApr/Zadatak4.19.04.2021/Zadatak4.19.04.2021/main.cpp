class O { protected: int i; };
class I1 : public O {};
class I2 : protected O {};

void f(O* po, I1* p1, I1 i1, I2* p2, I2 i2)
{
	po->i = 1;

	p1->i = 2;

	i1.i = 3;

	p2->i = 4;

	i2.i = 5;
}
/*
	Greske nastaju zbog toga sto atributu objekta klase O,I1,I2 pokusavamo
	pristupiti izvan te klase i to funkcijom koja nije prijateljska.

	Postoji mogucnost da ja ne shvatam ovaj zadatak.
*/