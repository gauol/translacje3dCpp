#pragma once

#include <string>
#include <sstream>

#ifndef _UTILS_H
#define _UTILS_H

namespace mathf {
	const float pi= 3.14159265358979323846f;
	const float e= 2.71828182845904523536f;

	float toRad(float deg);
	float toDeg(float rad);
	int round(float x);
}

namespace mathd {
	const double pi= 3.14159265358979323846;
	const double e= 2.71828182845904523536;

	double toRad(double deg);
	double toDeg(double rad);
	int round(double x);
}


std::string FloatToStr(float);
std::string IntToStr(int);
std::wstring FloatToWStr(float);
std::wstring IntToWStr(int);
int WStrToInt(std::wstring);
float WStrToFloat(std::wstring);
int TcharToInt(TCHAR ch[]);
float TcharToFloat(TCHAR ch[]);
std::wstring StrToWStr(const std::string&);
std::string WStrToStr(std::wstring);
std::string LPWSTRtoStr(LPWSTR);

#endif