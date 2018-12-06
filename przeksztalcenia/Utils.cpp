#include "stdafx.h"
#include "Utils.h"
#include "math.h"

using namespace std;

namespace mathf {

float toRad(float deg)
{
	return deg*pi/180.0f;
}

float toDeg(float rad)
{
	return rad*180.0f/pi;
}

int round(float x)
{
	float f, i;
	f= modff(x, &i);
	if (f <= 0.5f) return (int) floorf(x);
	return (int) ceilf(x);
}

}

namespace mathd {

double toRad(double deg)
{
	return deg*pi/180.0;
}

double toDeg(double rad)
{
	return rad*180.0/pi;
}

int round(double x)
{
	float f, i;
	f= modf(x, &i);
	if (f <= 0.5) return (int) floor(x);
	return (int) ceil(x);
}

}

string FloatToStr(float x)
{
	ostringstream buf;
	buf << x;
	return buf.str();
}

string IntToStr(int i)
{
	ostringstream buf;
	buf << i;
	return buf.str();
}

wstring FloatToWStr(float x)
{
	ostringstream buf;
	buf << x;
	return StrToWStr(buf.str());
}

wstring IntToWString(int i)
{
	ostringstream buf;
	buf << i;
	return StrToWStr(buf.str());
}

int WStrToInt(wstring ws)
{
	return _wtoi(ws.c_str());
}

float WStrToFloat(wstring ws)
{
	return (float) atof(WStrToStr(ws).c_str());
}

int TcharToInt(TCHAR ch[])
{
	wstring ws= ch;
	return WStrToInt(ws);
}

float TcharToFloat(TCHAR ch[])
{
	wstring ws= ch;
	return WStrToFloat(ws);
}

wstring StrToWStr(const string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    wstring r(buf);
    delete[] buf;
    return r;
}

string WStrToStr(wstring ws)
{
	string s;
	s.resize(ws.size()); //make enough room in s for the string
	copy(ws.begin(), ws.end(), s.begin()); //copy it
	return s;
}

string LPWSTRtoStr(LPWSTR lps)
{
	wstring ws= lps;
	string s;
	s.resize(ws.size()); //make enough room in s for the string
	copy(ws.begin(), ws.end(), s.begin()); //copy it
	return s;
}