#pragma once
#include "resource.h"


// Ŭ���̾�Ʈ �޼��� ����
class WindowsClient {
public:
	WindowsClient(LONG width, LONG height);
	~WindowsClient();

	BOOL initialize(HINSTANCE handle, WNDPROC procedure, LPCWSTR title, LPCWSTR id, INT cmd_show);

	HINSTANCE instance;						// ���μ��� �ν��Ͻ�
	HWND hwindow;							// â �ν��Ͻ�
	WindowProcedure procedure;				// â ó����
	WNDCLASSEX properties;					// â �������
	LPCWSTR title_caption, class_id;		// â �ĺ���
	LONG width, height;						// â ũ��
};
