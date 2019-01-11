// BasicPrj.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "przeksztalcenia.h"
#include "Utils.h"
#include "WindowRange.h"
#include "Graphics2D.h"
#include "Cmatrix.h"

// U¿ycie przestrzeni nazw "std"
using namespace std;

#define MAX_LOADSTRING 100

// Zmienne globalne:
HINSTANCE hInst;								// Uchwyt bie¿¹cej instancji (obiektu - okna)
TCHAR szTitle[MAX_LOADSTRING];					// Tekst na pasku tytu³owym okna
TCHAR szWindowClass[MAX_LOADSTRING];			// Nazwa klasy okna g³ównego

WindowRange wr= NULL;	// obiekt klasy WindowRange - do przeskalowywania zakresu okna

// Deklaracje funkcji zawartych w module
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void Paint(HWND hwnd, PAINTSTRUCT * ps);

/*
	_tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
              LPTSTR lpCmdLine, int nCmdShow);
	hInstance = Uchwyt programu (okna g³ównego).
	hPrevInstance = Uchwyt poprzedniej realizacji programu - w Win32 nieu¿ywany.
	lpCmdLine = wskaŸnik do ³añcucha znaków linii wywo³ania aplikacji.
	nCmdShow = Sposób wyœwietlenia aplikacji.

	G³ówna funkcja aplikacji - dzia³anie programu rozpoczyna sie od tej funkcji.

 */
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance); // Argumenty nieu¿ywane w Win32
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Inicjalizacja ³añcuchów globalnych
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PRZEKSZTALCENIA, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance); // Utwórz i zarejestruj klasê okna

	// Inicjalizacja aplikacji...
	if (!InitInstance (hInstance, nCmdShow)) // Je¿eli nieudana...
	{
		return FALSE;
	}

	// Inicjalizacja akceleratorów programu
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PRZEKSZTALCENIA));

	// G³ówna pêtla wiadomoœci (œledzenie zdarzeñ):
	while (GetMessage(&msg, NULL, 0, 0)) // Wychwyæ wiadomoœæ okna w kolejce wiadomoœci aplikacji
	{
		// Reaguj na u¿ycie akceleratora - przet³umacz kombinacjê klawiszy 
		// na wiadomoœæ zwi¹zan¹ z menu i wyœlij j¹ do procedury okna
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) // Je¿eli nie u¿yto akceleratora...
		{
			TranslateMessage(&msg); // Przet³umacz u¿ycie klawiatury na tzw. wiadomoœæ klawiszow¹ 
			DispatchMessage(&msg); // Wyœlij wiadomoœæ do procedury okna, która przetworzy wiadomoœæ.
		}
	}

	return (int) msg.wParam;
}



/*
	ATOM MyRegisterClass(HINSTANCE hInstance)
	hInstance = Uchwyt okna 

	Funkcja definiuje zmienn¹ typu WNDCLASSEX (klasa okna), 
	wype³niawartoœciami pola tej struktury i rejestruje klasê okna w systemie.
*/
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	/*
	Struktura WNDCLASSEX:
	cbSize = Rozmiar struktury WNDCLASSEX w bajtach.
	style = Styl klasy okna (np. CS_HREDRAW - system wymusi odœwie¿enie okna,
			je¿eli zmianie uleg³a szerokoœæ obszaru roboczego okna).
	lpfnWndProc = Adres procedury okna, zajmuj¹cej siê obs³ug¹ wiadomoœci 
				  wysy³anych przez system do aplikacji.
	cbClsExtra = Liczba bajtów dodatkowej pamiêci zarezerwowana podczas 
				 rejestracji klasy okna.
	cbWndExtra = Liczba bajtów dodatkowej pamiêci zarezerwowana dla ka¿dego okna
				 tworzonego na podstawie danej klasy okna.	
	hInstance = Uchwyt aplikacji (okna g³ównego).
	hIcon = Uchwyt ikony (tzw. du¿a ikona, 32x32 piksele).
	hCursor = Uchwyt kursora wyœwietlanego nad obszarem roboczym okna.
	hbrBackground = Pêdzel wype³nienia obszaru roboczego okna podczas jego odœwie¿ania.
	lpszMenuName = Identyfikator menu do³¹czonego do tworzonego okna.
	lpszClassName = Adres ³ñcucha znaków okreœlaj¹cego nazwê klasy okna.
	hIconSm = Uchwyt tzw. ma³ej ikony (16x16 pikseli) wyœwietlanej m.in. na belce tytu³owej.
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

	return RegisterClassEx(&wcex); // Rejestruj klasê okna w systemie
}

/*  
	InitInstance(HINSTANCE hInstance, int nCmdShow)
	hInstance = Uchwyt okna.
	nCmdShow = Identyfikator sposobu wyœwietlania okna.

	Funkcja tworzy i wyœwietla okno g³ówne aplikacji.
	Zwraca TRUE (tworzenie okna powiod³o siê) lub FALSE.
*/
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	

   HWND hWnd;

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

	lpClassName = Adres ³ñcucha znaków okreœlaj¹cego nazwê klasy okna.
	lpWindowName = Adres ³ñcucha znaków okreœlaj¹cego tekst na belce tytu³owej.
	dwStyle = standardowy styl okna (np. WS_SIZEBOX - krawêdŸ okna pozwala na 
				zmianê jego rozmiaru).
	x, y = pozycja górnego lewego naro¿nika okna.
	nWidth, nHeight = Szerokoœæ i wysokoœæ okna.
	hWndParent = Uchwyt okna-rodzica lub okna nadrzêdnego (w³aœciciela).
	hMenu = Uchwyt menu do³¹czonego do okna.
	hInstance = Uchwyt aplikacji (okna g³ównego).
	lpParam = 32-bitowa wartoœæ przekazana do procedury okna wraz z wiadomoœci¹ WM_CREATE.
   */

   if (!hWnd) // Je¿eli tworzenie okna siê nie powiod³o... 
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow); // Poka¿ okno.
   UpdateWindow(hWnd); // Natychmiast po wyœwietleniu okna odœwie¿ je.

   return TRUE;
}

