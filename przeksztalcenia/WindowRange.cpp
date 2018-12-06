#include "StdAfx.h"
#include "WindowRange.h"
#include "Utils.h"


WindowRange::WindowRange(HWND hwnd)
{
	this->hwnd= hwnd;
	this->bProp= true;
	IniRange();
}


WindowRange::~WindowRange(void)
{
}

void WindowRange::IniRange()
{
	int iw, ih;
	GetWindowSize(&iw, &ih);
	if (iw <= 0 || ih <= 0) 
	{
		range.Set(-1, -1, 1, 1);
		sx= 1;
		sy= 1;
		k= 1;
	}

	float w= 0.5f*iw;
	float h= 0.5f*ih;
	range.Set(-w, -h, w, h);
	sx= 1;
	sy= 1;
	k= w/h;
}

float WindowRange::GetX1()
{
	return range.GetX1();
}

float WindowRange::GetY1()
{
	return range.GetY1();
}

float WindowRange::GetX2()
{
	return range.GetX2();
}

float WindowRange::GetY2()
{
	return range.GetY2();
}

float WindowRange::GetWidth()
{
	return range.GetWidth();
}

float WindowRange::GetHeight()
{
	return range.GetHeight();
}

float WindowRange::GetAspectRatio()
{
	return range.GetWidth()/range.GetHeight();
}

void WindowRange::GetWindowSize(float * w, float * h)
{
	RECT r;
	GetClientRect(hwnd, &r);
	*w= (float) (r.right-r.left);
	*h= (float) (r.bottom-r.top);
}

void WindowRange::GetWindowSize(int * w, int * h)
{
	RECT r;
	GetClientRect(hwnd, &r);
	*w= r.right-r.left;
	*h= r.bottom-r.top;
}

bool WindowRange::GetProportional()
{
	return bProp;
}

void WindowRange::SetProportional(bool prop)
{
	bProp= prop;
	SetRange(range0.GetX1(), range0.GetY1(), range0.GetX2(), range0.GetY2());
}

void WindowRange::SetRange(float x1, float y1, float x2, float y2)
{
	float k1, k2, dim, marg;

	range0.Set(x1, y1, x2, y2);
	float w= range0.GetWidth();
	float h= range0.GetHeight();

	float w1, h1;
	GetWindowSize(&w1, &h1);
	if (w1 == 0 || h1 == 0) return;

	if (bProp)
	{
		k= w1/h1;	
		k1= k;
		k2= w/h;
		if (k1 <= k2) 
		{
			dim= w/k1;
			marg= (dim-h)*0.5f;
			range.Set(x1, y1-marg, x2, y2+marg);
		}
		else 
		{
			dim= h*k1;
			marg= (dim-w)*0.5f;
			range.Set(x1-marg, y1, x2+marg, y2);
		}	
	}
	else
	{
		range.Set(x1, y1, x2, y2);
	}
	
	sx= GetWidth()/w1;
	sy= GetHeight()/h1;
}

void WindowRange::Update(HWND hwnd)
{
	this->hwnd= hwnd;
	SetRange(range0.GetX1(), range0.GetY1(), range0.GetX2(), range0.GetY2());
}

void WindowRange::ScaleRange(float s)
{
	range.Scale(s);
}

float WindowRange::GetScaleX()
{
	return sx;
}

float WindowRange::GetScaleY()
{
	return -sy;
}

float WindowRange::GetTranslationX()
{
	return GetX1();
}

float WindowRange::GetTranslationY()
{
	return GetY2();
}