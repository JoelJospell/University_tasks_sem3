#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Massive
{
	int* p;
	int length;
public:
	Massive(int a)
	{
		p = (int*)malloc(a * sizeof(int));
		length = a;
	}
	Massive(Massive& parent)
	{
		length = parent.length;
		p = new int[length];
		p = (int*)malloc(length * sizeof(int));
		for (int i = 0; i < length; i++)
		{
			p[i] = parent.p[i];
		}
	}
	~Massive() {}
	void print()
	{
		for (int i = 0; i < length; i++)
		{
			cout << p[i] << " " << endl;
		}
	}
	void set(int a, int number)
	{
		if ((a >= -100) && (a <= 100) && (number > -1) && (number < length))
		{
			p[number] = a;
		}
	}
	void setrandom()
	{
		srand(time(NULL));
		for (int i = 0; i < length; i++)
		{
			p[i] = rand() % 101 - 100;
		}
	}
	void get(int number)
	{
		if ((number > -1) && (number < length))
		{
			cout << p[number] << endl;
		}
	}
	void add(int a)
	{
		if ((a > -100) && (a < 100))
		{
			int* p2 = (int*)malloc((length + 1) * sizeof(int));
			for (int i = 0; i < length; i++)
			{
				p2[i] = p[i];
			}
			p2[length] = a;
			free(p);
			p = p2;
			length++;
		}
	}
	void plus(Massive& second)
	{
		for (int i = 0; i < length; i++)
		{
			p[i] += second.p[i];
		}
	}
	void minus(Massive& second)
	{
		for (int i = 0; i < length; i++)
		{
			p[i] -= second.p[i];
		}
	}
};
int main(int argc, char *argv[])
{
	Massive mas1(5);
	mas1.set(5, 2);
	mas1.get(2);
	cout<<endl;
	mas1.print();
	cout<<endl;
	Massive mas2(mas1);
	mas2.print();
	cout<<endl;
	mas1.add(6);
	mas1.print();
	mas1.plus(mas2);
	cout<<endl;
	mas1.print();
	mas1.minus(mas2);
	cout<<endl;
	mas1.print();
	mas1.setrandom();
	cout<<endl;
	mas1.print();
	return 0;
}