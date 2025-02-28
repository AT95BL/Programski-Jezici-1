#include <iostream>





template <class T>
class X
{

private:

	int index, capacity;

	T* collection{};

public:

	X(const int nmb, const T* array)
	{
		index = 0;

		capacity = nmb;

		collection = new(T[nmb]);

		for (int i = 0; i < nmb; i++)
			collection[index++] = array[i];
	}

	X(const X& other)
	{
		index = other.index;
		capacity = other.capacity;

		collection = new(T[other.capacity]);

		if(other.index < other.capacity)
		for (int i = 0; i < other.index; i++)
			collection[i] = other.collection[i];
	}

	~X() { delete[] collection; }

	
	template <class T>
	friend std::ostream& operator<<(std::ostream&, X<T>&);
	
};





template <class T>
std::ostream& operator<<(std::ostream& out, X<T>& other)
{
	for (int i = 0; i < other.index; i++)
		out << i + 1 << ". " <<  other.collection[i] << std::endl;

	return out;
}





int main()
{
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }, n = sizeof(array)/sizeof(int);

	X<int> x(n, array), b(x);

	std::cout << x;

	return 0;
}