#include "StdAfx.h"
#include "Graphics2D.h" 
#include "math.h" 

using namespace mathf;

Graphics2D::Graphics2D(void)
{
	hdc= NULL;
	wr= NULL;
	sx= 0;
	sy= 0;
	tx= 0;
	ty= 0;
	bpen= false;
	bbrush= false;
	bfont= false;
}

Graphics2D::Graphics2D(HDC hdc, WindowRange * wr)
{
	this->hdc= hdc;
	this->wr= wr;
	Update();
	bpen= false;
	bbrush= false;
	bfont= false;
}

Graphics2D::~Graphics2D(void)
{
	if (bpen) 
	{	
		HGDIOBJ hobj= SelectObject(hdc, GetStockObject(BLACK_PEN));
		DeleteObject(hobj);
	}

	if (bbrush) 
	{
		HGDIOBJ hobj= SelectObject(hdc, GetStockObject(NULL_BRUSH));
		DeleteObject(hobj);
	}

	if (bfont)
	{
		HGDIOBJ hobj= SelectObject(hdc, GetStockObject(SYSTEM_FONT));
		DeleteObject(hobj);
	}
}


void Graphics2D::SetWindow(HDC hdc, WindowRange * wr)
{
	this->hdc= hdc;
	this->wr= wr;
	Update();
}

HDC Graphics2D::GetDC()
{
	return hdc;
}
	
WindowRange * Graphics2D::GetWindowRange()
{
	return wr;
}

void Graphics2D::Update()
{
	sx= wr->GetScaleX();
	sy= wr->GetScaleY();
	tx= wr->GetTranslationX();
	ty= wr->GetTranslationY();
}

float Graphics2D::XfromPixels(int xp)
{
	return sx*xp + tx;
}

float Graphics2D::YfromPixels(int yp)
{
	return sy*yp + ty;
}

int Graphics2D::XtoPixels(float x)
{
	return mathf::round((x - tx)/sx);
}

int Graphics2D::YtoPixels(float y)
{
	return mathf::round((y - ty)/sy);
}

void Graphics2D::FromPixels(int xp, int yp, float * x, float * y)
{
	*x= XfromPixels(xp);
	*y= YfromPixels(yp);
}

void Graphics2D::ToPixels(float x, float y, int * xp, int * yp)
{
	*xp= XtoPixels(x);
	*yp= YtoPixels(y);
}

void Graphics2D::DrawPoint(float x, float y)
{
	SetPixel(hdc, XtoPixels(x), YtoPixels(y), GetPenColor());
}	

void Graphics2D::MoveTo(float x, float y)
{
	MoveToEx(hdc, XtoPixels(x), YtoPixels(y), NULL);
}

void Graphics2D::DrawLineTo(float x, float y)
{
	LineTo(hdc, XtoPixels(x), YtoPixels(y));
}

void Graphics2D::DrawLine(float x1, float y1, float x2, float y2)
{
	MoveToEx(hdc, XtoPixels(x1), YtoPixels(y1), 0);
	LineTo(hdc, XtoPixels(x2), YtoPixels(y2));
}

void Graphics2D::DrawArc(float x, float y, float r, float ang0, float ang)
{
	int x1= XtoPixels(x-r);
	int y1= YtoPixels(y-r);
	int x2= XtoPixels(x+r);
	int y2= YtoPixels(y+r);
	float alpha= toRad(ang0);
	int x3= XtoPixels(x + r*cos(alpha));  
	int y3= YtoPixels(y + r*sin(alpha));
	alpha= toRad(ang0 + ang);
	int x4= XtoPixels(x + r*cos(alpha));  
	int y4= YtoPixels(y + r*sin(alpha));
	Arc(hdc, x1, y1, x2, y2, x3, y3, x4, y4); 
}

void Graphics2D::DrawArc(float x1, float y1, float x2, float y2, float ang0, float ang)
{
	float x= 0.5f*(x1+x2);
	float y= 0.5f*(y1+y2);
	float a= fabsf(x2-x1)*0.5f;
	float b= fabsf(y2-y1)*0.5f;
	int ix1= XtoPixels(x1);
	int iy1= YtoPixels(y1);
	int ix2= XtoPixels(x2);
	int iy2= YtoPixels(y2);
	float alpha= toRad(ang0);
	int ix3= XtoPixels(x + a*cos(alpha));  
	int iy3= YtoPixels(y + b*sin(alpha));
	alpha= toRad(ang0 + ang);
	int ix4= XtoPixels(x + a*cos(alpha));  
	int iy4= YtoPixels(y + b*sin(alpha));
	Arc(hdc, ix1, iy1, ix2, iy2, ix3, iy3, ix4, iy4); 
}

