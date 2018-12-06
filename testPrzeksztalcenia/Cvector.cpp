#include "stdafx.h"
#include "Cvector.h"


Cvector::Cvector()
{
	this->V[0] = 0;
	this->V[1] = 0;
	this->V[2] = 1;
}

Cvector::Cvector(float x, float y)
{
	this->V[0] = x;
	this->V[1] = y;
	this->V[2] = 1;
}

Cvector::~Cvector()
{
}

void Cvector::SetVector(float x, float y) {
	this->V[0] = x;
	this->V[1] = y;
}
void Cvector::SetX(float x) {
	this->V[0] = x;
}

void Cvector::SetY(float y) {
	this->V[1] = y;
}

float Cvector::GetX(void) {
	return this->V[0];
}

float Cvector::GetY(void) {
	return this->V[1];
}

void Cvector::PrintVector(void) {
	printf("[%.5f,%.5f,%d]", this->V[0], this->V[1], (int)this->V[2]);
}

Cvector Cvector::operator + (const Cvector a) {
	Cvector suma;
	for (int i = 0; i < 2; i++)
		suma.V[i] = this->V[i] + a.V[i];
	return suma;
}

Cvector Cvector::operator - (const Cvector a) {
	Cvector roznica;
	for (int i = 0; i < 3; i++)
		roznica.V[i] = this->V[i] + a.V[i];
	return roznica;
}