#include "stdafx.h"
#include "Cvector.h"
#include "Cmatrix.h"
#include <cmath>

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
	Cvector rt = mat * (*this);
	return rt;
}

Cvector Cvector::GetIzo() {
	Cmatrix mat;
	Cvector rt(this->GetX(), this->GetY(), this->GetZ());
	mat.SetRotateOY(0.7853981634);
	rt = mat * rt;
	mat.SetRotateOX(asin(tan(0.5235987756)));
	rt = mat * rt;
	mat.SetOrto();
	rt = mat * rt;

	return rt;
}

Cvector Cvector::GetPersp(Cvector theta, Cvector C, Cvector e) {
	Cmatrix buff;
	Cvector v(this->GetX(), this->GetY(), this->GetZ());

	v = v - C;

	buff.SetRotateOX(theta.V[0]);	
	v = buff * v;

	buff.SetRotateOY(theta.V[1]);
	v = buff * v; 

	buff.SetRotateOZ(theta.V[2]);
	v = buff * v;

	buff.SetPersp(e);
	v = buff * v;

	v = Cvector(v.V[0] / v.V[3], v.V[1] / v.V[3], 0);

	return v;
}


#ifdef consoleDebug
void Cvector::PrintVector(void) {
	printf("[%.5f,\t %.5f,\t %.5f,\t %.5f] \n\r", X, Y, Z, this->V[3]);
}
#endif

Cvector Cvector::operator + (const Cvector a) {
	Cvector suma;
	for (int i = 0; i < 3; i++)
		suma.V[i] = this->V[i] + a.V[i];
	return suma;
}

Cvector Cvector::operator - (const Cvector a) {
	Cvector roznica;
	for (int i = 0; i < 3; i++)
		roznica.V[i] = this->V[i] - a.V[i];
	return roznica;
}
