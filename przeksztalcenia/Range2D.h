#pragma once
class Range2D
{

public:
	Range2D(void);
	Range2D(float x1, float y1, float x2, float y2);
	~Range2D(void);

	float GetX1();
	float GetY1();
	float GetX2();
	float GetY2();
	float GetWidth();
	float GetHeight();
	void Set(float x1, float y1, float x2, float y2);
	void Scale(float s);
	float * Get();

private:
	float x1, x2, y1, y2;

};

