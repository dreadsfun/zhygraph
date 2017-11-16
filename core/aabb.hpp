#pragma once
#include <glm/vec3.hpp>
#include <bitset>
using namespace glm;

class aabb {
private:
	vec3 mmid;
	vec3 msize;
	mutable std::bitset<8> mdirty;
	mutable vec3 mpoints[8];
#define minindex 6
#define maxindex 1
public:
	aabb(const vec3& mid, const vec3& size)
		: mmid(mid),
		msize(size) {
		mdirty.set();
	}
	aabb() {
		mdirty.set();
	}

	bool _gvec3(const vec3& v1, const vec3& v2) const {
		return v1.x > v2.x && v1.y > v2.y && v1.z > v2.z;
	}

	bool _lvec3(const vec3& v1, const vec3& v2) const {
		return v1.x < v2.x && v1.y < v2.y && v1.z < v2.z;
	}

	bool contains(const vec3& p) const {
		return _gvec3(p, min()) && _lvec3(p, max());
	}
	bool contains(const aabb& box) const {
		for (uint8_t i = 0; i < 8; ++i) {
			if (!this->contains(box.point(i))) {
				return false;
			}
		}
		return true;
	}
	const vec3& min() const {
		vec3& pmin = mpoints[minindex];
		if (mdirty.test(minindex)) {
			pmin = mmid - msize;
			mdirty.reset(minindex);
		}
		return pmin;
	}
	const vec3& max() const {
		vec3& pmax = mpoints[maxindex];
		if (mdirty.test(maxindex)) {
			pmax = mmid + msize;
			mdirty.reset(maxindex);
		}
		return pmax;
	}
	const vec3& point(uint8_t idx) const {
		assert(idx < 8);
		vec3& pp = mpoints[idx];
		if (mdirty.test(idx)) {
			std::bitset<3> i(idx);
			pp = vec3(
				(i.test(0) ? 1 : -1) * msize.x + mmid.x,
				(i.test(2) ? -1 : 1) * msize.y + mmid.y,
				(i.test(1) ? -1 : +1) * msize.z + mmid.z
			);
			mdirty.reset(idx);
		}
		return pp;
	}
	const vec3& size() const {
		return msize;
	}
	void size(const vec3& v) {
		msize = v;
		mdirty = true;
	}
	const vec3& mid() const {
		return mmid;
	}
	void mid(const vec3& v) {
		mmid = v;
		mdirty = true;
	}
};

class aabbvolume {
private:
	aabb mvol;
public:
	aabbvolume(const aabb& vol)
		: mvol(vol) {}
	bool containedin(const aabb& box) const {
		return box.contains(mvol);
	}
};