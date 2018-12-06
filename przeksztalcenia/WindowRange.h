#pragma once

#include "Range2D.h"

class WindowRange
{

public:
	WindowRange(HWND hwnd);
	~WindowRange(void);

	float GetX1();
	float GetY1();
	float GetX2();
	float GetY2();
	float GetWidth();
	float GetHeight();
	float GetAspectRatio();
	bool GetProportional();
	void SetRange(float x1, float y1, float x2, float y2);
	void SetProportional(bool prop);
	void Update(HWND hwnd);
	void ScaleRange(float s);
	float GetScaleX();
	float GetScaleY();
	float GetTranslationX();
	float GetTranslationY();

	void GetWindowSize(float * w, float * h);
	void GetWindowSize(int * w, int * h);

private:
	HWND hwnd;
	Range2D range;
	Range2D range0;
	float k, sx, sy;
	bool bProp;

	void IniRange();

};

