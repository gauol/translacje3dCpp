// BasicPrj.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "przeksztalcenia.h"
#include "Utils.h"
#include "WindowRange.h"
#include "Graphics2D.h"
#include "Cmatrix.h"
#include <chrono>
#include <thread>
#include <functional>

// U�ycie przestrzeni nazw "std"
using namespace std;

#define MAX_LOADSTRING 100

#define PERSP 1
#define ORTO 2
#define IZO 3

#define INTERVAL 50


// Zmienne globalne:
HINSTANCE hInst;								// Uchwyt bie��cej instancji (obiektu - okna)
TCHAR szTitle[MAX_LOADSTRING];					// Tekst na pasku tytu�owym okna
TCHAR szWindowClass[MAX_LOADSTRING];			// Nazwa klasy okna g��wnego
HWND hWnd;

WindowRange wr= NULL;	// obiekt klasy WindowRange - do przeskalowywania zakresu okna

// Deklaracje funkcji zawartych w module
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

// parametry rzutowania perspektywicznego
Cvector theta(0, 0, 0);  // ori�tacja kamery
Cvector C(0, 0, 15);	 // wspolrzedne kamery
Cvector e(-5, -5, -15);	 // wspolrzedne ekranu wzgledem C

//parametry animacji
float rotateX = 1.5;
float rotateY = 0.5;
float rotateZ = 2.5;

void do_something();
void timer_start(std::function<void(void)> func, unsigned int interval);

void Paint(HWND hwnd, PAINTSTRUCT * ps);

/*
	_tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
              LPTSTR lpCmdLine, int nCmdShow);
	hInstance = Uchwyt programu (okna g��wnego).
	hPrevInstance = Uchwyt poprzedniej realizacji programu - w Win32 nieu�ywany.
	lpCmdLine = wska�nik do �a�cucha znak�w linii wywo�ania aplikacji.
	nCmdShow = Spos�b wy�wietlenia aplikacji.

	G��wna funkcja aplikacji - dzia�anie programu rozpoczyna sie od tej funkcji.

 */
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance); // Argumenty nieu�ywane w Win32
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Inicjalizacja �a�cuch�w globalnych
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PRZEKSZTALCENIA, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance); // Utw�rz i zarejestruj klas� okna

	// Inicjalizacja aplikacji...
	if (!InitInstance (hInstance, nCmdShow)) // Je�eli nieudana...
	{
		return FALSE;
	}

	// Inicjalizacja akcelerator�w programu
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PRZEKSZTALCENIA));

	// G��wna p�tla wiadomo�ci (�ledzenie zdarze�):
	while (GetMessage(&msg, NULL, 0, 0)) // Wychwy� wiadomo�� okna w kolejce wiadomo�ci aplikacji
	{
		// Reaguj na u�ycie akceleratora - przet�umacz kombinacj� klawiszy 
		// na wiadomo�� zwi�zan� z menu i wy�lij j� do procedury okna
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) // Je�eli nie u�yto akceleratora...
		{
			TranslateMessage(&msg); // Przet�umacz u�ycie klawiatury na tzw. wiadomo�� klawiszow� 
			DispatchMessage(&msg); // Wy�lij wiadomo�� do procedury okna, kt�ra przetworzy wiadomo��.
		}
	}

	return (int) msg.wParam;
}



