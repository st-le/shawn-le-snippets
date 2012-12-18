#include <iostream>

using namespace std;


char chrArr[] = {1, 3, 5, 9, 11, 13};
char ch = 5;

const int MAX = 100;


template <class T>   // func template
T abs (T n)      
{
	return (n < 0)? -n : n;
}

template <class atype> 
int find(atype* array, atype value, int size)  // func template
{

	for (int j = 0; j < size; j++)
		if (array[j] == value)
			return j;
	return -1;
}

template <class atype, class btype> 
int find(atype* array, atype value, btype size)  // func template
{

	for (int j = 0; j < size; j++)
		if (array[j] == value)
			return j;
	return static_cast<btype>(-1);
}


template <class Type>    // class template
class Stack
{
private:
	Type st[MAX];
	int top;
public:
	Stack()
	{ top = -1;	}
	void push(Type var)
	{
		st[++top] = var;
	}
	Type pop()
	{
		return st[top--];
	}
};

template <class Type>		// class template with separate declaration
class Stack_sep
{
private:
	Type st[MAX];
	int top;
public:
	Stack_sep();
	
	void push(Type var);

	Type pop();
};


template <class Type>
Stack_sep<Type>::Stack_sep()
{ top = -1;	};

template <class Type>
void Stack_sep<Type>::push(Type var)
{
	st[++top] = var;
}

template <class Type>
Type Stack_sep<Type>::pop()
{
	return st[top--];
}


int main()
{
	int num_int = -7;
	float num_f = -3.5;

	cout << "test result = " <<  abs(num_int) << endl;  // calling func template no need type define
	cout << "test result = " <<  abs(num_f) << endl;

	cout << "\n 5 in chrArray: index= " << find(chrArr, ch, 6) << endl;  


	Stack<float> s1;

	s1.push(111.1F);
	s1.push(222.2F);
	s1.push(333.3F);
	cout << "1: " << s1.pop() << endl;
	cout << "2: " << s1.pop() << endl;
	cout << "3: " << s1.pop() << endl;


	Stack_sep<long> st;
	st.push(12341233L);
	st.push(1234343333L);
	st.push(555555555L);
	cout << "1: " << st.pop() << endl;
	cout << "2: " << st.pop() << endl;
	cout << "3: " << st.pop() << endl;

	getchar();

	return 0;
}