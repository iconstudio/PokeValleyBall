#pragma once
#include "resource.h"
#include "Framework.h"
#include "Phaser.h"
#include "Sprite.h"
#include "Core.h"


constexpr double GRAVITY = km_per_hr(0.0098);


// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

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

	double hspeed, vspeed;			// ���� �ӵ� (���� ����)
};


// �ΰ� ���Ժ�
class sceneIntro : public GameScene {
public:
	using parent = GameScene;

private:
	Phaser state{ 0.4f, 3.0f, 0.6f };
	double alpha = 0.0;
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

	virtual void on_create() override;
	virtual void on_destroy() override;
	virtual void on_update(double frame_advance) override;
	virtual void on_update_later(double frame_advance) override;
	virtual void on_render(HDC canvas) override;

private:
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

		virtual void on_update(double frame_advance) override;

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

};

class oPlayerPoke : public oGraviton {

};

class oEnemyPoke : public oGraviton {

};
