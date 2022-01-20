#include <iostream>
#include <exception>
#include <cmath>
using namespace std;

template <class T> class Massive
{
	T* p;
	int length;
public:
	Massive(int a)
	{
		p = (T*)malloc(a * sizeof(T));
		if (p == nullptr)
		{
			throw std::bad_alloc();
		}
		length = a;
	}
	Massive(Massive& parent)
	{
		length = parent.length;
		p = (T*)malloc(length * sizeof(T));
		if (p == nullptr)
		{
			throw std::bad_alloc();
		}
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
	void set(T a, int number)
	{
		if ((a>100) || (a<-100))
		{
			throw std::invalid_argument("INVALID ARGUMENT");
		}
		if((number<0) || (number >=length))
		{
			throw std::out_of_range("OUT OF RANGE");
		}
		else
		{
			p[number] = a;
		}
	}
	void setZero()
	{
		for (int i = 0; i < length; i++)
		{
			p[i] =0;
		}
	}
	void get(int number)
	{
		if ((number <0) || (number >= length))
		{
			throw std::out_of_range("OUT OF RANGE");
		}
		else
		{
			std::cout << p[number] << std::endl;
		}
		
	}
	void add(T a)
	{
		if ((a > 100) and (a < -100))
		{
			throw std::invalid_argument("INVALID ARGUMENT");
		}
		else
		{
			int* p2 = (int*)malloc((length + 1) * sizeof(int));
			if (p2 == nullptr)
			{
				throw std::bad_alloc();
			}
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
		int min_length;
		if (length < second.length)
		{
			min_length = length;
		}
		else
		{
			min_length = second.length;
		}
		for (int i = 0; i < min_length; i++)
		{
			p[i] += second.p[i];
		}
	}
	void minus(Massive& second)
	{
		int min_length;
		if (length < second.length)
		{
			min_length = length;
		}
		else
		{
			min_length = second.length;
		}
		for (int i = 0; i < min_length; i++)
		{
			p[i] -= second.p[i];
		}
		
	}
	void test()
	{
		this->setZero();
		this->set(5, 2);
		this->get(2);
		cout << endl;
		this->print();
		cout << endl;
		Massive mas2(*this);
		mas2.print();
		cout << endl;
		this->add(6);
		this->print();
		this->plus(mas2);
		cout << endl;
		this->print();
		cout << endl;
		this->print();
		cout << endl;
		mas2.print();
		cout << endl;
		*this = mas2;
		this->print();
	}
	void operator= (Massive<T>& mas)
	{
		int min_length;
		if (this->length < mas.length)
		{
			min_length = this->length;
		}
		else
		{
			min_length = mas.length;
		}
		for (int i = 0; i < min_length; i++)
		{
			this->p[i] = mas.p[i];
		}
	}
	friend std::ostream& operator<< (std::ostream& out, const Massive<T>& mas)
	{
		for (int i = 0; i < mas.length;i++)
		{
			out << mas.p[i];
		}
		return out;
	}
	float distance(Massive<T>& mas)
	{
		throw std::logic_error();
	}
};
template <>
void Massive<int>::set(int val, int number)
{
	if ((val > 100) || (val < -100))
	{
		throw std::invalid_argument("INVALID ARGUMENT");
	}
	if ((number < 0) || (number >= length))
	{
		throw std::out_of_range("OUT OF RANGE");
	}
	else
	{
		p[number] = val;
	}
}
template<>
float Massive<int>::distance(Massive<int>& mas)
{
	if (this->length != mas.length)
	{
		cout << "ERROR. Massives have different Length!!!" << endl;
		return -1;
	}
	else
	{
		int dist=0;
		Massive<int> difference = *this;
		difference.minus(mas);
		for (int i = 0; i < this->length; i++)
		{
			dist += (difference.p[i])*(difference.p[i]);
		}
		return sqrt(dist);
	}
}
int main()
{
	try
	{
		Massive<int> mas1(5);
		mas1.test();
		Massive<int> mas2(2);
		Massive<int> mas3(2);
		mas2.setZero();
		mas3.setZero();
		mas2.set(1, 0);
		mas3.set(1, 1);
		cout << "Distance between mas2 and mas3: " << mas2.distance(mas3) << endl;
	}
	catch(std::bad_alloc e3)
	{
		std::cout << "bad_alloc" << std::endl;
	}
	catch (std::out_of_range e)
	{
		cout<<e.what()<<endl;
	}
	catch (std::invalid_argument e2)
	{
		cout<<e2.what()<<endl;
	}
	return 0;
}