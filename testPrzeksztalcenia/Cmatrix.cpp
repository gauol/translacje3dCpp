#include "stdafx.h"
#include "Cmatrix.h"
#include <math.h>

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
			this->M[i][j] = 0;
	this->M[3][3] = 1;
}

void Cmatrix::SetIdentity(void) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (i == j)
				this->M[i][j] = 1.0f;
			else
				this->M[i][j] = 0.0f;
}

void Cmatrix::SetOrto() {
	this->SetIdentity();
	this->M[2][2] = 0;
}


void Cmatrix::SetTranslate(float tx, float ty, float tz) {
	this->SetIdentity();
	this->M[0][3] = tx;  // wpierw wiersz potem kolumna M[wiersz][kolumna]
	this->M[1][3] = ty;
	this->M[2][3] = tz;
}

void Cmatrix::SetRotateOX(float phi) {
	this->SetZero();
	this->M[1][1] = cosf(phi);
	this->M[1][2] = -sinf(phi);
	this->M[2][1] = sinf(phi);
	this->M[2][2] = cosf(phi);
	this->M[0][0] = 1;

}

void Cmatrix::SetRotateOY(float phi) {
	this->SetZero();
	this->M[0][0] = cosf(phi);
	this->M[0][2] = sinf(phi);
	this->M[2][0] = -sinf(phi);
	this->M[2][2] = cosf(phi);
	this->M[1][1] = 1;
}

void Cmatrix::SetRotateOZ(float phi) {
	this->SetZero();
	this->M[0][0] = cosf(phi);
	this->M[0][1] = -sinf(phi);
	this->M[1][0] = sinf(phi);
	this->M[1][1] = cosf(phi);
	this->M[2][2] = 1;
}

void Cmatrix::SetScale(float sx, float sy, float sz) {
	this->SetZero();
	this->M[0][0] = sx;
	this->M[1][1] = sy;
	this->M[2][2] = sz;
}

void Cmatrix::SetScale(float s) {
	this->SetIdentity();
	this->M[3][3] = 1/s;
}

void Cmatrix::PrintMartix() {
	printf("\n\r");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			printf("%.5f \t ", this->M[i][j]);
		printf("\n");
	}
	//printf("\n\r");
}

Cmatrix Cmatrix::operator * (const Cmatrix B) {
	Cmatrix result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float suma = 0.0f;
			for (size_t k = 0; k < 4; k++)
				suma += this->M[i][k] * B.M[i][k];
			result.M[i][j] = suma;
		}
	}
		return result;
}

Cvector Cmatrix::operator * (const Cvector x) {
	Cvector result;
	for (size_t i = 0; i < 4; i++){
		float suma = 0.0f;
		for (size_t j = 0; j < 4; j++)
			suma += this->M[i][j] * x.V[j];
		result.V[i] = suma;
	}
	return result;
}