/*
	ATOM MyRegisterClass(HINSTANCE hInstance)
	hInstance = Uchwyt okna 

	Funkcja definiuje zmienn� typu WNDCLASSEX (klasa okna), 
	wype�niawarto�ciami pola tej struktury i rejestruje klas� okna w systemie.
*/
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	/*
	Struktura WNDCLASSEX:
	cbSize = Rozmiar struktury WNDCLASSEX w bajtach.
	style = Styl klasy okna (np. CS_HREDRAW - system wymusi od�wie�enie okna,
			je�eli zmianie uleg�a szeroko�� obszaru roboczego okna).
	lpfnWndProc = Adres procedury okna, zajmuj�cej si� obs�ug� wiadomo�ci 
				  wysy�anych przez system do aplikacji.
	cbClsExtra = Liczba bajt�w dodatkowej pami�ci zarezerwowana podczas 
				 rejestracji klasy okna.
	cbWndExtra = Liczba bajt�w dodatkowej pami�ci zarezerwowana dla ka�dego okna
				 tworzonego na podstawie danej klasy okna.	
	hInstance = Uchwyt aplikacji (okna g��wnego).
	hIcon = Uchwyt ikony (tzw. du�a ikona, 32x32 piksele).
	hCursor = Uchwyt kursora wy�wietlanego nad obszarem roboczym okna.
	hbrBackground = P�dzel wype�nienia obszaru roboczego okna podczas jego od�wie�ania.
	lpszMenuName = Identyfikator menu do��czonego do tworzonego okna.
	lpszClassName = Adres ��cucha znak�w okre�laj�cego nazw� klasy okna.
	hIconSm = Uchwyt tzw. ma�ej ikony (16x16 pikseli) wy�wietlanej m.in. na belce tytu�owej.
	*/

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PRZEKSZTALCENIA));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_PRZEKSZTALCENIA);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex); // Rejestruj klas� okna w systemie
}

/*  
	InitInstance(HINSTANCE hInstance, int nCmdShow)
	hInstance = Uchwyt okna.
	nCmdShow = Identyfikator sposobu wy�wietlania okna.

	Funkcja tworzy i wy�wietla okno g��wne aplikacji.
	Zwraca TRUE (tworzenie okna powiod�o si�) lub FALSE.
*/
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{

	timer_start(do_something, INTERVAL);

   hInst = hInstance; // Przechowaj uchwyt okna w zmiennej globalnej

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
   /*
	Funcja CreateWindow(
    LPCTSTR lpClassName, LPCTSTR lpWindowName,
    DWORD dwStyle,
    int x, int y,
    int nWidth, int nHeight,
    HWND hWndParent, HMENU hMenu, HINSTANCE hInstance,
    LPVOID lpParam
	);

	Funkcja tworzy okno i zwraca jego uchwyt.

	lpClassName = Adres ��cucha znak�w okre�laj�cego nazw� klasy okna.
	lpWindowName = Adres ��cucha znak�w okre�laj�cego tekst na belce tytu�owej.
	dwStyle = standardowy styl okna (np. WS_SIZEBOX - kraw�d� okna pozwala na 
				zmian� jego rozmiaru).
	x, y = pozycja g�rnego lewego naro�nika okna.
	nWidth, nHeight = Szeroko�� i wysoko�� okna.
	hWndParent = Uchwyt okna-rodzica lub okna nadrz�dnego (w�a�ciciela).
	hMenu = Uchwyt menu do��czonego do okna.
	hInstance = Uchwyt aplikacji (okna g��wnego).
	lpParam = 32-bitowa warto�� przekazana do procedury okna wraz z wiadomo�ci� WM_CREATE.
   */

   if (!hWnd) // Je�eli tworzenie okna si� nie powiod�o... 
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow); // Poka� okno.
   UpdateWindow(hWnd); // Natychmiast po wy�wietleniu okna od�wie� je.

   return TRUE;
}

