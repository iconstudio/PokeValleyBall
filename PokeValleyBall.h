#pragma once

#include "resource.h"


// �߻� ���� ������Ʈ
class GameBehavior {
public:
	using pointer = GameBehavior*;

	static pointer create() = delete;

	GameBehavior();
	virtual ~GameBehavior();

	virtual void on_create() = 0;
	virtual void on_destroy() = 0;
	virtual void on_update(double) = 0;
	virtual void on_update_later(double) = 0;
	virtual void on_render(HDC) = 0;

	int data;
	bool done;
};