void Graphics2D::DrawArc2(float x, float y, float a, float b, float ang0, float ang)
{
	int ix1= XtoPixels(x-a);
	int iy1= YtoPixels(y-b);
	int ix2= XtoPixels(x+a);
	int iy2= YtoPixels(y+b);
	float alpha= toRad(ang0);
	int ix3= XtoPixels(x + a*cos(alpha));  
	int iy3= YtoPixels(y + b*sin(alpha));
	alpha= toRad(ang0 + ang);
	int ix4= XtoPixels(x + a*cos(alpha));  
	int iy4= YtoPixels(y + b*sin(alpha));
	Arc(hdc, ix1, iy1, ix2, iy2, ix3, iy3, ix4, iy4); 
}

void Graphics2D::DrawPolyline(POINT2D * pt2, int n)
{
	POINT * pt= new POINT[n];
	Pt2DtoPt(pt2, pt, n);
	Polyline(hdc, pt, n);
}	

void Graphics2D::DrawPolyline(float * X, float * Y, int n)
{
	POINT * pt= new POINT[n];
	XYtoPt(X, Y, pt, n);
	Polyline(hdc, pt, n);
}

void Graphics2D::Pt2DtoPt(POINT2D * pt2, POINT * pt, int n)
{
	for (int i = 0; i < n; i++)
	{
		float x= (*pt2).x;
		float y= (*pt2).y;
		pt->x= XtoPixels(x);
		pt->y= YtoPixels(y);
		pt2++;
		pt++;
	}
}

void Graphics2D::XYtoPt(float * X, float * Y, POINT * pt, int n)
{
	for (int i = 0; i < n; i++)
	{
		float xi= *X;
		float yi= *Y;
		pt->x= XtoPixels(xi);
		pt->y= YtoPixels(yi);
		X++;
		Y++;
		pt++;
	}
}

void Graphics2D::DrawRectangle(float x1, float y1, float x2, float y2)
{
	Rectangle(hdc, XtoPixels(x1), YtoPixels(y1), XtoPixels(x2), YtoPixels(y2));
}

void Graphics2D::DrawEllipse(float x1, float y1, float x2, float y2)
{
	Ellipse(hdc, XtoPixels(x1), YtoPixels(y1), XtoPixels(x2), YtoPixels(y2));
}

void Graphics2D::DrawEllipse2(float x, float y, float a, float b)
{
	Ellipse(hdc, XtoPixels(x-a), YtoPixels(y-b), XtoPixels(x+a), YtoPixels(y+b));
}

void Graphics2D::DrawCircle(float x, float y, float r)
{
	Ellipse(hdc, XtoPixels(x-r), YtoPixels(y-r), XtoPixels(x+r), YtoPixels(y+r));
}
	
void Graphics2D::DrawPolygon(POINT2D * pt2, int n)
{
	POINT * pt= new POINT[n];
	Pt2DtoPt(pt2, pt, n);
	Polygon(hdc, pt, n);
}	

void Graphics2D::DrawPolygon(float * X, float * Y, int n)
{
	POINT * pt= new POINT[n];
	XYtoPt(X, Y, pt, n);
	Polygon(hdc, pt, n);
}

void Graphics2D::DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
	POINT pt[3]= {XtoPixels(x1), YtoPixels(y1), 
		XtoPixels(x2), YtoPixels(y2), 
		XtoPixels(x3), YtoPixels(y3)};
	Polygon(hdc, pt, 3);
}

void Graphics2D::FillBackground(COLORREF col)
{
	HPEN hpen= GetPen();
	HBRUSH hbr= GetBrush();

	SetSolidPen(col, 1);
	SetSolidBrush(col);
	int w, h;
	wr->GetWindowSize(&w, &h);
	Rectangle(hdc, 0, 0, w, h);

	SetPen(hpen);
	SetBrush(hbr);
}

void Graphics2D::SetBackground(COLORREF col)
{
	SetBkColor(hdc, col);
}

bool Graphics2D::IsStandardPen(HPEN hpen)
{
	if (hpen == GetStockObject(WHITE_PEN) || 
		hpen == GetStockObject(BLACK_PEN) || 
		hpen == GetStockObject(NULL_PEN)) return true;
	return false;
}

bool Graphics2D::IsStandardBrush(HBRUSH hbr)
{
	if (hbr == GetStockObject(WHITE_BRUSH) || 
		hbr == GetStockObject(LTGRAY_BRUSH) || 
		hbr == GetStockObject(GRAY_BRUSH) || 
		hbr == GetStockObject(DKGRAY_BRUSH) || 
		hbr == GetStockObject(BLACK_BRUSH) || 
		hbr == GetStockObject(NULL_BRUSH)) return true;
	return false;
}

