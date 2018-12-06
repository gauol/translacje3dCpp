// testPrzeksztalcenia.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Cvector.h"
#include "Cmatrix.h"

using namespace std;

int main()
{
	cout << "hello" << endl;
	Cvector a = Cvector(5.56124, 1.15661), b, c;
	b.SetVector(6.123, 9.666);

	a.PrintVector(); printf("\n");
	b.PrintVector(); printf("\n");

	c = a + b;
	c.PrintVector(); printf("\n");

	Cmatrix y;
	y.SetTranslate(12, 3);
	y.PrintMartix();
    return 0;
}

