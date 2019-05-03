#pragma once




class spoint
{
public:
	int x, y;
	constexpr spoint() : x(0), y(0) {}
	constexpr spoint(int posx, int posy) : x(posx), y(posy) {}
	constexpr spoint(const spoint &pt) = default;


	constexpr bool operator==(const spoint& rhs) const
	{
		if (this->x != rhs.x) return false;
		if (this->y != rhs.y) return false;
		return true;
	}

	constexpr bool operator!=(const spoint& rhs) const
	{
		return !(rhs == *this);
	}

	constexpr spoint& operator +=(const spoint& p2)
	{
		this->x += p2.x;
		this->y += p2.y;
		return *this;
	}

	constexpr spoint& operator -=(const spoint& p2)
	{
		this->x -= p2.x;
		this->y -= p2.y;
		return *this;
	}

	constexpr spoint operator +(const spoint& point) const
	{
		auto tmp = *this;
		return tmp += point;
	}

	constexpr spoint operator -(const spoint& point) const
	{
		auto tmp = *this;
		return tmp -= point;
	}

	constexpr spoint operator +(const int& val) const
	{
		spoint tmp = *this;
		tmp.x += val;
		tmp.y += val;
		return tmp;
	}

	constexpr spoint operator -(const int& val) const
	{
		spoint tmp = *this;
		tmp.x -= val;
		tmp.y -= val;
		return tmp;
	}

	constexpr spoint operator *(const int& val) const
	{
		spoint tmp = *this;
		tmp.x *= val;
		tmp.y *= val;
		return tmp;
	}

	constexpr spoint operator *(const float& val) const
	{
		spoint tmp = *this;
		auto x = float(tmp.x),
			y = float(tmp.y);
		x *= val;
		y *= val;
		tmp.x = roundfloat(x);
		tmp.y = roundfloat(y);
		return tmp;
	}
private:

	/* no constexpr in cmath yet */
	constexpr int roundfloat(const float sx) const { return int(sx >= 0 ? x + 0.5f : x - 0.5f); }
};