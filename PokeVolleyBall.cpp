﻿// PokeValleyBall.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "pch.h"
#include "stdafx.h"
#include "PokeVolleyBall.h"
#include "Client.h"


#define MAX_LOADSTRING 100
#define RENDER_TIMER_ID 0


// 전역 변수:
WCHAR szTitle[MAX_LOADSTRING];								// 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];						// 기본 창 클래스 이름입니다.
WindowsClient game_client{ RESOLUTION_W, RESOLUTION_H };	// 클라이언트 객체입니다.
GameFramework game_framework;


template<class GInstance>
auto instance_nearest(double x, double y) {

}

template<class GInstance1, class GInstance2>
auto instance_place(GInstance1 whoami, double x, double y) {

}

template<class GInstance>
auto instance_position(double x, double y) {
	if (game_framework.state_id)
		return new GInstance(game_framework.state_id, x, y);
	else
		return nullptr;
}

template<>
auto instance_position<ALL>(double x, double y) {}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
					  _In_opt_ HINSTANCE hPrevInstance,
					  _In_ LPWSTR    lpCmdLine,
					  _In_ int       nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_POKEVALLEYBALL, szWindowClass, MAX_LOADSTRING);


	// 애플리케이션 초기화를 수행합니다:
	if (!game_client.initialize(hInstance, WndProc, szTitle, szWindowClass, nCmdShow)) {
		return FALSE;
	}


	// 단축키의 목록을 불러옵니다.
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_POKEVALLEYBALL));
	MSG msg{};


	// 게임 초기화
	game_framework.init();

	// 사용자 코드입니다:
	game_framework.input_register(VK_LEFT);
	game_framework.input_register(VK_RIGHT);
	game_framework.input_register(VK_UP);
	game_framework.input_register(VK_DOWN);

	var room_0 = game_framework.state_push<sceneGame>();
	var inst_0 = room_0->instance_create<oValleyBall>(0.0, 0.0);
	var find_0 = room_0->instance_seek<oValleyBall>(0);
	cout << find_0->done << endl;

	// 게임 빌드
	game_framework.build();

	// 기본 메시지 루프입니다:
	bool done = false;

	while (true) { // 1
		game_framework.on_create();

		while (true) { // 2
			if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				if (msg.message == WM_QUIT) {
					done = true;
					break;
				}

				if (!::TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
					::TranslateMessage(&msg);
					::DispatchMessage(&msg);
				}
			}

			auto status = game_framework.update();
			if (!status) { // The current state is completed.
				break;
			}
		} // 2
		game_framework.on_destroy();

		if (game_framework.state_remains()) {
			game_framework.state_jump_next();
		} else {
			break;
		}

		if (done)
			break;
	} // 1

	game_framework.quit();
	game_framework.state_clear();

	return (int)msg.wParam;
}

////////////////////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		// 창 생성
		case WM_CREATE:
		{
			SetTimer(hwnd, RENDER_TIMER_ID, 1, NULL);
		}
		break;

		// 창 크기 조절
		case WM_SIZE:
		{
			game_client.width = LOWORD(lParam);
			game_client.height = HIWORD(lParam);
		}
		break;

		// 마우스 왼쪽 누름
		case WM_LBUTTONDOWN:
		{
			auto vk_status = game_framework.key_checkers[VB_LEFT];
			vk_status->pressing = true;

			game_framework.mouse_x = LOWORD(lParam);
			game_framework.mouse_y = HIWORD(lParam);
		}
		break;

		// 마우스 왼쪽 뗌
		case WM_LBUTTONUP:
		{
			auto vk_status = game_framework.key_checkers[VB_LEFT];
			vk_status->pressing = false;
		}
		break;

		// 마우스 오른쪽 누름
		case WM_RBUTTONDOWN:
		{
			auto vk_status = game_framework.key_checkers[VB_RIGHT];
			vk_status->pressing = true;

			game_framework.mouse_x = LOWORD(lParam);
			game_framework.mouse_y = HIWORD(lParam);
		}
		break;

		// 마우스 오른쪽 뗌
		case WM_RBUTTONUP:
		{
			auto vk_status = game_framework.key_checkers[VB_RIGHT];
			vk_status->pressing = false;
		}
		break;

		// 마우스 휠 누름
		case WM_MBUTTONDOWN:
		{
			auto vk_status = game_framework.key_checkers[VB_MIDDLE];
			vk_status->pressing = true;

			game_framework.mouse_x = LOWORD(lParam);
			game_framework.mouse_y = HIWORD(lParam);
		}
		break;

		// 마우스 휠 뗌
		case WM_MBUTTONUP:
		{
			auto vk_status = game_framework.key_checkers[VB_MIDDLE];
			vk_status->pressing = false;
		}
		break;

		// 키보드 누름
		case WM_KEYDOWN:
		{
			if (wParam == VK_F1) {
				DialogBox(game_client.instance, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, About);
				break;
			}
			
			auto vk_status = game_framework.key_checkers.find(wParam);
			if (vk_status != game_framework.key_checkers.end()) {
				vk_status->second->pressing = true;
			}
		}
		break;

		// 키보드 뗌
		case WM_KEYUP:
		{
			auto vk_status = game_framework.key_checkers.find(wParam);
			if (vk_status != game_framework.key_checkers.end()) {
				vk_status->second->pressing = false;
			}
		}
		break;

		// 렌더링 타이머
		case WM_TIMER:
		{
			Render::refresh(hwnd);
		}
		break;

		// 렌더링
		case WM_PAINT:
		{
			game_framework.on_render(hwnd);
		}
		break;

		// 창 종료
		case WM_DESTROY:
		{
			KillTimer(hwnd, RENDER_TIMER_ID);
			PostQuitMessage(0);
		}
		break;

		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
		case WM_INITDIALOG:
			return (INT_PTR)TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			break;
	}
	return (INT_PTR)FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////

