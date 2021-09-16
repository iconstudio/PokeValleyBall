#pragma once
#include "resource.h"
#include "Framework.h"
#include "Phaser.h"
#include "Sprite.h"
#include "Core.h"


#define RENDER_TIMER_ID 0


// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);


template<class GInstance>
auto instance_create(double x, double y);


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


class oGraviton : public GameInstance {
	public:
		// ���� Ÿ��
		using type = oGraviton;
		using parent = GameInstance;

		double hspeed, vspeed, gravity;


};

class oValleyBall;
class oPokemon;
class oPlayerPoke;
class oEnemyPoke;