/*  
	WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	hWnd = Uchwyt okna.
	message = Numer (kod) wiadomo�ci.
	wParam = 32-bitowa warto�� bez znaku okre�laj�ca dodatkowe informacje o wiadomo�ci.
	lParam = 32-bitowa warto�� (ze znakiem) okre�laj�ca dodatkowe informacje o wiadomo�ci.

	Tzw. procedura okna.
	Funkcja przetwarza wiadomo�ci wys�ane przez system do aplikacji (obs�uga zdarze�).
	Zwraca 32-bitow� liczb� ca�kowit� ze znakiem.
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message) // Sprawd� typ wiadomo�ci (komunikatu)
	{
	case WM_COMMAND: // Wyb�r z menu
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		
		switch (wmId) // Sprawd�, kt�ry element (pole) menu wybrano
		{
		case IDM_ABOUT: // Poka� okno dialogowe "About"
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT: // Wyjd� - zamknij program
			DestroyWindow(hWnd);
			break;
		default:
			// Procedura przetwarzaj�ca wiadomo�� w domy�lny spos�b
			return DefWindowProc(hWnd, message, wParam, lParam); 
		}
		break;

	case WM_CREATE: // Tworzenie okna
		wr= WindowRange(hWnd);  // ustaw uchwyt okna w obiekcie zakresu
	    wr.SetRange(-100, -100, 100, 100); // domy�lny zakres osi
		break;

	case WM_PAINT: // Przerysowanie okna
		hdc = BeginPaint(hWnd, &ps);
		Paint(hWnd, &ps);	// rysuj w obszarze roboczym (procedura poni�ej)
		EndPaint(hWnd, &ps);
		break;

	case WM_SIZE: // Zmiana rozmiaru okna
		wr.Update(hWnd);  // uaktualnij zakres
		//InvalidateRect(hWnd, NULL, true); // przerysuj wszystko
		break;

	case WM_DESTROY: // Niszczenie okna
		PostQuitMessage(0); // Wstaw wiadomo�� WM_QUIT do kolejki aplikacji
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

/*
	Procedura okna dialogowego "About".
	Parametry i dzia�anie analogiczne do procedury okna g��wnego. 
*/
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void timer_start(std::function<void(void)> func, unsigned int interval)
{
	std::thread([func, interval]() {
		while (true)
		{
			func();
			std::this_thread::sleep_for(std::chrono::milliseconds(interval));
		}
	}).detach();
}


void do_something()
{
	rotateX = rotateX + (float)0.05;
	rotateZ = rotateZ + (float)0.05;
	rotateY = rotateY + (float)0.01;
	if (rotateX >= 6.28)
		rotateX = 0;
	if (rotateZ >= 6.28)
		rotateZ = 0;
	if (rotateY >= 6.28)
		rotateY = 0;
	RedrawWindow(hWnd, 0, 0, RDW_INVALIDATE | RDW_ERASE);
	UpdateWindow(hWnd);
}

class object {
	int pointsNumber;
	Cvector * pointsVectors;

	class Edge {
		int a, b;
		public:
			Edge() {

			}

			Edge(int a, int b){
				this->a = a;
				this->b = b;
			}

			int getA(void) {
				return a;
			}

			int getB(void) {
				return b;
			}
	};

	int edgesNumbers;
	Edge * edges;

public:
	object(float *X, float *Y, float *Z, int n) {
		this->pointsNumber = n;
		this->pointsVectors = new Cvector[this->pointsNumber];
		for (int i = 0; i < this->pointsNumber; i++) this->pointsVectors[i] = Cvector(X[i], Y[i], Z[i]);
	}

	void freemem() {
		delete[] this->edges;
		delete[] this->pointsVectors;
	}

	void defineEdges(int *a, int *b, int n) {
		this->edgesNumbers = n;
		this->edges = new Edge[this->edgesNumbers];
		for (int i = 0; i < this->edgesNumbers; i++) this->edges[i] = Edge(a[i], b[i]);
	}

	object drawObject(Graphics2D gr, int type) {
		for (int i = 0; i < this->edgesNumbers; i++) {
			if(i == 0 )
				gr.SetPen(Graphics2D::cl_RED, PS_SOLID, 2);
			if(i == 4)
				gr.SetPen(Graphics2D::cl_BLUE, PS_SOLID, 2);
			if(i == 8)
				gr.SetPen(Graphics2D::cl_CYAN, PS_SOLID, 2);

			Cvector pointA;
			Cvector pointB;

			if (type == PERSP){
				pointA = pointsVectors[edges[i].getA()].GetPersp(theta, C, e);
				pointB = pointsVectors[edges[i].getB()].GetPersp(theta, C, e);
			}
			if (type == ORTO){
				pointA = pointsVectors[edges[i].getA()].GetOrto();
				pointB = pointsVectors[edges[i].getB()].GetOrto();
			}
			if (type == IZO){
				pointA = pointsVectors[edges[i].getA()].GetIzo();
				pointB = pointsVectors[edges[i].getB()].GetIzo();
			}

			gr.DrawLine(pointA.GetX(), pointA.GetY(), pointB.GetX(), pointB.GetY());
		}
		return *this;
	}

