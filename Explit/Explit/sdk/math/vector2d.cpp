#include <cmath>

#include "vector2d.hpp"

vector2d::vector2d(void)
{
}

vector2d::vector2d(vec_t X, vec_t Y)
{
	x = X; y = Y;
}

vector2d::vector2d(vec_t* clr)
{
	x = clr[0]; y = clr[1];
}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------

void vector2d::Init(vec_t ix, vec_t iy)
{
	x = ix; y = iy;
}

void vector2d::Random(float minVal, float maxVal)
{
	x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
}

void vector2dClear(vector2d& a)
{
	a.x = a.y = 0.0f;
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------

vector2d& vector2d::operator=(const vector2d &vOther)
{
	x = vOther.x; y = vOther.y;
	return *this;
}

//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------

vec_t& vector2d::operator[](int i)
{
	return ((vec_t*)this)[i];
}

vec_t vector2d::operator[](int i) const
{
	return ((vec_t*)this)[i];
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------

vec_t* vector2d::Base()
{
	return (vec_t*)this;
}

vec_t const* vector2d::Base() const
{
	return (vec_t const*)this;
}

//-----------------------------------------------------------------------------
// IsValid?
//-----------------------------------------------------------------------------

bool vector2d::IsValid() const
{
	return !isinf(x) && !isinf(y);
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------

bool vector2d::operator==(const vector2d& src) const
{
	return (src.x == x) && (src.y == y);
}

bool vector2d::operator!=(const vector2d& src) const
{
	return (src.x != x) || (src.y != y);
}


//-----------------------------------------------------------------------------
// Copy
//-----------------------------------------------------------------------------

void vector2dCopy(const vector2d& src, vector2d& dst)
{
	dst.x = src.x;
	dst.y = src.y;
}

void vector2d::CopyToArray(float* rgfl) const
{
	rgfl[0] = x; rgfl[1] = y;
}

//-----------------------------------------------------------------------------
// standard Math operations
//-----------------------------------------------------------------------------

void vector2d::Negate()
{
	x = -x; y = -y;
}

void vector2dAdd(const vector2d& a, const vector2d& b, vector2d& c)
{
	c.x = a.x + b.x;
	c.y = a.y + b.y;
}

void vector2dSubtract(const vector2d& a, const vector2d& b, vector2d& c)
{
	c.x = a.x - b.x;
	c.y = a.y - b.y;
}

void vector2dMultiply(const vector2d& a, vec_t b, vector2d& c)
{
	c.x = a.x * b;
	c.y = a.y * b;
}

void vector2dMultiply(const vector2d& a, const vector2d& b, vector2d& c)
{
	c.x = a.x * b.x;
	c.y = a.y * b.y;
}


void vector2dDivide(const vector2d& a, vec_t b, vector2d& c)
{
	vec_t oob = 1.0f / b;
	c.x = a.x * oob;
	c.y = a.y * oob;
}

void vector2dDivide(const vector2d& a, const vector2d& b, vector2d& c)
{
	c.x = a.x / b.x;
	c.y = a.y / b.y;
}

void vector2dMA(const vector2d& start, float s, const vector2d& dir, vector2d& result)
{
	result.x = start.x + s * dir.x;
	result.y = start.y + s * dir.y;
}

// FIXME: Remove
// For backwards compatability
void vector2d::MulAdd(const vector2d& a, const vector2d& b, float scalar)
{
	x = a.x + b.x * scalar;
	y = a.y + b.y * scalar;
}

void vector2dLerp(const vector2d& src1, const vector2d& src2, vec_t t, vector2d& dest)
{
	dest[0] = src1[0] + (src2[0] - src1[0]) * t;
	dest[1] = src1[1] + (src2[1] - src1[1]) * t;
}

//-----------------------------------------------------------------------------
// dot, cross
//-----------------------------------------------------------------------------
vec_t DotProduct2D(const vector2d& a, const vector2d& b)
{
	return(a.x*b.x + a.y*b.y);
}

// for backwards compatability
vec_t vector2d::Dot(const vector2d& vOther) const
{
	return DotProduct2D(*this, vOther);
}

vec_t vector2dNormalize(vector2d& v)
{
	vec_t l = v.Length();
	if (l != 0.0f) {
		v /= l;
	}
	else {
		v.x = v.y = 0.0f;
	}
	return l;
}

//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------
vec_t vector2dLength(const vector2d& v)
{
	return (vec_t)sqrt(v.x*v.x + v.y*v.y);
}

vec_t vector2d::NormalizeInPlace()
{
	return vector2dNormalize(*this);
}

bool vector2d::IsLengthGreaterThan(float val) const
{
	return LengthSqr() > val*val;
}

bool vector2d::IsLengthLessThan(float val) const
{
	return LengthSqr() < val*val;
}

vec_t vector2d::Length(void) const
{
	return vector2dLength(*this);
}


void vector2dMin(const vector2d &a, const vector2d &b, vector2d &result)
{
	result.x = (a.x < b.x) ? a.x : b.x;
	result.y = (a.y < b.y) ? a.y : b.y;
}


void vector2dMax(const vector2d &a, const vector2d &b, vector2d &result)
{
	result.x = (a.x > b.x) ? a.x : b.x;
	result.y = (a.y > b.y) ? a.y : b.y;
}

//-----------------------------------------------------------------------------
// Computes the closest point to vecTarget no farther than flMaxDist from vecStart
//-----------------------------------------------------------------------------
void ComputeClosestPoint2D(const vector2d& vecStart, float flMaxDist, const vector2d& vecTarget, vector2d *pResult)
{
	vector2d vecDelta;
	vector2dSubtract(vecTarget, vecStart, vecDelta);
	float flDistSqr = vecDelta.LengthSqr();
	if (flDistSqr <= flMaxDist * flMaxDist) {
		*pResult = vecTarget;
	}
	else {
		vecDelta /= sqrt(flDistSqr);
		vector2dMA(vecStart, flMaxDist, vecDelta, *pResult);
	}
}

//-----------------------------------------------------------------------------
// Returns a vector2d with the min or max in X, Y, and Z.
//-----------------------------------------------------------------------------

vector2d vector2d::Min(const vector2d &vOther) const
{
	return vector2d(x < vOther.x ? x : vOther.x, y < vOther.y ? y : vOther.y);
}

vector2d vector2d::Max(const vector2d &vOther) const
{
	return vector2d(x > vOther.x ? x : vOther.x, y > vOther.y ? y : vOther.y);
}


//-----------------------------------------------------------------------------
// arithmetic operations
//-----------------------------------------------------------------------------

vector2d vector2d::operator-(void) const
{
	return vector2d(-x, -y);
}

vector2d vector2d::operator+(const vector2d& v) const
{
	vector2d res;
	vector2dAdd(*this, v, res);
	return res;
}

vector2d vector2d::operator-(const vector2d& v) const
{
	vector2d res;
	vector2dSubtract(*this, v, res);
	return res;
}

vector2d vector2d::operator*(float fl) const
{
	vector2d res;
	vector2dMultiply(*this, fl, res);
	return res;
}

vector2d vector2d::operator*(const vector2d& v) const
{
	vector2d res;
	vector2dMultiply(*this, v, res);
	return res;
}

vector2d vector2d::operator/(float fl) const
{
	vector2d res;
	vector2dDivide(*this, fl, res);
	return res;
}

vector2d vector2d::operator/(const vector2d& v) const
{
	vector2d res;
	vector2dDivide(*this, v, res);
	return res;
}

vector2d operator*(float fl, const vector2d& v)
{
	return v * fl;
}