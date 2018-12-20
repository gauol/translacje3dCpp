#include "stdafx.h"
#include "Cvector.h"
#include "Cmatrix.h"

#define X this->V[0]
#define Y this->V[1]
#define Z this->V[2]

Cvector::Cvector()
{
	X = 0;
	Y = 0;
	Z = 0;
	this->V[3] = 1;
}

Cvector::Cvector(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
	this->V[3] = 1;
}

Cvector::~Cvector()
{
}

void Cvector::SetVector(float x, float y, float z) {
	X = x;
	Y = y;
	Z = z;
}
void Cvector::SetX(float x) {
	X = x;
}

void Cvector::SetY(float y) {
	Y = y;
}

void Cvector::SetZ(float z) {
	Z = z;
}

float Cvector::GetX(void) {
	return X;
}

float Cvector::GetY(void) {
	return Y;
}

float Cvector::GetZ(void) {
	return Z;
}

Cvector Cvector::GetOrto(void) {
	Cmatrix mat;
	mat.SetOrto();
	Cvector rt = mat * *this;
	return rt;
}

Cvector Cvector::GetIzo(float phi) {
	Cmatrix mat;
	mat.SetOrto();
	Cvector rt = mat * *this;
	return rt;
}

//void Cvector::PrintVector(void) {
//	printf("[%.5f,\t %.5f,\t %.5f,\t %d] \n\r", X, Y, Z, (int)this->V[3]);
//}

Cvector Cvector::operator + (const Cvector a) {
	Cvector suma;
	for (int i = 0; i < 3; i++)
		suma.V[i] = this->V[i] + a.V[i];
	return suma;
}

Cvector Cvector::operator - (const Cvector a) {
	Cvector roznica;
	for (int i = 0; i < 4; i++)
		roznica.V[i] = this->V[i] + a.V[i];
	return roznica;
}
