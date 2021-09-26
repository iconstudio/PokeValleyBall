#pragma once
#include "resource.h"
#include "Framework.h"
#include "Phaser.h"
#include "Sprite.h"
#include "Core.h"

#define VK_CHAR_C 0x43
#define VK_CHAR_R 0x52
#define VK_CHAR_X 0x58
#define VK_CHAR_Z 0x5A
#define VK_CHAR_P 0x54

// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

constexpr LONG GROUND_Y = RESOLUTION_H - 100; // ���� ��ǥ
constexpr double GRAVITY = km_per_hr(300.0);
constexpr double GRAVITY_BALL = km_per_hr(190.0);

constexpr double PIKA_X_START_PLAYER = RESOLUTION_W * 0.3; // �÷��̾� ���� x ��ǥ
constexpr double PIKA_X_START_ENEMY = RESOLUTION_W * 0.7; // ��� ���� x ��ǥ
constexpr double PIKA_Y_START = GROUND_Y - 30.; // ���� ���� y ��ǥ

constexpr double BALL_PLAYER_X_START = PIKA_X_START_PLAYER; // �÷��̾� ������ �� ���� x ��ǥ
constexpr double BALL_PLAYER_Y_START = PIKA_Y_START - 200.; // �÷��̾� ������ �� ���� y ��ǥ
constexpr double BALL_ENEMY_X_START = PIKA_X_START_ENEMY; // �� ������ �� ���� x ��ǥ
constexpr double BALL_ENEMY_Y_START = PIKA_Y_START - 200.; // �� ������ �� ���� y ��ǥ

constexpr double FENCE_X_LEFT = RESOLUTION_W * 0.5 - 8.0; // ��� ��Ʈ�� ���� ���
constexpr double FENCE_X_RIGHT = RESOLUTION_W * 0.5 + 8.0; // ��� ��Ʈ�� ���� ���
constexpr double FENCE_HEIGHT = GROUND_Y * 0.4; // ��Ʈ ����
constexpr double FENCE_Y = GROUND_Y - FENCE_HEIGHT;
constexpr double PLAYER_X_MIN = 30.0;
constexpr double PLAYER_X_MAX = FENCE_X_LEFT;
constexpr double ENEMY_X_MIN = FENCE_X_RIGHT;
constexpr double ENEMY_X_MAX = RESOLUTION_W - 30.0;
constexpr double FENCE_APGUREUGI_BOUNCE_MIN_XVELOCITY = km_per_hr(8); // �ձ����� �Ҷ� ���� ������ �ðܳ� �ӵ��� �ּҰ�
constexpr double FIELD_SIZE = PLAYER_X_MAX - PLAYER_X_MIN; // �÷��̾ �ٴ� �� �ִ� ���� �ʺ�

constexpr double PIKA_MOVE_XACCEL = km_per_hr(190); // ��ī�� �¿� ���ӵ�
constexpr double PIKA_MOVE_XVELOCITY = km_per_hr(34); // ��ī�� �¿� �̵� �ӵ�
constexpr double PIKA_JUMP_VELOCITY = km_per_hr(100); // ��ī�� ���� �ӵ�

constexpr double PIKA_APGUREUGI_GRAVITY = km_per_hr(55); // �ձ����� �Ҷ� �ٲ�� �߷�
constexpr double PIKA_APGUREUGI_XVELOCITY = km_per_hr(47); // �ձ����� ���� �ӵ�
constexpr double PIKA_APGUREUGI_YVELOCITY = km_per_hr(12); // �ձ����� �ٱ� �ӵ�
constexpr double PIKA_APGUREUGI_BOUNCE_STD_YVELOCITY = km_per_hr(8);
constexpr double PIKA_APGUREUGI_BOUNCE_YVELOCITY = km_per_hr(6);
constexpr double PIKA_APGUREUGI_REBOUND_DURATION = 0.25; // �ձ����� ���� �� ȸ�� �ð�

constexpr double PIKA_BLINK_DISTANCE = FIELD_SIZE * 0.38; // ������ȭ �Ÿ�
constexpr double PIKA_BLINK_DURATION = 0.1; // ������ȭ �ҿ� �ð�
constexpr double PIKA_BLINK_VELOCITY = PIKA_BLINK_DISTANCE / PIKA_BLINK_DURATION;
constexpr double PIKA_BLINK_STOP_DURATION = 0.25; // ������ȭ �� ȸ�� �ð�
constexpr double PIKA_BLINK_RECOVER_DURATION = 1.0; // ������ȭ �� ȸ�� �ð�
constexpr double PIKA_BLINK_REBOUND_VELOCITY = km_per_hr(20);

constexpr double PIKA_STAMINA_MAX = 15.0; // �ִ� ü�� (�ð�)
constexpr double STAMINA_SPEND_APGUREUGI = 3.5; // �ձ������� �Ҹ� ü�� (�ð�)
constexpr double STAMINA_SPEND_BLINK = 5.5; // ������ȭ�� �Ҹ� ü�� (�ð�)


