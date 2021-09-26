#pragma once
#include "resource.h"


// ���� ������
class GameFramework {
public:
	GameFramework();
	~GameFramework();

	void input_register(const WPARAM virtual_button);
	bool input_check(const WPARAM virtual_button);
	bool input_check_pressed(const WPARAM virtual_button);

	void init();
	void build();
	bool update();

	void delta_start();
	void delta_inspect();
	double get_elapsed_second() const;

	size_t make_sprite(HINSTANCE instance, const UINT resource, const UINT number, const int xoff, const int yoff);
	size_t make_sprite(const LPCTSTR path, const UINT number, const int xoff, const int yoff);
	shared_ptr<GameSprite> find_sprite(const size_t index);

	void on_create(); // ���� ����
	void on_destroy(); // ���� ��
	void on_update(const double frame_advance);
	void on_update_later(const double frame_advance);
	void on_mousedown(const WPARAM button, const LPARAM cursor);
	void on_mouseup(const WPARAM button, const LPARAM cursor);
	void on_keydown(const WPARAM key);
	void on_keyup(const WPARAM key);
	void on_render(HWND window);

	template<class GScene>
	size_t state_push() {
		states.push_back(new GScene());

		return states.size() - 1;
	}

	bool state_is_done() const;
	void state_clear();
	bool state_remains();
	void state_jump(const INT);
	void state_jump_next();

	GameScene* state_id; // ���� ���� ������
	INT state_handle = 0; // ���� ������ ��ġ ��ȣ

	LONG mouse_x, mouse_y; // ���콺 ��ǥ

	HDC surface_app;
private:
	class GameInput {
	public:
		int time = -1;

		void on_press() { time++; }
		void on_release() { time = -1; }
		bool is_pressing() const { return (0 <= time); }
		bool is_pressed() const { return (0 == time); }
	};

	using tick_type = std::chrono::microseconds;
	using clock_type = std::chrono::system_clock::time_point;

	clock_type clock_previos, clock_now;
	LONGLONG elapsed;
	double delta_time;

	PAINTSTRUCT painter;

	deque<GameScene*> states; // ���� ��� ����
	vector<shared_ptr<GameSprite>> sprites;
	map<WPARAM, shared_ptr<GameInput>> key_checkers;
};

// ���콺 ��ư
const WPARAM VB_LEFT = 0, VB_MIDDLE = 1, VB_RIGHT = 2;
