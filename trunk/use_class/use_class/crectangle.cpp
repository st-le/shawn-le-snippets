#include "stdafx.h"
#include "crectangle.h"

CRectangle::CRectangle (int a, int b)   // constructor
{
	width = new int;
	height = new int;
	*width = a;
	*height = b;

	lalala = 3;
}

CRectangle::CRectangle ()   // overloading constructor
{
	width = new int;
	height = new int;
	*width = 5;
	*height = 5;

	lalala = 3;
}

CRectangle::~CRectangle()	// destructor
{
	delete width;
	delete height;
}
