#pragma once
#include "resource.h"


// Ŭ���̾�Ʈ �޼��� ����
class WindowsClient {
public:
	/// <summary>
	///		GameClient(width, height)
	/// </summary>
	/// <param name="width">â�� �ʺ�</param>
	/// <param name="height">â�� ����</param>
	WindowsClient(const LONG, const LONG);
	~WindowsClient();

	/// <summary>
	///		initialize(handle)
	/// 
	///		�� â Ŭ������ ����ϰ� �����մϴ�.
	/// </summary>
	/// <param name="handle">â �ν��Ͻ�</param>
	/// <param name="procedure">�޽��� ó�� �޼���</param>
	/// <param name="title">Ŭ���̾�Ʈ ����</param>
	/// <param name="id">Ŭ���̾�Ʈ �ĺ���</param>
	/// <param name="cmd_show">â ���� ���</param>
	BOOL initialize(HINSTANCE, WNDPROC, LPCWSTR, LPCWSTR, INT);

	HINSTANCE instance;						// ���μ��� �ν��Ͻ�
	HWND hwindow;							// â �ν��Ͻ�
	WindowProcedure procedure;				// â ó����
	WNDCLASSEX properties;					// â �������
	LPCWSTR title_caption, class_id;		// â �ĺ���
	LONG width, height;						// â ũ��
};
