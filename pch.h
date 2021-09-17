﻿// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

#pragma warning(disable : 4267) // size_t에서 int로 손실 경고
#pragma warning(disable : 4244) // double에서 int로 손실 경고, int에서 unsigned int로 손실 경고

#include "stdafx.h"

typedef LRESULT(CALLBACK* WindowProcedure)(HWND, UINT, WPARAM, LPARAM);

#define sign(_x) ((_x > 0) ? 1 : ((_x == 0) ? 0 : -1))
#define var auto

#define RESOLUTION_W 640 // 창 너비
#define RESOLUTION_H 480 // 창 높이

class GameCamera;
class GameInput;
class GameFramework;
class GameSprite;

class GameBehavior;
class GameScene;
class sceneTitle;
class sceneMainMenu;
class sceneGameReady;
class sceneGame;
class sceneGamePaused;
class sceneGameComplete;
class sceneScoring;
class sceneSetting;

class GameInstance;
class oSolid;
class oGraviton;
class oValleyBall;
class oPokemon;
class oPlayerPoke;
class oEnemyPoke;


namespace Render {
	void refresh(HWND hwnd);

	void transform_set(HDC, XFORM&);
	void transform_set_identity(HDC);
	void transform_set_rotation(HDC);

	BOOL draw_rectangle(HDC, int, int, int, int);
	void draw_end(HDC, HGDIOBJ, HGDIOBJ);

	static XFORM transform_identity{ 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f };
}


inline constexpr auto radtodeg(double value) {
	return value / M_PI * 180;
}

inline constexpr auto degtorad(double value) {
	return value * M_PI / 180;
}

inline double lengthdir_x(double length, double direction) {
	return cos(degtorad(direction)) * length;
}

inline double lengthdir_y(double length, double direction) {
	return -sin(degtorad(direction)) * length;
}


constexpr double pixel_to_meter = 0.03125; // 32px == 1m
constexpr double meter_to_pixel = 32.; // 1m == 32px, 1km == 32000px
constexpr double sec_to_hour = 3600.;

constexpr double px_per_sec(const double km_per_hr) {
	var result = km_per_hr * meter_to_pixel * 1000 / sec_to_hour;

	return result;
}

constexpr COLORREF COLOR_BLACK = RGB(0, 0, 0);
constexpr COLORREF COLOR_WHITE = RGB(255, 255, 255);
constexpr COLORREF COLOR_GREY = RGB(128, 128, 128);
constexpr COLORREF COLOR_LTGREY = RGB(192, 192, 192);
constexpr COLORREF COLOR_DKGREY = RGB(64, 64, 64);
constexpr COLORREF COLOR_SEMIBLACK = RGB(224, 224, 224);

constexpr COLORREF COLOR_SALMON = RGB(255, 128, 128);
constexpr COLORREF COLOR_RED = RGB(255, 0, 0);
constexpr COLORREF COLOR_MAROON = RGB(128, 0, 0);
constexpr COLORREF COLOR_LIME = RGB(0, 255, 0);
constexpr COLORREF COLOR_GREEN = RGB(0, 128, 0);
constexpr COLORREF COLOR_BLUE = RGB(0, 0, 255);
constexpr COLORREF COLOR_NAVY = RGB(20, 18, 149);
constexpr COLORREF COLOR_ORANGE = RGB(255, 128, 0);
constexpr COLORREF COLOR_YELLOW = RGB(255, 255, 0);
constexpr COLORREF COLOR_GOLD = RGB(223, 130, 20);
#endif //PCH_H
