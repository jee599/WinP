#include "CFrameWork.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = "ApiBase";

CFrameWork* FrameWork;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(
		lpszClass, // ������ Ŭ���� �̸�
		"Shooting Simple", // ������ Ÿ��Ʋ �̸�
		WS_OVERLAPPEDWINDOW, // ������ ��Ÿ��
		300, // ������ ��ġ, x��ǥ 
		0, // ������ ��ġ, y��ǥ
		WIDTH + 20, // ������ ����(��) ũ�� 
		HEIGHT + 40, // ������ ����(����) ũ��
		NULL, // �θ� ������ �L��
		NULL, // �޴� �L��
		hInstance, // ���� ���α׷� �ν��Ͻ�
		NULL);   // ������ ������ ����
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM
	wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (iMessage) {

	case WM_CREATE:
		FrameWork = new CFrameWork;
		SetTimer(hwnd, 1, 100 / 60, NULL);
		break;
	
	case WM_LBUTTONDOWN:
		FrameWork->MouseDown(lParam);
		break;
	
	case WM_TIMER:
		if (wParam == 1)
			FrameWork->Animate();
		InvalidateRect(hwnd, NULL, FALSE);
		break;

	case WM_CHAR:
		break;

	case WM_KEYDOWN:
		FrameWork->KeyDown(wParam);
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_KEYUP:
		FrameWork->KeyUp(wParam);
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		FrameWork->Render(hdc);
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		delete FrameWork;
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMessage, wParam, lParam));
}