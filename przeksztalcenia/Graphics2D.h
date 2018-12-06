#pragma once

#include "WindowRange.h"
#include "Utils.h"

class Graphics2D
{

public:
	static struct POINT2D {  // punkt o wspó³rzêdnych rzeczywistych
		float x;
		float y;
	};

	static enum FontStyle {  // styl czcionki
		fs_NORMAL = 2,
		fs_BOLD = 4,
		fs_ITALIC = 8,
		fs_UNDERLINE = 16,
		fs_STRIKE_OUT = 32
	};

	static enum Color{  // kolory predefiniowane
		cl_WHITE = RGB(255, 255, 255),
		cl_BLACK = RGB(0, 0, 0),
		cl_RED = RGB(255, 0, 0),
		cl_GREEN = RGB(0, 255, 0),
		cl_DARK_GREEN = RGB(0, 100, 0),
		cl_BLUE = RGB(0, 0, 255),
		cl_LIGHT_BLUE = RGB(173, 216, 230),
		cl_YELLOW = RGB(255, 255, 0),
		cl_LIGHT_YELLOW = RGB(255, 255, 224),
		cl_ORANGE = RGB(255, 140, 0),
		cl_BROWN = RGB(139, 69, 19),
		cl_LIGHT_GRAY = RGB(220, 220, 220),
		cl_GRAY = RGB(190, 190, 190),
		cl_DARK_GRAY = RGB(105, 105, 105),
		cl_VIOLET = RGB(148, 0, 211),
		cl_CYAN = RGB(0, 255, 255)
	};

private:

	static void DecodeFontStyle(int style, int * weight, DWORD * italic, DWORD * underline, DWORD * strikeout)
	{
		switch (style)
		{
		case fs_BOLD:
			*weight= FW_BOLD;
			break;
		case fs_ITALIC:
			*italic= true;
			break;
		case fs_UNDERLINE:
			*underline= true;
			break;
		case fs_STRIKE_OUT:
			*strikeout= true;
			break;
		case fs_BOLD + fs_ITALIC:
			*weight= FW_BOLD;
			*italic= true;
			break;
		case fs_BOLD + fs_ITALIC + fs_UNDERLINE:
			*weight= FW_BOLD;
			*italic= true;
			*underline= true;
			break;
		case fs_BOLD + fs_ITALIC + fs_UNDERLINE + fs_STRIKE_OUT:
			*weight= FW_BOLD;
			*italic= true;
			*underline= true;
			*strikeout= true;
			break;
		case fs_BOLD + fs_UNDERLINE + fs_STRIKE_OUT:
			*weight= FW_BOLD;
			*underline= true;
			*strikeout= true;
			break;
		case fs_BOLD + fs_UNDERLINE:
			*weight= FW_BOLD;
			*underline= true;
			break;
		case fs_ITALIC + fs_UNDERLINE + fs_STRIKE_OUT:
			*italic= true;
			*underline= true;
			*strikeout= true;
			break;
		case fs_ITALIC + fs_STRIKE_OUT:
			*italic= true;
			*strikeout= true;
			break;
		case fs_UNDERLINE + fs_STRIKE_OUT:
			*underline= true;
			*strikeout= true;
			break;
		}
	}

public:
	Graphics2D(void);
	Graphics2D(HDC hdc, WindowRange * wr);
	~Graphics2D(void);

	void SetWindow(HDC hdc, WindowRange * wr);
	HDC GetDC();
	WindowRange * GetWindowRange();
	void Update();

	float XfromPixels(int xp);
	float YfromPixels(int yp);
	int XtoPixels(float x);
	int YtoPixels(float y);
	void FromPixels(int xp, int yp, float * x, float * y);
	void ToPixels(float x, float y, int * xp, int * yp);
	void Pt2DtoPt(POINT2D * pt2, POINT * pt, int n);
	void XYtoPt(float * X, float * Y, POINT * pt, int n);

	void DrawPoint(float x, float y);
	void MoveTo(float x, float y);
	void DrawLineTo(float x, float y);
	void DrawLine(float x1, float y1, float x2, float y2);
	void DrawArc(float x, float y, float r, float ang0, float ang);
	void DrawArc(float x1, float y1, float x2, float y2, float ang0, float ang);
	void DrawArc2(float x1, float y1, float a, float b, float ang0, float ang);
	void DrawPolyline(POINT2D * pt2, int n);
	void DrawPolyline(float * X, float * Y, int n);
	void DrawRectangle(float x1, float y1, float x2, float y2);
	void DrawEllipse(float x1, float y1, float x2, float y2);
	void DrawEllipse2(float x, float y, float a, float b);
	void DrawCircle(float x, float y, float r);
	void DrawPolygon(POINT2D * pt2, int n);
	void DrawPolygon(float * X, float * Y, int n);
	void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);

	void FillBackground(COLORREF col = cl_WHITE);
	void SetBackground(COLORREF col = cl_WHITE);
	void SetPen(COLORREF col, int style, int width = 1);
	void SetSolidPen(COLORREF col, int width = 1);
	void SetPen(HPEN hpen);
	void SetWhitePen();
	void SetBlackPen();
	void SetNullPen();
	HPEN GetPen();
	COLORREF GetPenColor();
	bool DeletePen(HPEN hpen);

	void SetBrush(COLORREF col, int style, LONG hatch = BS_SOLID);
	void SetSolidBrush(COLORREF col);
	void SetBrush(HBRUSH hbr);
	void SetWhiteBrush();
	void SetNullBrush();
	void SetBlackBrush();
	HBRUSH GetBrush();
	COLORREF GetBrushColor();
	bool DeleteBrush(HBRUSH hbr);

	void SetFont(LPCTSTR name, float h, int style = fs_NORMAL);
	void SetFont(LPCTSTR name, float h, int style, COLORREF col);
	void SetFont(LPCTSTR name, float h, float w, int style, 
		float angle, DWORD charset = DEFAULT_CHARSET, DWORD pitchAndFamily = DEFAULT_PITCH | FF_DONTCARE);
	void SetFont(HFONT hf);
	HFONT GetFont();
	void SetFontColor(COLORREF col);
	COLORREF GetFontColor();
	void SetTextAlignment(UINT align);
	bool DeleteFont(HFONT hf);

	void TextOut(LPCTSTR text, Range2D * range, UINT format = DT_NOCLIP);
	void TextOut(float x, float y, LPCTSTR text);
	void TextOut(float x, float y, LPCTSTR text, int align);


private:
	HDC hdc;
	WindowRange * wr;
	float sx, sy, tx, ty;
	bool bpen, bbrush, bfont;

	bool IsStandardPen(HPEN hpen);
	bool IsStandardBrush(HBRUSH hbr);
	bool IsStandardFont(HFONT hfont);
};

