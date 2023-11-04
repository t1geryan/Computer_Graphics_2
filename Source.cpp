#pragma once
#include "Loader.h"
#include "Render2D.h"

WNDCLASS createWindowClass(HBRUSH bgColor, HCURSOR cursor, HINSTANCE hInstance, HICON icon, LPCWSTR windowName, WNDPROC windowProcedure);
LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	WNDCLASS mainWindow = createWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInstance, LoadIcon(NULL, IDI_QUESTION), L"MainWndClass", windowProcedure);

	if (!RegisterClassW(&mainWindow))
		return -1;

	CreateWindow(L"MainWndClass", L"MainWindow", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 800, 800, NULL, NULL, NULL, NULL);

	MSG message = { 0 };
	while (GetMessage(&message, NULL, NULL, NULL)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return 0;
}

WNDCLASS createWindowClass(HBRUSH bgColor, HCURSOR cursor, HINSTANCE hInstance, HICON icon, LPCWSTR windowName, WNDPROC windowProcedure)
{
	WNDCLASS wc = { 0 };

	wc.hCursor = cursor;
	wc.hIcon = icon;
	wc.hInstance = hInstance;
	wc.lpszClassName = windowName;
	wc.hbrBackground = bgColor;
	wc.lpfnWndProc = windowProcedure;

	return wc;
}

Render2D render;
Loader triangleLoader("triangle.txt");
Loader trapezoidLoader("trapezoid.txt");
Loader shape3Loader("shape3.txt");

Model2D* models[] = { new Model2D(triangleLoader), new Model2D(trapezoidLoader), new Model2D(shape3Loader) };
size_t MODELS_COUNT = 3;
size_t selectedModelIndex = 0;
double translatingDelta = 0.1;
double rotateDelta = 0.1;
double scalingSize = .1;

LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	HDC hdc = NULL;

	switch (msg)
	{
	case WM_CREATE:
		for (size_t i = 0; i < MODELS_COUNT; ++i)
			render.addObject(models[i]);
		break;
	case WM_DESTROY:
		for (size_t i = 0; i < MODELS_COUNT; ++i)
			delete models[i];
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		hdc = GetDC(hWnd);
		render.draw(hdc);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_KEYDOWN:
		switch (wp)
		{
		case VK_LEFT: // <- compression by x
			models[selectedModelIndex]->scale((1 - scalingSize), 1);
			break;
		case VK_RIGHT: // -> stretching by x
			models[selectedModelIndex]->scale((1 + scalingSize), 1);
			break;
		case VK_UP: // stretching by y
			models[selectedModelIndex]->scale(1, (1 + scalingSize));
			break;
		case VK_DOWN: // compression by y
			models[selectedModelIndex]->scale(1, (1 - scalingSize));
			break;
		case 0x57: // W translate up
			models[selectedModelIndex]->translate(0, translatingDelta);
			break;
		case 0x53: // S translate down
			models[selectedModelIndex]->translate(0, -translatingDelta);
			break;
		case 0x41: // A translate left
			models[selectedModelIndex]->translate(-translatingDelta, 0);
			break;
		case 0x44: // D translate right
			models[selectedModelIndex]->translate(translatingDelta, 0);
			break;
		case 0x51: // Q rotate left
			models[selectedModelIndex]->rotate(-rotateDelta);
			break;
		case 0x45: // E rotate rigth
			models[selectedModelIndex]->rotate(rotateDelta);
			break;
		case 0x52: // R reflect by OX
			models[selectedModelIndex]->reflect(true, false);
			break;
		case 0x46: // F reflect by OY
			models[selectedModelIndex]->reflect(false, true);
			break;
		case 0x43: // C change figure
			selectedModelIndex = (selectedModelIndex + 1) % MODELS_COUNT;
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}
