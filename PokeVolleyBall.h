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

// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

constexpr LONG GROUND_Y = RESOLUTION_H - 100; // ���� ��ǥ
constexpr double GRAVITY = 6.0; // �ð� �� ���� �̵��Ÿ�

constexpr double PIKA_X_START_PLAYER = RESOLUTION_W * 0.3; // �÷��̾� ���� x ��ǥ
constexpr double PIKA_X_START_ENEMY = RESOLUTION_W * 0.7; // ��� ���� x ��ǥ
constexpr double PIKA_Y_START = GROUND_Y - 30.; // ���� ���� y ��ǥ

constexpr double BALL_PLAYER_X_START = PIKA_X_START_PLAYER; // �÷��̾� ������ �� ���� x ��ǥ
constexpr double BALL_PLAYER_Y_START = PIKA_Y_START - 200.; // �÷��̾� ������ �� ���� y ��ǥ
constexpr double BALL_ENEMY_X_START = PIKA_X_START_ENEMY; // �� ������ �� ���� x ��ǥ
constexpr double BALL_ENEMY_Y_START = PIKA_Y_START - 200.; // �� ������ �� ���� y ��ǥ

constexpr double FENCE_X_LEFT = RESOLUTION_W * 0.5 - 8.0; // ��� ��Ʈ�� ���� ���
constexpr double FENCE_X_RIGHT = RESOLUTION_W * 0.5 + 8.0; // ��� ��Ʈ�� ���� ���
constexpr double PLAYER_X_MIN = 10.0;
constexpr double PLAYER_X_MAX = FENCE_X_LEFT;
constexpr double ENEMY_X_MIN = FENCE_X_RIGHT;
constexpr double ENEMY_X_MAX = RESOLUTION_W - 10.0;
constexpr double FENCE_APGUREUGI_BOUNCE_MIN_XVELOCITY = 8.; // �ձ����� �Ҷ� ���� ������ �ðܳ� �ӵ��� �ּҰ�
constexpr double FIELD_SIZE = PLAYER_X_MAX - PLAYER_X_MIN; // �÷��̾ �ٴ� �� �ִ� ���� �ʺ�

constexpr double PIKA_MOVE_XACCEL = 4.; // ��ī�� �¿� ���ӵ�
constexpr double PIKA_MOVE_XVELOCITY = 25.; // ��ī�� �¿� �̵� �ӵ�
constexpr double PIKA_JUMP_VELOCITY = 140.; // ��ī�� ���� �ӵ�

constexpr double PIKA_APGUREUGI_GRAVITY = 1.1; // �ձ����� �Ҷ� �ٲ�� �߷�
constexpr double PIKA_APGUREUGI_XVELOCITY = 40.; // �ձ����� ���� �ӵ�
constexpr double PIKA_APGUREUGI_YVELOCITY = 11.; // �ձ����� �ٱ� �ӵ�
constexpr double PIKA_APGUREUGI_BOUNCE_YVELOCITY = 6.;
constexpr double PIKA_APGUREUGI_BOUNCE_STD_YVELOCITY = 7.;
constexpr double PIKA_APGUREUGI_REBOUND_DURATION = 0.26; // �ձ����� ���� �� ȸ�� �ð�

constexpr double PIKA_BLINK_DISTANCE = FIELD_SIZE * 0.5; // ������ȭ �Ÿ�
constexpr double PIKA_BLINK_DURATION = 0.2; // ������ȭ �ҿ� �ð�
constexpr double PIKA_BLINK_VELOCITY = PIKA_BLINK_DISTANCE / PIKA_BLINK_DURATION;
constexpr double PIKA_BLINK_REBOUND_DURATION = 0.45; // ������ȭ �� ȸ�� �ð�

constexpr double PIKA_STAMINA_MAX = 15.0; // �ִ� ü�� (�ð�)
constexpr double STAMINA_SPEND_APGUREUGI = 3.5; // �ձ������� �Ҹ� ü�� (�ð�)
constexpr double STAMINA_SPEND_BLINK = 5.5; // ������ȭ�� �Ҹ� ü�� (�ð�)

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
	using parent = GameScene;

	virtual void on_create() override;
	virtual void on_destroy() override;
	virtual void on_update(double frame_advance) override;
	virtual void on_update_later(double frame_advance) override;
	virtual void on_render(HDC canvas) override;

private:
	TURN turn; // ���� ����

	oVolleyBall* ball;
	oPlayerPoke* player;
	oEnemyPoke* enemy;
};

// ���� �Ͻ� ����
class sceneGamePaused : public GameScene {
public:
	using parent = GameScene;

private:

};

// ����
class sceneSetting : public GameScene {
public:
	using parent = GameScene;


private:

};

// �߷� ��ü
class oGraviton : public GameInstance {
public:
	using parent = GameInstance;

	oGraviton(GameScene* nclan, double nx, double ny);

	// �߷� ��ü ����
	virtual void on_update(double frame_advance) override;

	virtual void move(const double mx, const double my);
	virtual void jump(double power);
	virtual void contact();
	virtual void thud();

	double hspeed, vspeed, gravity;
	double hbounce, vbounce;
};

class oVolleyBall : public oGraviton {
public:
	using parent = oGraviton;

	oVolleyBall(GameScene* nclan, double nx, double ny);
};

class oPikachu : public oGraviton {
public:
	using parent = oGraviton;

	oPikachu(GameScene* nclan, double nx, double ny);

	virtual void on_update(double frame_advance) override;

	void walk(int direction, double frame_advance); // hspeed ����� �¿� �̵�
	void jump(double power); // vspeed ����� ����
	void thud(); // ����

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
	void set_xborder(const double min, const double max);

	GameInstance* ball;

private:
	bool jumping, sliding, blinking, carrying; // ���� �÷���

	double stamina; // ü��

	double wake_time;
	double x_min, x_max;
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
