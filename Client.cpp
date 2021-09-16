#include "pch.h"
#include "Client.h"


WindowsClient::WindowsClient(const LONG cw, const LONG ch) : width(cw), height(ch), procedure(NULL) {}

WindowsClient::~WindowsClient() {
	UnregisterClassW(class_id, instance);
}

BOOL WindowsClient::initialize(HINSTANCE handle, WNDPROC procedure, LPCWSTR title, LPCWSTR id, INT cmd_show) {
	properties.cbSize = sizeof(WNDCLASSEX);
	properties.style = CS_HREDRAW | CS_VREDRAW;
	properties.lpfnWndProc = procedure;
	properties.cbClsExtra = 0;
	properties.cbWndExtra = 0;
	properties.hInstance = handle;
	properties.hIcon = LoadIcon(handle, MAKEINTRESOURCE(IDI_POKEVALLEYBALL));
	properties.hCursor = LoadCursor(nullptr, IDC_ARROW);
	properties.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	properties.lpszMenuName = MAKEINTRESOURCE(IDC_POKEVALLEYBALL);
	properties.lpszClassName = id;
	properties.hIconSm = LoadIcon(properties.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassEx(&properties);


	HWND hWnd = CreateWindow(id, title, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX
							  , CW_USEDEFAULT, 0, width, height, nullptr, nullptr, instance, nullptr);
	instance = handle;
	title_caption = title;
	class_id = id;

	if (!hWnd) {
		return FALSE;
	}

	hwindow = hWnd;
	ShowWindow(hWnd, cmd_show);
	UpdateWindow(hWnd);

	return TRUE;
}
