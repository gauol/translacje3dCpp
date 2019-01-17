#pragma once
#include "Cvector.h"

class Cmatrix
{
	float M[4][4];

public:
	Cmatrix(void);
	~Cmatrix(void);
	void SetZero(void); //zeruje maciez
	void SetIdentity(void); // maciez jednostkowa - jedynki na diagonalach
	void SetOrto();
	void SetPersp(Cvector e);
	Cmatrix SetTranslate(float tx, float ty, float tz);
	Cmatrix SetRotateOX(float phi);
	Cmatrix SetRotateOY(float phi);
	Cmatrix SetRotateOZ(float phi);
	Cmatrix SetScale(float sx, float sy, float sz);
	Cmatrix SetScale(float s);

	#ifdef consoleDebug
	void PrintMartix();
	#endif

	Cmatrix operator * (const Cmatrix B);
	Cvector operator * (const Cvector x);

};

