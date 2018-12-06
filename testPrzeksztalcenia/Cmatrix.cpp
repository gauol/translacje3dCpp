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
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			this->M[i][j] = 0;
	this->M[2][2] = 1;
}

void Cmatrix::SetIdentity(void) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (i == j)
				this->M[i][j] = 1.0f;
			else
				this->M[i][j] = 0.0f;
}

void Cmatrix::SetTranslate(float tx, float ty) {
	this->SetIdentity();
	this->M[2][0] = tx;
	this->M[2][1] = ty;
}

void Cmatrix::SetRotate(float phi) {\
	this->SetZero();
	this->M[0][0] = cosf(phi);
	this->M[0][1] = -sinf(phi);
	this->M[1][0] = sinf(phi);
	this->M[1][1] = cosf(phi);
}

void Cmatrix::SetScale(float sx, float sy) {
	this->SetZero();
	this->M[0][0] = sx;
	this->M[1][1] = sy;
}

void Cmatrix::SetShearY(float beta) {
	this->SetIdentity();
	this->M[1][0] = tanf(beta);
}

void Cmatrix::SetShearX(float alpha) {
	this->SetIdentity();
	this->M[0][1] = tanf(alpha);
}

void Cmatrix::SetSymerticX(void) {
	this->SetIdentity();
	this->M[1][1] = -1.0f;
}

void Cmatrix::SetSymetricY(void) {
	this->SetIdentity();
	this->M[0][0] = -1.0f;
}

void Cmatrix::SetSymetricO(void) {
	this->SetIdentity();
	for (size_t i = 0; i < 2; i++)
		this->M[i][i] = -1.0f;
}

float Cmatrix::Determinant(void) {
	return ((this->M[0][0] * this->M[1][1]) - (this->M[0][1] * this->M[1][0]));
}

void Cmatrix::PrintMartix() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			printf("%.5f \t ", this->M[j][i]);
		printf("\n");
	}
}

Cmatrix Cmatrix::operator * (const Cmatrix B) {
	Cmatrix result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float suma = 0.0f;
			for (size_t k = 0; k < 3; k++)
				suma += this->M[i][k] * B.M[i][k];
			result.M[i][j] = suma;
		}
	}
		return result;
}

Cvector operator * (const Cmatrix B, const Cvector x) {
	Cvector result;
	for (size_t i = 0; i < 3; i++){
		float suma = 0.0f;
		for (size_t j = 0; j < 2; j++)
			suma += B.M[i][j] * x.V[j];
		result.V[i] = suma;
	}
	return result;
}