/*  
	WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	hWnd = Uchwyt okna.
	message = Numer (kod) wiadomoœci.
	wParam = 32-bitowa wartoœæ bez znaku okreœlaj¹ca dodatkowe informacje o wiadomoœci.
	lParam = 32-bitowa wartoœæ (ze znakiem) okreœlaj¹ca dodatkowe informacje o wiadomoœci.

	Tzw. procedura okna.
	Funkcja przetwarza wiadomoœci wys³ane przez system do aplikacji (obs³uga zdarzeñ).
	Zwraca 32-bitow¹ liczbê ca³kowit¹ ze znakiem.
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message) // SprawdŸ typ wiadomoœci (komunikatu)
	{
	case WM_COMMAND: // Wybór z menu
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		
		switch (wmId) // SprawdŸ, który element (pole) menu wybrano
		{
		case IDM_ABOUT: // Poka¿ okno dialogowe "About"
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT: // WyjdŸ - zamknij program
			DestroyWindow(hWnd);
			break;
		default:
			// Procedura przetwarzaj¹ca wiadomoœæ w domyœlny sposób
			return DefWindowProc(hWnd, message, wParam, lParam); 
		}
		break;

	case WM_CREATE: // Tworzenie okna
		wr= WindowRange(hWnd);  // ustaw uchwyt okna w obiekcie zakresu
	    wr.SetRange(-100, -100, 100, 100); // domyœlny zakres osi
		break;

	case WM_PAINT: // Przerysowanie okna
		hdc = BeginPaint(hWnd, &ps);
		Paint(hWnd, &ps);	// rysuj w obszarze roboczym (procedura poni¿ej)
		EndPaint(hWnd, &ps);
		break;

	case WM_SIZE: // Zmiana rozmiaru okna
		wr.Update(hWnd);  // uaktualnij zakres
		//InvalidateRect(hWnd, NULL, true); // przerysuj wszystko
		break;

	case WM_DESTROY: // Niszczenie okna
		PostQuitMessage(0); // Wstaw wiadomoœæ WM_QUIT do kolejki aplikacji
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

/*
	Procedura okna dialogowego "About".
	Parametry i dzia³anie analogiczne do procedury okna g³ównego. 
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

	void defineEdges(int *a, int *b, int n) {
		this->edgesNumbers = n;
		this->edges = new Edge[this->edgesNumbers];
		for (int i = 0; i < this->edgesNumbers; i++) this->edges[i] = Edge(a[i], b[i]);
	}

	void drawObject(Graphics2D gr) {
		for (int i = 0; i < this->edgesNumbers; i++) {
			if(i == 0 )
				gr.SetPen(Graphics2D::cl_RED, PS_SOLID, 1);
			if(i == 4)
				gr.SetPen(Graphics2D::cl_BLUE, PS_SOLID, 1);
			if(i == 8)
				gr.SetPen(Graphics2D::cl_CYAN, PS_SOLID, 1);

			Cvector pointA = pointsVectors[edges[i].getA()].GetPersp(0, 0, 12);
			Cvector pointB = pointsVectors[edges[i].getB()].GetPersp(0, 0, 12);

			gr.DrawLine(pointA.GetX(), pointA.GetY(), pointB.GetX(), pointB.GetY());
		}
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

	// Pobranie uchwytu kontekstu urz¹dzenia na podstawie uchwytu okna
	HDC hdc= GetDC(hwnd); // lub: HDC hdc= ps->hdc;

	// Utworzenie obiektu klasy Graphics2D za pomoc¹ konstruktora parametrowego dla danego kontekstu i zakresu okna
	Graphics2D gr(hdc, &wr);

	wr.SetProportional(true);
	wr.SetRange(-10.0, -10.0, 10.0, 10.0);
	gr.Update();

	//gr.DrawLine(-10, 0, 10, 0);
	//gr.DrawLine(0, -10, 0, 10);
	
	float x[8] = { 0, 0, 2, 2,	 0, 0, 2, 2 },
		  y[8] = { 0, 2, 0, 2,	 0, 2, 0, 2 },
		  z[8] = { 0, 0, 0, 0,	 2, 2, 2, 2 };

	/*float	x[11] = { 0, 0, 2, 2},
			y[11] = { 0, 2, 0, 2},
			z[11] = { 0, 0, 0, 2};*/


	object kostka(x, y, z, 12);
	int a[12] = {0, 0, 1, 3,	 4, 4, 5, 7,	 0, 1, 2, 3},
		b[12] = {1, 2, 3, 2,	 5, 6, 7, 6,	 4, 5, 6, 7};

	kostka.defineEdges(a, b, 12);
	

	Cmatrix transformacja;
	transformacja.SetTranslate(1, 2, 3);
	transformacja.SetRotateOY(1.1);
	//transformacja.SetScale(0.9);
	kostka.affineTransform(transformacja);

	Cmatrix obrot;
	obrot.SetRotateOX(0.2);
	kostka.affineTransform(obrot);

	Cmatrix skala;
	skala.SetScale(2,3,4);
	kostka.affineTransform(skala);
	kostka.drawObject(gr);

	//gr.DrawPolygon(x, y, 11);
	
	gr.~Graphics2D(); // wywo³anie destruktora obiektu gr
	ReleaseDC(hwnd, hdc);
}
