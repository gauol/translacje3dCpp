#pragma once
#include "Cvector.h"

class Cmatrix
{
	float M[3][3];

public:
	Cmatrix(void);
	~Cmatrix(void);
	void SetZero(void); //zeruje maciez
	void SetIdentity(void); // maciez jednostkowa - jedynki na diagonalach
	void SetTranslate(float tx, float ty);
	void SetRotate(float phi);
	void SetScale(float sx, float sy);
	void SetShearY(float beta);
	void SetShearX(float alpha);
	void SetSymerticX(void);
	void SetSymetricY(void);
	void SetSymetricO(void);


	float Determinant();
	void PrintMartix();

	Cmatrix operator * (const Cmatrix B);
	Cvector operator * (const Cvector x);

};

