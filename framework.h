#pragma once
#include "resource.h"


class GameInput {
public:
	bool pressing = false;
};


// ���� ������
class GameFramework {
public:
	GameFramework();
	~GameFramework();

	UINT mouse_x, mouse_y; // ���콺 ��ǥ

	void input_register(int);
	bool input_check(int);
	//bool input_check_pressed(int button);
	//bool input_check_released(int button);

	void init();
	void build(); // ����� �ҷ��ɴϴ�.
	bool update();
	void quit();

	void on_create();
	void on_destroy();
	void on_update(double);
	void on_update_later(double);
	void on_render(HWND);

	template<class GScene = GameScene>
	GameScene* state_push() {
		var room = new GScene();
		states.push_back(room);

		return (GameScene*)room;
	}

	bool state_is_done() const;
	void state_clear();
	bool state_remains();
	void state_jump(const INT);
	void state_jump_next();

	friend LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
private:
	double delta_time; // ���� �ð�
	//GameChrono game_clock; // ���� �ð� ��� ��ü�Դϴ�.

	// ���� ��� ����
	deque<GameScene*> states;
	GameScene* state_id;
	INT state_handle = 0;

	PAINTSTRUCT painter; // ������ ����

	map<WPARAM, shared_ptr<GameInput>> key_checkers;
};

// ���콺 ��ư
const WPARAM VB_LEFT = 0, VB_MIDDLE = 1, VB_RIGHT = 2;
