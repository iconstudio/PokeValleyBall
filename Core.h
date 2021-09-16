#pragma once
#include "resource.h"
#include "pch.h"


// �߻� ���� ������Ʈ
class GameBehavior {
public:
	// ���� Ÿ��
	using type = GameBehavior;

	GameBehavior() : data(0), done(false) {}
	virtual ~GameBehavior() {}

	virtual void on_create() = 0;
	virtual void on_destroy() = 0;
	virtual void on_update(double frame_advance) = 0;
	virtual void on_update_later(double frame_advance) = 0;
	virtual void on_render(HDC canvas) = 0;

	int data;
	bool done;
};

// �߻� ��� ������Ʈ
class GameScene : public GameBehavior {
public:
	// ���� Ÿ��
	using type = GameScene;
	using parent = GameBehavior;

	GameScene() : parent(), instances{} {}

	GameScene(type&) = default;

	virtual ~GameScene() {
		instances.clear();
	}

	void on_create() override {
		if (!instances.empty()) {
			for (const auto& instance : instances)
				instance->on_create();
		}
	}

	void on_destroy() override {
		if (!instances.empty()) {
			for (const auto& instance : instances)
				instance->on_destroy();
		}
	}

	void on_update(double frame_advance) override {
		if (!instances.empty()) {
			for (const auto& instance : instances)
				instance->on_update(frame_advance);
		}
	}

	void on_update_later(double frame_advance) override {
		if (!instances.empty()) {
			for (const auto& instance : instances)
				instance->on_update_later(frame_advance);
		}
	}

	void on_render(HDC canvas) override {
		if (!instances.empty()) {
			for (const auto& instance : instances)
				instance->on_render(canvas);
		}
	}

private:
	vector<GameBehavior*> instances;
};

// �߻� ��ü ������Ʈ
class GameInstance : public GameBehavior {
public:
	// ���� Ÿ��
	using type = GameInstance;
	using parent = GameBehavior;

	GameInstance(GameScene* nclan, double nx = 0.0, double ny = 0.0, double nz = 0.0)
		: parent(), room(nclan), sprite_index(-1), x(nx), y(ny), z(nz), image_index(0.0), image_speed(0.0) {}

	GameInstance(type&) = default;

	virtual ~GameInstance() {}

	virtual void on_create() = 0;
	virtual void on_destroy() = 0;
	virtual void on_update(double frame_advance) = 0;
	virtual void on_update_later(double frame_advance) = 0;
	virtual void on_render(HDC canvas) = 0;

	UINT sprite_index;
	double x, y, z, image_index, image_speed;

private:
	GameScene* room;
};
