#include <iostream>
using namespace std;

class X {};
class Y : public X {};
class Z : public Y {};

int main()
{
	X x; Y y; Z z;

	for (int i = 1; i < 3; i++)
	{
		try
		{
			for (int j = i + 1; j < 5; j++)
			{
				try
				{
					switch (j % 3)
					{
					case 0: throw z;
					case 1: throw y;
					default: throw x;
					}
				}


				catch (Z) { cout << "Z"; }
				catch (Y) { cout << "Y"; throw x; }
				catch (X) { cout << "X"; throw y; }

			}
		}

		catch (X) { cout << "X" << endl; }
		catch (Y) { cout << "Y" << endl; }
		catch (Z) { cout << "Z" << endl; }

	}

	

	return 0;
}