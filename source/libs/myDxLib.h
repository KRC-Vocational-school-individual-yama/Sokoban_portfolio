#pragma once

#include<DxLib.h>

namespace DxLib {
	struct Vec2 {
		int x, y;
	};

	inline Vec2 operator +(const Vec2& a,const Vec2& b) {
		return Vec2{ a.x + b.x,a.y + b.y };
	}
	inline Vec2 operator -(const Vec2& a, const Vec2 b) {
		return Vec2{a.x-b.x,a.y-b.y};
	}
	inline Vec2 operator *(const Vec2& a, const Vec2& b) {
		return Vec2{a.x*b.x,a.y*b.y};
	}
	inline Vec2 operator /(const Vec2& a, const Vec2& b) {
		return Vec2{a.x/b.x,a.y/b.y};
	}
	inline Vec2 operator %(const Vec2& a, const Vec2& b) {
		return Vec2{a.x%b.x,a.y%b.y};
	}

	inline Vec2& operator +=( Vec2& a, const Vec2& b) {
		a.x += b.x;
		a.y += b.y;
		return a;
	}
	inline Vec2 operator -=( Vec2& a, const Vec2& b) {
		a.x -= b.x;
		a.y -= b.y;
		return a;
	}
	inline Vec2 operator *=(Vec2& a, const Vec2& b) {
		a.x *= b.x;
		a.y *= b.y;
		return a;
	}
	inline Vec2 operator /=(Vec2& a, const Vec2& b) {
		a.x /= b.x;
		a.y /= b.y;
		return a;
	}
	inline Vec2 operator %=(Vec2& a, const Vec2& b) {
		a.x %= b.x;
		a.y%= b.y;
		return a;
	}
	inline const bool operator ==(const Vec2& a, const Vec2& b) {
		return a.x==b.x&&a.y==b.y;
	}
}