bool Graphics2D::IsStandardFont(HFONT hf)
{
	if (hf == GetStockObject(ANSI_FIXED_FONT) || 
		hf == GetStockObject(ANSI_VAR_FONT) || 
		hf == GetStockObject(SYSTEM_FIXED_FONT) || 
		hf == GetStockObject(SYSTEM_FONT) || 
		hf == GetStockObject(OEM_FIXED_FONT) || 
		hf == GetStockObject(DEFAULT_GUI_FONT)) return true;
	return false;
}

void Graphics2D::SetPen(COLORREF col, int style, int width)
{
	HPEN hpen= CreatePen(style, width, col);
	HGDIOBJ hobj= SelectObject(hdc, hpen);
	if (bpen) DeleteObject(hobj);

	bpen= true;
}

void Graphics2D::SetSolidPen(COLORREF col, int width)
{
	HPEN hpen= CreatePen(PS_SOLID, width, col);
	HGDIOBJ hobj= SelectObject(hdc, hpen);
	if (bpen) DeleteObject(hobj);

	bpen= true;
}

void Graphics2D::SetPen(HPEN hpen)
{
	HGDIOBJ hobj= SelectObject(hdc, hpen);
	if (bpen) DeleteObject(hobj);

	bpen= false;
}

void Graphics2D::SetWhitePen()
{
	HGDIOBJ hobj= SelectObject(hdc, GetStockObject(WHITE_PEN));
	if (bpen) DeleteObject(hobj);

	bpen= false;
}

void Graphics2D::SetBlackPen()
{
	HGDIOBJ hobj= SelectObject(hdc, GetStockObject(BLACK_PEN));
	if (bpen) DeleteObject(hobj);

	bpen= false;
}

void Graphics2D::SetNullPen()
{
	HGDIOBJ hobj= SelectObject(hdc, GetStockObject(NULL_PEN));
	if (bpen) DeleteObject(hobj);

	bpen= false;
}

HPEN Graphics2D::GetPen()
{
	bpen= false;
	HGDIOBJ hobj= GetCurrentObject(hdc, OBJ_PEN);
	HPEN hpen= (HPEN) hobj;
	return hpen;
}

COLORREF Graphics2D::GetPenColor()
{
	return GetDCPenColor(hdc);
}

bool Graphics2D::DeletePen(HPEN hpen)
{
	if (IsStandardPen(hpen)) return false;
	if (GetPen() == hpen) 
	{
		SelectObject(hdc, GetStockObject(BLACK_PEN));
		bpen= false;
	}
	DeleteObject(hpen);
	return true;
}

void Graphics2D::SetBrush(COLORREF col, int style, LONG hatch)
{
	LOGBRUSH lbr;
	lbr.lbColor= col;
	lbr.lbStyle= style;
	lbr.lbHatch= hatch;
	
	HBRUSH hbr= CreateBrushIndirect(&lbr);
	HGDIOBJ hobj= SelectObject(hdc, hbr);
	if (bbrush) DeleteObject(hobj);

	bbrush= true;
}

void Graphics2D::SetSolidBrush(COLORREF col)
{
	LOGBRUSH lbr;
	lbr.lbColor= col;
	lbr.lbStyle= HS_HORIZONTAL;
	lbr.lbHatch= BS_SOLID;
	
	HBRUSH hbr= CreateBrushIndirect(&lbr);
	HGDIOBJ hobj= SelectObject(hdc, hbr);
	if (bbrush) DeleteObject(hobj);

	bbrush= true;
}

void Graphics2D::SetBrush(HBRUSH hbr)
{
	HGDIOBJ hobj= SelectObject(hdc, hbr);
	if (bbrush) DeleteObject(hobj);

	bbrush= false;
}

void Graphics2D::SetWhiteBrush()
{
	HGDIOBJ hobj= SelectObject(hdc, GetStockObject(WHITE_BRUSH));
	if (bbrush) DeleteObject(hobj);

	bbrush= false;
}

void Graphics2D::SetBlackBrush()
{
	HGDIOBJ hobj= SelectObject(hdc, GetStockObject(BLACK_BRUSH));
	if (bbrush) DeleteObject(hobj);

	bbrush= false;
}

void Graphics2D::SetNullBrush()
{
	HGDIOBJ hobj= SelectObject(hdc, GetStockObject(NULL_BRUSH));
	if (bbrush) DeleteObject(hobj);

	bbrush= false;
}

HBRUSH Graphics2D::GetBrush()
{
	bbrush= false;
	HGDIOBJ hobj= GetCurrentObject(hdc, OBJ_BRUSH);
	HBRUSH hbr= (HBRUSH) hobj;
	return hbr;
}

COLORREF Graphics2D::GetBrushColor()
{
	return GetDCBrushColor(hdc);
}

