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
	void SetTranslate(float tx, float ty, float tz);
	void SetRotateOX(float phi);
	void SetRotateOY(float phi);
	void SetRotateOZ(float phi);
	void SetScale(float sx, float sy, float sz);
	void SetScale(float s);

	//void PrintMartix();

	Cmatrix operator * (const Cmatrix B);
	Cvector operator * (const Cvector x);

};

