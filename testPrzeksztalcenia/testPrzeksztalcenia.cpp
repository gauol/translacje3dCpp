// testPrzeksztalcenia.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Cvector.h"
#include "Cmatrix.h"
#include <windows.h>   // WinApi header

using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void printOK(void) {
	SetConsoleTextAttribute(hConsole, 10);
	printf("OK\n\r");
	SetConsoleTextAttribute(hConsole, 7);
}

int main()
{

	cout << "hello" << endl;
	Cvector a = Cvector(5.56124, 1.15661, 2.33), b, c;
	b.SetVector(6.123, 9.666, 1.123);

	a.PrintVector(); 
	b.PrintVector(); 

	c = a + b;
	c.PrintVector(); 

	Cmatrix y;
	y.SetTranslate(12, 3, 2);  
	y.PrintMartix();
	printOK();
	
	// cosf(2) = -0.41615
	// sinf(phi) = 0.90930

	// [0][0] = cosf(phi)  --- [0][2] = sinf(phi)
	// [2][0] = -sinf(phi) --- [2][2] = cosf(phi)
	y.SetRotateOX(2);		
	y.PrintMartix();
	printOK();

	// [0][0] = cosf(phi)  =  --- [0][2] = sinf(phi);
	// [2][0] = -sinf(phi) =  --- [2][2] = cosf(phi);
	y.SetRotateOY(2);
	y.PrintMartix();
	printOK();

	// [0][0] = cosf(phi) --- [0][1] = -sinf(phi)
	// [1][0] = sinf(phi) --- [1][1] = cosf(phi)
	y.SetRotateOZ(2);
	y.PrintMartix();
	printOK();

    return 0;
}

