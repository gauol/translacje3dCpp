#include "stdafx.h"
#include "Cmatrix.h"
#include <math.h>

#define Mx this->M

// Mx[z][x]

Cmatrix::Cmatrix(void)
{
	this->SetZero();
}


Cmatrix::~Cmatrix()
{
}

void Cmatrix::SetZero(void) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			Mx[i][j] = 0;
	Mx[3][3] = 1;
}

void Cmatrix::SetIdentity(void) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (i == j)
				Mx[i][j] = 1.0f;
			else
				Mx[i][j] = 0.0f;
}

void Cmatrix::SetOrto() {
	this->SetIdentity();
	Mx[2][2] = 0;
}

void Cmatrix::SetPersp(Cvector e) {
	this->SetIdentity();
	Mx[3][3] = 0;
	Mx[0][2] = e.GetX() / e.GetZ();
	Mx[1][2] = e.GetY() / e.GetZ();
	Mx[3][2] = 1 / e.GetZ();
}


Cmatrix Cmatrix::SetTranslate(float tx, float ty, float tz) {
	this->SetIdentity();
	Mx[0][3] = tx;  // wpierw wiersz potem kolumna M[wiersz][kolumna]
	Mx[1][3] = ty;
	Mx[2][3] = tz;
	return *this;
}

Cmatrix Cmatrix::SetRotateOX(float phi) {
	this->SetZero();
	Mx[1][1] = cosf(phi);
	Mx[1][2] = -sinf(phi);
	Mx[2][1] = sinf(phi);
	Mx[2][2] = cosf(phi);
	Mx[0][0] = 1;
	return *this;
}

Cmatrix Cmatrix::SetRotateOY(float phi) {
	this->SetZero();
	Mx[0][0] = cosf(phi);
	Mx[0][2] = sinf(phi);
	Mx[2][0] = -sinf(phi);
	Mx[2][2] = cosf(phi);
	Mx[1][1] = 1;
	return *this;
}

Cmatrix Cmatrix::SetRotateOZ(float phi) {
	this->SetZero();
	Mx[0][0] = cosf(phi);
	Mx[0][1] = -sinf(phi);
	Mx[1][0] = sinf(phi);
	Mx[1][1] = cosf(phi);
	Mx[2][2] = 1;
	return *this;
}

Cmatrix Cmatrix::SetScale(float sx, float sy, float sz) {
	this->SetZero();
	Mx[0][0] = sx;
	Mx[1][1] = sy;
	Mx[2][2] = sz;
	return *this;
}

Cmatrix Cmatrix::SetScale(float s) {
	this->SetZero();
	Mx[3][3] = 1/s;
	return *this;
}

#ifdef consoleDebug
void Cmatrix::PrintMartix() {
	printf("\n\r");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			printf("%.5f \t ", Mx[i][j]);
		printf("\n");
	}
	//printf("\n\r");
}
#endif

Cmatrix Cmatrix::operator * (const Cmatrix B) {
	Cmatrix result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float suma = 0.0f;
			for (size_t k = 0; k < 4; k++)
				suma += Mx[i][k] * B.M[i][k];
			result.M[i][j] = suma;
		}
	}
		return result;
}

Cvector Cmatrix::operator * (const Cvector x) {
	Cvector result;
	for (size_t row = 0; row < 4; row++){
		float suma = 0.0f;
		for (size_t j = 0; j < 4; j++)
			suma += Mx[row][j] * x.V[j];
		result.V[row] = suma;
	}
	return result;
}
