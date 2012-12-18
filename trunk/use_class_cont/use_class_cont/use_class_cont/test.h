#pragma once

class test
{
private:
	
	int a;
	int b;

public:
	int lala;

	test(void);
	test(int inp1, int inp2);

	int plus(int a, int b);
	int minus(int a, int b);
	int plus(void);
	int minus(void);

	~test(void);
};
