#include "StdAfx.h"
#include "Range2D.h"


Range2D::Range2D(void)
{
	Set(0, 0, 0, 0);
}

Range2D::Range2D(float x1, float y1, float x2, float y2)
{
	Set(x1, y1, x2, y2);
}

Range2D::~Range2D(void)
{
}


float Range2D::GetX1()
{
	return x1;
}

float Range2D::GetY1()
{
	return y1;
}

float Range2D::GetX2()
{
	return x2;
}

float Range2D::GetY2()
{
	return y2;
}

float Range2D::GetWidth()
{
	return x2-x1;
}

float Range2D::GetHeight()
{
	return y2-y1;
}

void Range2D::Set(float x1, float y1, float x2, float y2)
{
	this->x1= x1;	
	this->y1= y1;
	this->x2= x2;
	this->y2= y2;
}

void Range2D::Scale(float s)
{
	float x0= 0.5f * (x1 + x2);
	float y0= 0.5f * (y1 + y2);
	float mx= GetWidth()*0.5f*s;
	float my= GetHeight()*0.5f*s;
	Set(x0-mx, y0-my, x0+mx, y0+my);
}