GameBehavior::GameBehavior() : data(0), done(false) {}

GameBehavior::~GameBehavior() {}

GameInstance::GameInstance(GameScene* nclan, double nx, double ny)
	: parent(), room(nclan), sprite_index(-1), box{ 0, 0, 0, 0 }
	, x(nx), y(ny), image_number(0), image_index(0.0), image_speed(0.0) {}

GameInstance::~GameInstance() {
	signout();
}

void GameInstance::signout() {
	if (room) {
		room->instance_uninstall(this);
		room = nullptr;
	}
}

void GameInstance::signin(GameScene* enter) {
	enter->instance_install(this);
	room = enter;
}

void GameInstance::on_create() {}

void GameInstance::on_destroy() {}

void GameInstance::on_update(double frame_advance) {}

void GameInstance::on_update_later(double frame_advance) {
	if (-1 != sprite_index) {
		double animation_speed;
		if (1 < image_number && 0.0 != (animation_speed = image_speed * frame_advance)) {
			image_index += animation_speed;

			while (image_index < 0) image_index += image_number;
			while (image_number <= image_index) image_index -= image_number;
		}
	}
}

void GameInstance::on_render(HDC canvas) {}



////////////////////////////////////////////////////////////////////////////////////////////

sceneIntro::sceneIntro() : parent() {}

sceneIntro::~sceneIntro() {}

sceneTitle::sceneTitle() : parent() {}

sceneTitle::~sceneTitle() {}

sceneGame::sceneGame() {}

sceneGame::~sceneGame() {}

void sceneGame::on_create() {}

void sceneGame::on_destroy() {}

void sceneGame::on_update(double frame_advance) {}

void sceneGame::on_update_later(double frame_advance) {}

void sceneGame::on_render(HDC canvas) {}

sceneMainMenu::sceneMainMenu() {}

sceneMainMenu::~sceneMainMenu() {}

////////////////////////////////////////////////////////////////////////////////////////////

oGraviton::oGraviton(GameScene* nclan, double nx, double ny)
	: parent(nclan, nx, ny), hspeed(0.0), vspeed(0.0), gravity(GRAVITY) {
}

void oGraviton::on_create() {}

void oGraviton::on_destroy() {}

void oGraviton::on_update(double frame_advance) {
	if (frame_advance <= 0)
		return;

	var xspeed = px_per_sec(hspeed) * frame_advance;
	if (0.0 != xspeed) {
		GameBehavior* check_horizontal;
		if (0.0 < xspeed)
			check_horizontal = false; // instance_place<oSolid>(x + xspeed + 1, y);
		else
			check_horizontal = false; // instance_place<oSolid>(x + xspeed - 1, y);

		if (check_horizontal) {
			
		} else {
			x += xspeed;
		}
	}

	if (0 != hspeed) {
		var yspeed = px_per_sec(vspeed);

		y += yspeed;
	}
	
}

void oGraviton::on_render(HDC canvas) {}

oValleyBall::oValleyBall(GameScene* nclan, double nx, double ny) : parent(nclan, nx, ny) {}
