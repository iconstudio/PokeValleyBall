#pragma once
#include "resource.h"
#include "Framework.h"
#include "Phaser.h"
#include "Sprite.h"
#include "Core.h"


constexpr double GRAVITY = px_per_sec(0.098);

// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

class GCamera {
public:
	GCamera();
	~GCamera();

	void on_update_later(HWND);

	bool canmove = true;

	static long width, height;		// ���� ũ��
	RECT* rect;						// ���� �簢��
	double x, y;					// ���� ��ǥ
	double destx, desty;			// ���� ��ǥ ��ǥ
	double speed = 10;				// ���� �ӵ� (-1 �̸� �ٷ� �̵�)

	double hspeed, vspeed;			// ���� �ӵ� (���� ����)
};


// �ΰ� ���Ժ�
class sceneIntro : public GameScene {
public:
	// ���� Ÿ��
	using type = sceneIntro;
	using parent = GameScene;

	sceneIntro();
	sceneIntro(type&) = default;
	virtual ~sceneIntro();

private:
	Phaser state{ 0.4f, 3.0f, 0.6f };
	double alpha = 0.0;
};

// Ÿ��Ʋ
class sceneTitle : public GameScene {
public:
	// ���� Ÿ��
	using type = sceneTitle;
	using parent = GameScene;

	sceneTitle();
	sceneTitle(type&) = default;
	virtual ~sceneTitle();

private:

};

// �� �޴�
class sceneMainMenu : public GameScene {
public:
	// ���� Ÿ��
	using type = sceneMainMenu;
	using parent = GameScene;

	sceneMainMenu();
	sceneMainMenu(type&) = default;
	virtual ~sceneMainMenu();

private:

};

// ���� �غ�
class sceneGameReady : public GameScene {
public:
	// ���� Ÿ��
	using type = sceneGameReady;
	using parent = GameScene;

	sceneGameReady();
	sceneGameReady(type&) = default;
	virtual ~sceneGameReady();

private:

};

// ���� ��
class sceneGame : public GameScene {
public:
	// ���� Ÿ��
	using type = sceneGame;
	using parent = GameScene;

	sceneGame();
	sceneGame(type&) = default;
	virtual ~sceneGame();

	virtual void on_create() override;
	virtual void on_destroy() override;
	virtual void on_update(double frame_advance) override;
	virtual void on_update_later(double frame_advance) override;
	virtual void on_render(HDC canvas) override;

private:

};

// ���� �Ͻ� ����
class sceneGamePaused : public GameScene {
public:
	// ���� Ÿ��
	using type = sceneGamePaused;
	using parent = GameScene;

	sceneGamePaused();
	sceneGamePaused(type&) = default;
	virtual ~sceneGamePaused();

private:

};

// ���� �ϼ�
class sceneGameComplete : public GameScene {
public:
	// ���� Ÿ��
	using type = sceneGameComplete;
	using parent = GameScene;

	sceneGameComplete();
	sceneGameComplete(type&) = default;
	virtual ~sceneGameComplete();

private:

};

// ���� ����
class sceneScoring : public GameScene {
public:
	// ���� Ÿ��
	using type = sceneScoring;
	using parent = GameScene;

	sceneScoring();
	sceneScoring(type&) = default;
	virtual ~sceneScoring();

private:

};

// ����
class sceneSetting : public GameScene {
public:
	// ���� Ÿ��
	using type = sceneSetting;
	using parent = GameScene;

	sceneSetting();
	sceneSetting(type&) = default;
	virtual ~sceneSetting();

private:

};

class oSolid : public GameInstance {
public:
	const long my_serial = 2L;
	static constexpr long serial = 2L;

	// ���� Ÿ��
	using type = oSolid;
	using parent = GameInstance;
};

// �߷� ��ü
class oGraviton : public GameInstance {
	public:
		const long my_serial = 1L;
		static constexpr long serial = 1L;

		// ���� Ÿ��
		using type = oGraviton;
		using parent = GameInstance;

		oGraviton(GameScene* nclan, double nx, double ny);
		oGraviton(type&) = default;

		virtual void on_create() override;
		virtual void on_destroy() override;
		virtual void on_update(double frame_advance) override;
		virtual void on_render(HDC canvas) override;

		double hspeed, vspeed, gravity;

};

class oValleyBall : public oGraviton {
public:
	const long my_serial = 3L;
	static constexpr long serial = 3L;

	// ���� Ÿ��
	using type = oValleyBall;
	using parent = oGraviton;

	oValleyBall(GameScene* nclan, double nx, double ny);
	oValleyBall(type&) = default;


};

class oPokemon;
class oPlayerPoke;
class oEnemyPoke;
