
#include <bitset>
#include <iostream>
#include <unordered_map>
#include <cassert>

class vec3 {
private:
	float mx{ .0f };
	float my{ .0f };
	float mz{ .0f };
public:
	vec3() = default;
	vec3(float x, float y, float z)
		: mx(x),
		my(y),
		mz(z) {}
	vec3(float xy, float z)
		: mx(xy),
		my(xy),
		mz(z) {}
	vec3(float xyz)
		: mx(xyz),
		my(xyz),
		mz(xyz) {}
	const float& x() const {
		return mx;
	}
	float& x() {
		return mx;
	}
	const float& y() const {
		return my;
	}
	float& y() {
		return my;
	}
	const float& z() const {
		return mz;
	}
	float& z() {
		return mz;
	}
	bool operator < (const vec3& o) const {
		return mx < o.mx && my < o.my && mz < o.mz;
	}
	bool operator > (const vec3& o) const {
		return mx > o.mx && my > o.my && mz > o.mz;
	}
	bool operator == (const vec3& o) const {
		return mx == o.mx && my == o.my && mz == o.mz;
	}
	vec3 operator - (const vec3& o) const {
		return{ mx - o.mx, my - o.my, mz - o.mz };
	}
	vec3 operator / (float v) const {
		return{ mx / v, my / v, mz / v };
	}
	vec3 operator + (const vec3 o) const {
		return{ mx + o.mx, my + o.my, mz + o.mz };
	}
	vec3 absl() const {
		return{ abs(mx), abs(my), abs(mz) };
	}
	float len() const {
		return sqrt(mx * mx + my * my + mz * mz);
	}
	vec3 lenvec() const {
		return vec3(this->len());
	}
};

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
	bool contains(const vec3& p) const {
		return p > min() && p < max();
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
				(i.test(0) ? 1 : -1) * msize.x() + mmid.x(),
				(i.test(2) ? -1 : 1) * msize.y() + mmid.y(),
				(i.test(1) ? -1 : +1) * msize.z() + mmid.z()
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

/*
volume_t template interface:
	bool containedin(const aabb& box) const;
		returns true if the volume is contained in the box,
		false otherwise

	bool equals(const volume_t& vol) const;
		returns true if the volume equals to the specified one,
		false otherwise

	bool changed() const;
		returns true if the volume has changed since the last call to changed()
*/
template<typename t>
class octree_node {
private:
	using volume_t = t;
	using volume_list_t = std::list< volume_t& >;
	using poctree_node = octree_node*;
	aabb mbox;
	poctree_node mchildren[8];
	volume_list_t mvolumes;
	size_t mmaxvolume;
public:
	octree_node() {
		_rawrst();
	}
	octree_node(const aabb& box, size_t maxv = std::numeric_limits<size_t>::max())
		: mbox(box),
		mmaxvolume(maxv) {
		_rawrst();
	}
	uint64_t update() {
		for (auto it = mvolumes.begin(); it != mvolumes.end(); ++it) {
			if (v.changed())
				if (!v.containedin(mbox)) {
					mvolumes.erase(it);
				}
		}
		for (uint8_t i = 0; i < 8; ++i) {
			mchildren[i]->update();
		}
	}
	poctree_node matchvolume(const volume_t& vol) {
		const poctree_node r = this;
		if (vol.containedin(mbox)) {
			for (uint8_t i = 0; i < 8; ++i) {
				const poctree_node cc = mchildren[i];
				if (cc != nullptr) {
					cc = cc->matchvolume(vol);
				}
				if (cc != nullptr) {
					r = cc;
					break;
				}
			}
			return r;
		} else {
			return nullptr;
		}
	}
	poctree_node search(const volume_t& vol) const {
		poctree_node r = this->matchvolume(vol);
		for (volume_t& v : mvolumes) {
			if (v.equals(vol)) {
				return r;
			}
		}
		return nullptr;
	}
	bool addvolume(volume_t& vol) {
		if (vol.containedin(mbox)) {
			/*
			insertion into this node is only possible if the volume
			is inside this node's bounding box - this is basic requirement for an octree
			*/
			bool initch = false;
			for (uint8_t i = 0; i < 8; ++i) {
				if (mchildren[i] == nullptr) {
					/*
					mark if any of this nodes children is not initialized yet
					*/
					initch = true;
				}
				else if (mchildren[i]->addvolume(vol)) {
					/*
					if the child is initialized, then try to insert the volume into it
					this is to ensure, that the volume is inserted into the smallest possible successor
					and if it succeeded, then the whole insertion is succeeded
					*/
					return true;
				}
			}
			/*
			if we get here, it means that none of the initialized subtrees of the node
			could accept the volume, so it must check if one of the uninitialized child could
			accept it
			*/
			if (initch) {
				aabb tmpbox;
				for (uint8_t i = 0; i < 8; ++i) {
					/*
					iterate over the child indices, and generate the index bit mask
					if we look at the front of the node's bounding box the axes are aligned as follows:
					 x increments to the right, y increments to the top, z increments towards the viewer
					 the right-most bit is set if the child node is in positive direction from the mid point on the x-axis
					 the middle bit is set if the child node is in negative direction from the mid point on the z-axis
					 the left-most bit is set if the child node is in negative direction from the mid point on the y-axis
					*/
					std::bitset<3> bidx(i);
					vec3 tmpmid = {
						(bidx.test(0) ? 1 : -1) * mbox.size().x() / 2,
						(bidx.test(2) ? -1 : 1) * mbox.size().y() / 2,
						(bidx.test(1) ? -1 : +1) * mbox.size().z() / 2
					};
					/*
					here a temporary bounding box is created, which would be the bounding box of the
					i th child of this node if it was initialized
					if the volume fits inside this temporary BB, then a new child is initialized with the BB
					and the volume is inserted into the new child.. calling addvolume recursively ensures - once again -
					that the volume is inserted into the smallest possible successor of the node
					*/
					tmpbox.mid(tmpmid);
					tmpbox.size(mbox.size() / 2);
					if (vol.containedin(tmpbox)) {
						poctree_node nn = new octree_node(tmpbox, mmaxvolume);
						mchildren[i] = nn;
						return nn->addvolume(vol);
					}
				}
			}
			/*
			if the function gets here, it means that none of this node's initialized children could accept
			the specified volume, and none of the uninitialized could have accepted it either, meaning that
			this node must accept the volume, if size of the list of the accepted volumes is not exceeded by the max size
			*/
			if (mvolumes.size() == mmaxvolume)
				return false;
			else
				mvolumes.push_back(vol);
			return true;
		} else {
			return false;
		}
	}
private:
	void _rawrst() {
		for (uint8_t i = 0; i < 8; ++i) {
			mchildren[i] = nullptr;
		}
	}
	void _collapse() {
		for (uint8_t i = 0; i < 8; ++i) {
			poctree_node& cc = mchildren[i];
			if (cc != nullptr)
				cc->_collapse();
			cc = nullptr;
		}
		delete this;
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

template<typename t>
class octree {
private:
	using volume_t = t;
	using poctree_node = octree_node< volume_t >*;
	poctree_node mroot;
public:
	octree(const aabb& box) {
		mroot = new octree_node< volume_t >(box);
	}
	bool addbox(const aabb& box) {
		return mroot->addbox(box);
	}
	const poctree_node matchbox(const aabb& box) {
		return mroot->matchbox(box);
	}
};

int main() {
	octree< aabbvolume > ot(aabb(vec3(), vec3(1.f)));

	vec3 m1(0.13f, 0.26f, 0.12f);
	vec3 s1(.1f);

	aabb obj1(m1, s1);
	aabb obj2(m1, s1);
	aabb obj3(m1, s1);
	aabb obj4(m1, s1);

	obj1.point(1) == obj1.max();
	obj1.point(6) == obj1.min();

	ot.addbox(obj1);
	ot.addbox(obj2);
	ot.addbox(obj3);
	ot.addbox(obj4);

	using potn = const octree_node< aabbvolume >*;

	potn n1 = ot.matchbox(obj1);
	potn n2 = ot.matchbox(obj2);
	potn n3 = ot.matchbox(obj3);
	potn n4 = ot.matchbox(obj4);

	std::cin.ignore();
	return 0;
}