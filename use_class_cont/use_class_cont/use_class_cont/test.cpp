#include "StdAfx.h"
#include "test.h"




int test::plus(int inp1, int inp2)
{
	return (inp1 + inp2);

}

int test::plus()
{
	return (a + b);

}

int test::minus(int inp1, int inp2)

{
	return (inp1-inp2);


}

int test::minus()
{
	return (a-b);
}


test::test(void)
{
	a = 10;
	b = 5;
	lala = 7;
}

test::test(int inp1, int inp2)
{
	a = inp1;
	b = inp2;
	lala = 7;
}


test::~test(void)
{
}