	void affineTransform(Cmatrix translacja) {
		for (int i = 0; i < this->pointsNumber; i++)
			this->pointsVectors[i] = translacja * this->pointsVectors[i];
	}
};


/*
	Procedura rysowania w obszarze roboczym okna aplikacji.
*/
void Paint(HWND hwnd, PAINTSTRUCT * ps)
{
	// Pobranie uchwytu kontekstu urz�dzenia na podstawie uchwytu okna
	HDC hdc= GetDC(hwnd); // lub: HDC hdc= ps->hdc;

	// Utworzenie obiektu klasy Graphics2D za pomoc� konstruktora parametrowego dla danego kontekstu i zakresu okna
	Graphics2D gr(hdc, &wr);

	Cmatrix transformacja;
	Cmatrix skala;
	Cmatrix obrot;
	wr.SetProportional(true);
	wr.SetRange(-10.0, -10.0, 10.0, 10.0);
	gr.Update();

	//wiezcholki
	float x[8] = { 0, 0, 2, 2,	 0, 0, 2, 2 },
		  y[8] = { 0, 2, 0, 2,	 0, 2, 0, 2 },
		  z[8] = { 0, 0, 0, 0,	 2, 2, 2, 2 };
	//belki
	int a[12] = { 0, 0, 1, 3,	 4, 4, 5, 7,	 0, 1, 2, 3 },
		b[12] = { 1, 2, 3, 2,	 5, 6, 7, 6,	 4, 5, 6, 7 };

	//obiekt perspektywiczny
	object kostka(x, y, z, 12);
	kostka.defineEdges(a, b, 12);

	kostka.affineTransform(transformacja.SetTranslate(-1, 1, 0));
	kostka.affineTransform(obrot.SetRotateOX(rotateX));
	kostka.affineTransform(obrot.SetRotateOZ(rotateZ));
	kostka.affineTransform(obrot.SetRotateOY(rotateY));

	kostka.affineTransform(skala.SetScale(2, 2, 2));
	kostka.affineTransform(transformacja.SetTranslate(-5, 5, 0));

	kostka.drawObject(gr, PERSP).freemem();
	gr.TextOutW(-3, 0, L"Persp", TA_CENTER);

	// obiekt izometryczny
	object klocek(x, y, z, 12);
	klocek.defineEdges(a, b, 12);

	klocek.affineTransform(transformacja.SetTranslate(3, 0, 0));
	klocek.affineTransform(skala.SetScale(2, 3, 4));
	
	klocek.drawObject(gr, IZO).freemem();
	gr.TextOutW(3, 3, L"Izo", TA_CENTER);

	// obiekt orto
	object szescian(x, y, z, 12);
	szescian.defineEdges(a, b, 12);

	szescian.affineTransform(skala.SetScale(1, 2, 3));
	szescian.affineTransform(obrot.SetRotateOX(1));
	szescian.affineTransform(obrot.SetRotateOZ(0.5));
	szescian.affineTransform(obrot.SetRotateOY(1.2));
	szescian.affineTransform(transformacja.SetTranslate(3, -3, 0));
	szescian.drawObject(gr, ORTO).freemem();
	gr.TextOutW(3, -3, L"Orto", TA_CENTER);

	// uklad osi
	gr.SetPen(Graphics2D::cl_BLUE, PS_SOLID, 2);
	gr.DrawLine(0, 0, 0, 1);
	gr.SetPen(Graphics2D::cl_RED, PS_SOLID, 2);
	gr.DrawLine(0, 0, 1, 0);
	gr.SetPen(Graphics2D::cl_GREEN, PS_SOLID, 2);
	gr.DrawLine(0, 0, -0.75, -0.75);

	// opis osi ukladu wsp
	gr.TextOutW(1, 0, L"X", TA_CENTER);
	gr.TextOutW(0, 1.2, L"Y", TA_CENTER);
	gr.TextOutW(-0.6, -0.6, L"Z", TA_CENTER);

	gr.~Graphics2D(); // wywoanie destruktora obiektu gr
	ReleaseDC(hwnd, hdc);
}
