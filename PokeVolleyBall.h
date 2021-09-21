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

constexpr double PIKA_MOVE_XACCEL = 4.; // ��ī�� �¿� ���ӵ�
constexpr double PIKA_MOVE_XVELOCITY = 25.; // ��ī�� �¿� �̵� �ӵ�
constexpr double PIKA_JUMP_VELOCITY = 140.; // ��ī�� ���� �ӵ�

constexpr double PIKA_APGUREUGI_GRAVITY = 1.1; // �ձ����� �Ҷ� �ٲ�� �߷�
constexpr double PIKA_APGUREUGI_XVELOCITY = 40.; // �ձ����� ���� �ӵ�
constexpr double PIKA_APGUREUGI_YVELOCITY = 11.; // �ձ����� �ٱ� �ӵ�
constexpr double PIKA_APGUREUGI_BOUNCE_YVELOCITY = 6.;
constexpr double PIKA_APGUREUGI_BOUNCE_STD_YVELOCITY = 7.;
constexpr double PIKA_APGUREUGI_REBOUND_DURATION = 0.3; // �ձ����� ���� �� ȸ�� �ð�

constexpr double PIKA_STAMINA_MAX = 15.0; // �ִ� ü�� (�ð�)
constexpr double STAMINA_SPEND_APGUREUGI = 3.5; // �ձ������� �Ҹ� ü�� (�ð�)
constexpr double STAMINA_SPEND_BLINK = 5.5; // ������ȭ�� �Ҹ� ü�� (�ð�)

constexpr double FENCE_X_LEFT = RESOLUTION_W * 0.5 - 8.0; // ��� ��Ʈ�� ���� ���
constexpr double FENCE_X_RIGHT = RESOLUTION_W * 0.5 + 8.0; // ��� ��Ʈ�� ���� ���
constexpr double PLAYER_X_MIN = 10.0;
constexpr double PLAYER_X_MAX = FENCE_X_LEFT;
constexpr double ENEMY_X_MIN = FENCE_X_RIGHT;
constexpr double ENEMY_X_MAX = RESOLUTION_W - 10.0;
constexpr double FENCE_APGUREUGI_BOUNCE_MIN_XVELOCITY = 8.; // �ձ����� �Ҷ� ���� ������ �ðܳ� �ӵ��� �ּҰ�


enum class LOOKDIR : int { LEFT = -1, RIGHT = 1 };

enum class TURN { player, enemy };

class GameCamera {
public:
	GameCamera();
	~GameCamera();

	void on_update_later(HWND);

	bool canmove = true;

	static long width, height; // ���� ũ��
	RECT* rect; // ���� �簢��
	double x, y; // ���� ��ǥ
	double destx, desty; // ���� ��ǥ ��ǥ
	double speed = 100; // ���� �ӵ� (-1 �̸� �ٷ� �̵�)

	double hspeed, vspeed; // ���� �ӵ� (���� ����)
};

// �ΰ� ���Ժ�
class sceneIntro : public GameScene {
public:
	using parent = GameScene;

	virtual void on_create() override;
	// ���Ժ� ����� ���� �� �ΰ� ��������Ʈ�� �����մϴ�. �ſ� �Ŵ��� ��������Ʈ�� �޸𸮸� ���� �����մϴ�.
	virtual void on_destroy() override;
	virtual void on_update(double frame_advance) override;
	virtual void on_render(HDC canvas) override;

private:
	shared_ptr<GameSprite> logo;
	Phaser state{ 0.6, 3.0, 0.8, 1.0 };
	double alpha = 1.0;
};

// Ÿ��Ʋ
class sceneTitle : public GameScene {
public:
	using parent = GameScene;

private:

};

// �� �޴�
class sceneMainMenu : public GameScene {
public:
	using parent = GameScene;

private:

};

// ���� �غ�
class sceneGameReady : public GameScene {
public:
	using parent = GameScene;

private:

};

// ���� ��
class sceneGame : public GameScene {
public:
	using parent = GameScene;

	sceneGame();

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

// ���� �ϼ�
class sceneGameComplete : public GameScene {
public:
	using parent = GameScene;

private:

};

// ���� ����
class sceneScoring : public GameScene {
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

class oSolid : public GameInstance {
public:
	const long my_serial = 2L;
	static constexpr long serial = 2L;

	using parent = GameInstance;


};

// �߷� ��ü
class oGraviton : public GameInstance {
	public:
		const long my_serial = 1L;
		static constexpr long serial = 1L;

		using parent = GameInstance;

		oGraviton(GameScene* nclan, double nx, double ny);

		// �߷� ��ü ����
		virtual void on_update(double frame_advance) override;

		virtual void jump(double power);
		virtual void contact();
		virtual void thud();

		double hspeed, vspeed, gravity;
		double hbounce, vbounce;

};

class oVolleyBall : public oGraviton {
public:
	const long my_serial = 3L;
	static constexpr long serial = 3L;

	using parent = oGraviton;

	oVolleyBall(GameScene* nclan, double nx, double ny);
};

class oPokemon : public oGraviton {
public:
	const long my_serial = 4L;
	static constexpr long serial = 4L;

	using parent = oGraviton;

	oPokemon(GameScene* nclan, double nx, double ny);
	virtual ~oPokemon();

	virtual void on_create() override;
	virtual void on_update(double frame_advance) override;

	virtual void move(int direction, double frame_advance); // hspeed ����� �¿� �̵�
	virtual void jump(double power); // vspeed ����� ����
	virtual void thud(); // ����

	bool can_action(); // �̵��� ���� �������� ����
	bool can_rollingforward();
	bool can_blink();

	void rollingforward(); // �ձ�����
	void blink(); // ������ȭ

	void thud_recover(); // �ձ����� �� ȸ��
	void blink_recover(); // ������ȭ �� ȸ��

	void look_at(LOOKDIR direction);

	bool jumping, sliding, blinking; // ���� �÷���

	double stamina; // ü��

	double wake_time;
	double x_min, x_max;
	LOOKDIR dir;

	shared_ptr<GameInstance> ball;

};

class oPlayerPoke : public oPokemon {
public:
	const long my_serial = 5L;
	static constexpr long serial = 5L;

	using parent = oPokemon;

	oPlayerPoke(GameScene* nclan, double nx, double ny);

	virtual void on_update(double frame_advance) override;
};

class oEnemyPoke : public oPokemon {
public:
	const long my_serial = 6L;
	static constexpr long serial = 6L;

	using parent = oPokemon;

	oEnemyPoke(GameScene* nclan, double nx, double ny);

	virtual void on_update(double frame_advance) override;
};
