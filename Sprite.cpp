#include "pch.h"
#include "Sprite.h"


GameSprite::GameSprite(HINSTANCE instance, const UINT resource, const UINT number, const int xoff, const int yoff)
	: raw(CImage()), raw_width(0), raw_height(0), width(0), height(0), number(number), xoffset(xoff), yoffset(yoff) {
	raw.LoadFromResource(instance, resource);
	if (raw.IsNull()) {
		WCHAR temp[256];

		swprintf_s(temp, TEXT("�ڿ� ��������Ʈ %u��(��) �ҷ����� �߿� ������ �߻��߽��ϴ�."), resource);

		int error = MessageBox(NULL, temp, TEXT("����"), MB_OK);

		if (error) {
			SendMessage(NULL, WM_CLOSE, 0, 0);
		}
	}
	
	raw.SetHasAlphaChannel(true);
	raw_width = raw.GetWidth();
	raw_height = raw.GetHeight();

	auto result = __process_image(raw, raw_width, raw_height);
	if (!result) {
		WCHAR temp[256];

		swprintf_s(temp, TEXT("�ڿ� ��������Ʈ %u��(��) �ùٸ� ũ�⸦ ���� ���� �ʽ��ϴ�."), resource);

		int error = MessageBox(NULL, temp, L"����", MB_OK);
		if (error) {
			SendMessage(NULL, WM_CLOSE, 0, 0);
		}
	}
}

GameSprite::GameSprite(const LPCTSTR path, const UINT number, const int xoff, const int yoff)
	: raw(CImage()), raw_width(0), raw_height(0), width(0), height(0), number(number), xoffset(xoff), yoffset(yoff) {
	raw.Load(path);
	if (raw.IsNull()) {
		WCHAR temp[256];

		swprintf_s(temp, TEXT("��� %s���� ��������Ʈ�� �ҷ��� �� �����ϴ�."), path);

		int error = MessageBox(NULL, temp, TEXT("����"), MB_OK);

		if (error) {
			SendMessage(NULL, WM_CLOSE, 0, 0);
		}
	}

	raw.SetHasAlphaChannel(true);
	raw_width = raw.GetWidth();
	raw_height = raw.GetHeight();

	auto result = __process_image(raw, raw_width, raw_height);
	if (!result) {
		WCHAR temp[256];

		swprintf_s(temp, TEXT("%s�� ��ġ�� �׸� ������ �ùٸ� ũ�⸦ ���� ���� �ʽ��ϴ�."), path);

		int error = MessageBox(NULL, temp, TEXT("����"), MB_OK);
		if (error) {
			SendMessage(NULL, WM_CLOSE, 0, 0);
		}
	}
}

GameSprite::~GameSprite() {
	if (0 < number) {
		for (auto& image : frames) {
			image->Destroy();
		}
	}
	raw.Destroy();

	frames.clear();
}

void GameSprite::draw(HDC surface, const double x, const double y, const UINT index, const double angle, const double xscale, const double yscale, const double alpha) {
	if (1 < number) {
		auto frame = frames.at(index).get();
		__draw_single(surface, *frame, x, y, angle, xscale, yscale, alpha);
	} else {
		__draw_single(surface, raw, x, y, angle, xscale, yscale, alpha);
	}
}

void GameSprite::set_bbox(const LONG left, const LONG right, const LONG top, const LONG bottom) {
	bbox.left = left;
	bbox.right = right;
	bbox.top = top;
	bbox.bottom = bottom;
}

const int GameSprite::get_width() const {
	return width;
}

const int GameSprite::get_height() const {
	return height;
}

bool GameSprite::__process_image(CImage& image, const size_t width, const size_t height) {
	if (0 < width && 0 < height) {
		if (1 < number) { // �ִϸ��̼��� ���ؼ��� ���η� ������ �׸��� �ʿ��մϴ�.
			int slice_w, temp_w;
			if (1 == width) {
				slice_w = 1;
			} else {
				temp_w = (width / number);
				if (temp_w < 2) { // 0, 1
					slice_w = 1;
				} else {
					slice_w = temp_w;
				}
			}

			// ����
			frames.reserve(number);

			auto raw_bitlevel = raw.GetBPP();

			for (UINT i = 0; i < number; ++i) { // ������ ����
				// 1. ������ �׸� ����
				auto image_slice = new CImage(); // make_shared<CImage>();
				image_slice->Create(slice_w, height, raw_bitlevel);
				image_slice->SetHasAlphaChannel(true);

				auto slice_buffer = image_slice->GetDC();

				// 2. ���� �׸��� (i * slice_width, 0)�� ��ġ�� ������ ���� �׸��� (0, 0) ��ġ�� ����
				raw.BitBlt(slice_buffer, 0, 0, slice_w, height, i * slice_w, 0, SRCCOPY);

				// 3. �޸� ����ȭ
				image_slice->ReleaseDC(); // slice_buffer ����

				// 4. ���� ���� (������ �������� ���� ���� �Ұ�)
				frames.emplace_back(image_slice);
			}

			this->width = slice_w;
			this->height = raw_height;
		} else { // one frame
			this->width = raw_width;
			this->height = raw_height;
		}

		set_bbox(-xoffset, this->width - xoffset, -yoffset, this->height - yoffset);
	} else { // failed!
		return false;
	}

	return true;
}

void GameSprite::__draw_single(HDC surface, CImage& image, const double dx, const double dy, const double angle, const double xscale, const double yscale, const double alpha) {
	if (0.0 != angle) {
		float cosine = (float)lengthdir_x(1, angle);
		float sine = (float)lengthdir_y(1, angle);

		int center_x = dx, center_y = dy;

		int nGraphicsMode = SetGraphicsMode(surface, GM_ADVANCED);

		// �����ʹ� �޸� y ��ǥ�� ������
		XFORM xform;
		xform.eM11 = cosine;
		xform.eM12 = sine ;
		xform.eM21 = -sine;
		xform.eM22 = cosine;
		xform.eDx = (center_x - cosine * center_x + sine * center_y);
		xform.eDy = (center_y - cosine * center_y - sine * center_x);

		Render::transform_set(surface, xform);

		center_x -= xoffset * xscale;
		center_y -= yoffset * yscale;

		if (alpha != 1.0)
			image.AlphaBlend(surface, center_x, center_y, width * abs(xscale), height * abs(yscale), 0, 0, width, height, (BYTE)(255 * alpha));
		else
			image.Draw(surface, center_x, center_y, width * abs(xscale), height * abs(yscale), 0, 0, width, height);

		Render::transform_set_identity(surface);
		SetGraphicsMode(surface, nGraphicsMode);
	} else {
		int tx = (int)(dx - xoffset * xscale);
		int ty = (int)(dy - yoffset * yscale);
		
		if (alpha != 1.0)
			image.AlphaBlend(surface, tx, ty, width * abs(xscale), height * abs(yscale), 0, 0, width, height, (BYTE)(255 * alpha));
		else
			image.Draw(surface, tx, ty, width * abs(xscale), height * abs(yscale), 0, 0, width, height);
	}
}