constexpr double BALL_HEADING_YVELOCITY = km_per_hr(72); // �Ϲ� ���
constexpr double BALL_HEADING_JUMP_YVELOCITY = km_per_hr(120); // ���� ���
constexpr double BALL_HEADING_APGUREUGI_YVELOCITY = km_per_hr(80); // �ձ������� �� ���
constexpr double BALL_HEADING_BLINK_YVELOCITY = km_per_hr(110); // ������ȭ�� �� ���
constexpr double BALL_SMASH_HAIRPIN_XVELOCITY = km_per_hr(80); // �������� ������ �����
constexpr double BALL_SMASH_HAIRPIN_YVELOCITY = km_per_hr(10); // �������� ������ �����
constexpr double BALL_SMASH_UP_XVELOCITY = -km_per_hr(50); // ���� �÷�ġ�� �佺
constexpr double BALL_SMASH_UP_YVELOCITY = km_per_hr(130); // ���� �÷�ġ�� �佺
constexpr double BALL_SMASH_SPIKE_YVELOCITY = km_per_hr(80); // ������ �Ʒ��� �����ȴ� ���Ž�
constexpr double BALL_SMASH_SPIKE_XVELOCITY = km_per_hr(140); // ������ �Ʒ��� �����ȴ� ���Ž�

enum class LOOKDIR : int { LEFT = -1, RIGHT = 1 };
enum class TURN { player, enemy };

// �ΰ� ���Ժ�
class sceneIntro : public GameScene {
public:
	virtual void on_create() override;
	virtual void on_destroy() override;
	virtual void on_update(double frame_advance) override;
	virtual void on_render(HDC canvas) override;

private:
	shared_ptr<GameSprite> sprite_index;
	double x = RESOLUTION_W * 0.5;
	double y = RESOLUTION_H * 0.5;

	Phaser state{ 0.6, 3.0, 0.8, 1.0 };
	double alpha = 1.0;
};

// Ÿ��Ʋ
class sceneTitle : public GameScene {
public:
	virtual void on_create() override;
	virtual void on_destroy() override;
	virtual void on_update(double frame_advance) override;
	virtual void on_render(HDC canvas) override;

private:
	shared_ptr<GameSprite> sprite_index;
	double x = RESOLUTION_W * 0.5;
	double y = RESOLUTION_H * 0.5 - 50;

	bool entering = false;
};

// �� �޴�
class sceneMainMenu : public GameScene {
public:
	virtual void on_create() override;
	virtual void on_destroy() override;
	virtual void on_update(double frame_advance) override;
	virtual void on_render(HDC canvas) override;

private:

};

// ���� ��
class sceneGame : public GameScene {
public:
	virtual void on_create() override;
	virtual void on_destroy() override;
	virtual void on_update(double frame_advance) override;
	virtual void on_update_later(double frame_advance) override;
	virtual void on_render(HDC canvas) override;

private:
	bool ready_done;
	double ready_counter;
	bool wining;
	TURN winner;

	int score_player, score_enemy;

	TURN turn; // ���� ����

	oVolleyBall* ball;
	oPlayerPoke* player;
	oEnemyPoke* enemy;
};

// ����
class sceneSetting : public GameScene {
public:
	using parent = GameScene;


private:

};

class oVolleyBall : public GameInstance {
public:
	oVolleyBall(GameScene* nclan, double nx, double ny);

	virtual void on_update(double frame_advance) override;

	virtual void thud_left();
	virtual void thud_right();
	virtual void thud();
};

class oPikachu : public GameInstance {
public:
	oPikachu(GameScene* nclan, double nx, double ny);

	virtual void on_update(double frame_advance) override;

	void walk(int direction, double frame_advance); // hspeed ����� �¿� �̵�
	void jump(double power); // vspeed ����� ����
	virtual void thud_left();
	virtual void thud_right();
	virtual void thud(); // ����

	void set_flag_jump(bool flag);
	void set_flag_roll(bool flag);
	void set_flag_blink(bool flag);

	bool can_action() const; // �ൿ�� �������� ����
	bool can_move() const; // �̵��� �������� ����
	bool can_jump() const; // ������ �������� ����
	bool can_smash() const; // ���Žð� �������� ����
	bool can_rollingforward() const; // �ձ����Ⱑ �������� ����
	bool can_blink() const; // ������ȭ�� �������� ����

	void rollingforward(); // �ձ�����
	void blink(); // ������ȭ

	void rolling_recover(); // �ձ����� �� ȸ��
	void blink_recover(); // ������ȭ �� ȸ��

	bool is_acting() const;
	bool is_jumping() const;
	bool is_rolling() const;
	bool is_blinking() const;

	void look_at(LOOKDIR direction);

	GameInstance* ball;

private:
	bool jumping, sliding, blinking, carrying; // ���� �÷���

	double stamina; // ü��

	double wake_time;
	double blink_time, blink_recover_time;
	LOOKDIR dir;
};

class oPlayerPoke : public oPikachu {
public:
	using parent = oPikachu;

	oPlayerPoke(GameScene* nclan, double nx, double ny);

	virtual void on_update(double frame_advance) override;
};

class oEnemyPoke : public oPikachu {
public:
	using parent = oPikachu;

	// �� �ʱ�ȭ
	oEnemyPoke(GameScene* nclan, double nx, double ny);

	// �� �ΰ�����
	virtual void on_update(double frame_advance) override;
};