bool Graphics2D::DeleteBrush(HBRUSH hbr)
{
	if (IsStandardBrush(hbr)) return false;
	if (GetBrush() == hbr) 
	{
		SelectObject(hdc, GetStockObject(NULL_BRUSH));
		bbrush= false;
	}
	DeleteObject(hbr);
	return true;
}

void Graphics2D::SetFont(LPCTSTR name, float h, int style)
{
	int weight= 0;
	DWORD italic= false;
	DWORD underline= false;
	DWORD strikeout= false;
	Graphics2D::DecodeFontStyle(style, &weight, &italic, &underline, &strikeout);	

	int ih= (int) floorf(h/sy);

	HFONT hf= CreateFont(ih, 0, 0, 0, weight, italic, underline, strikeout, 
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, name);
	HGDIOBJ hobj= SelectObject(hdc, hf);
	if (bfont) DeleteObject(hobj);

	bfont= true;
}

void Graphics2D::SetFont(LPCTSTR name, float h, int style, COLORREF col)
{
	int weight= 0;
	DWORD italic= false;
	DWORD underline= false;
	DWORD strikeout= false;
	Graphics2D::DecodeFontStyle(style, &weight, &italic, &underline, &strikeout);	
	SetTextColor(hdc, col);
	int ih= (int) floorf(h/sy);

	HFONT hf= CreateFont(ih, 0, 0, 0, weight, italic, underline, strikeout, 
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, name);
	HGDIOBJ hobj= SelectObject(hdc, hf);
	if (bfont) DeleteObject(hobj);

	bfont= true;
}
	
void Graphics2D::SetFont(LPCTSTR name, float h, float w, int style, float angle, 
						 DWORD charset, DWORD pitchAndFamily)
{
	int weight= 0;
	DWORD italic= false;
	DWORD underline= false;
	DWORD strikeout= false;
	Graphics2D::DecodeFontStyle(style, &weight, &italic, &underline, &strikeout);	

	int ih= (int) floorf(h/sy);
	int iw= (int) floorf(w/sx);
	int ang10= mathf::round(angle*10);
	HFONT hf= CreateFont(ih, iw, ang10, 0, weight, italic, underline, strikeout, 
		charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, pitchAndFamily, name);
	HGDIOBJ hobj= SelectObject(hdc, hf);
	if (bfont) DeleteObject(hobj);

	bfont= true;
}

void Graphics2D::SetFontColor(COLORREF col)
{
	SetTextColor(hdc, col);
}

COLORREF Graphics2D::GetFontColor()
{
	return GetTextColor(hdc);
}
	
void Graphics2D::SetFont(HFONT hf)
{
	HGDIOBJ hobj= SelectObject(hdc, hf);
	if (bfont) DeleteObject(hobj);

	bfont= false;
}

HFONT Graphics2D::GetFont()
{
	bfont= false;
	HGDIOBJ hobj= GetCurrentObject(hdc, OBJ_FONT);
	HFONT hf= (HFONT) hobj;
	return hf;
}

void Graphics2D::SetTextAlignment(UINT align)
{
	SetTextAlign(hdc, align | TA_NOUPDATECP);	
}

bool Graphics2D::DeleteFont(HFONT hf)
{
	if (IsStandardFont(hf)) return false;
	if (GetFont() == hf) 
	{
		SelectObject(hdc, GetStockObject(SYSTEM_FONT));
		bfont= false;
	}
	DeleteObject(hf);
	return true;
}

void Graphics2D::TextOut(LPCTSTR text, Range2D * range, UINT format)
{
	RECT rect;
	rect.left= XtoPixels(range->GetX1());
	rect.right= XtoPixels(range->GetX2());
	rect.bottom= YtoPixels(range->GetY1());
	rect.top= YtoPixels(range->GetY2());

	DrawText(hdc, text, -1, &rect, format);
}

void Graphics2D::TextOut(float x, float y, LPCTSTR text)
{
	int xp= XtoPixels(x);
	int yp= YtoPixels(y);
	RECT rect= {xp-1, yp-1, xp+1, yp+1};

	DrawText(hdc, text, -1, &rect, DT_NOCLIP);
}
	
void Graphics2D::TextOut(float x, float y, LPCTSTR text, int align)
{
	int xp= XtoPixels(x);
	int yp= YtoPixels(y);
	RECT rect= {xp-1, yp-1, xp+1, yp+1};

	int a= DT_LEFT;
	switch (align)
	{
	case TA_RIGHT:
		a= DT_RIGHT;
		break;
	case TA_CENTER:
		a= DT_CENTER;
		break;
	}

	DrawText(hdc, text, -1, &rect, DT_NOCLIP | a);
}