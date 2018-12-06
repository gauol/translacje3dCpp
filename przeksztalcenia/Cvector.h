#pragma once
class Cvector
{
public:
	Cvector(void);
	Cvector(float x, float y);
	~Cvector(void);

	void SetVector(float x, float y);
	void SetX(float x);
	void SetY(float y);

	float GetX(void);
	float GetY(void);

	void PrintVector(void);

	Cvector operator + (const Cvector a);
	Cvector operator - (const Cvector a);

	float V[3];
};

