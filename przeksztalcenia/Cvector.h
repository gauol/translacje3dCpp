#pragma once
class Cvector
{
	float V[4];
	friend class Cmatrix;

public:
	Cvector(void);
	Cvector(float x, float y, float z);
	~Cvector(void);

	void SetVector(float x, float y, float z);
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);

	float GetX(void);
	float GetY(void);
	float GetZ(void);

	Cvector GetOrto(void);
	Cvector GetIzo();
	Cvector GetPersp(float x, float y, float z);



	//void PrintVector(void);

	Cvector operator + (const Cvector a);
	Cvector operator - (const Cvector a);

};

