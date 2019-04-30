#pragma once

typedef float vec_t;
// 2D Vector
class vector2d
{
public:
	// Members
	vec_t x, y;

	// Construction/destruction:
	vector2d(void);
	vector2d(vec_t X, vec_t Y);
	vector2d(vec_t* clr);

	vector2d::vector2d(const vector2d &vOther)
	{
		x = vOther.x; y = vOther.y;
	}

	// Initialization
	void Init(vec_t ix = 0.0f, vec_t iy = 0.0f);
	// TODO (Ilya): Should there be an init that takes a single float for consistency?

	// Got any nasty NAN's?
	bool IsValid() const;
	void Invalidate();

	// array access...
	vec_t operator[](int i) const;
	vec_t& operator[](int i);

	// Base address...
	vec_t* Base();
	vec_t const* Base() const;

	// Initialization methods
	void Random(vec_t minVal, vec_t maxVal);
	void Zero(); ///< zero out a vector

				 // equality
	bool operator==(const vector2d& v) const;
	bool operator!=(const vector2d& v) const;

	// arithmetic operations
	vector2d& operator+=(const vector2d& v)
	{
		x += v.x; y += v.y;
		return *this;
	}

	vector2d& operator-=(const vector2d& v)
	{
		x -= v.x; y -= v.y;
		return *this;
	}

	vector2d& operator*=(float fl)
	{
		x *= fl;
		y *= fl;
		return *this;
	}

	vector2d& operator*=(const vector2d& v)
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}

	vector2d& operator/=(const vector2d& v)
	{
		x /= v.x;
		y /= v.y;
		return *this;
	}

	// this ought to be an opcode.
	vector2d& operator+=(float fl)
	{
		x += fl;
		y += fl;
		return *this;
	}

	// this ought to be an opcode.
	vector2d& operator/=(float fl)
	{
		x /= fl;
		y /= fl;
		return *this;
	}
	vector2d& operator-=(float fl)
	{
		x -= fl;
		y -= fl;
		return *this;
	}

	// negate the vector components
	void Negate();

	// Get the vector's magnitude.
	vec_t Length() const;

	// Get the vector's magnitude squared.
	vec_t LengthSqr(void) const
	{
		return (x*x + y * y);
	}

	// return true if this vector is (0,0,0) within tolerance
	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance);
	}

	vec_t NormalizeInPlace();
	vector2d Normalized() const;
	bool IsLengthGreaterThan(float val) const;
	bool IsLengthLessThan(float val) const;

	// check if a vector is within the box defined by two other vectors
	bool WithinAABox(vector2d const &boxmin, vector2d const &boxmax);

	// Get the distance from this vector to the other one.
	vec_t DistTo(const vector2d &vOther) const;

	// Get the distance from this vector to the other one squared.
	// NJS: note, VC wasn't inlining it correctly in several deeply nested inlines due to being an 'out of line' .  
	// may be able to tidy this up after switching to VC7
	vec_t DistToSqr(const vector2d &vOther) const
	{
		vector2d delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;

		return delta.LengthSqr();
	}

	// Copy
	void CopyToArray(float* rgfl) const;

	// Multiply, add, and assign to this (ie: *this = a + b * scalar). This
	// is about 12% faster than the actual vector equation (because it's done per-component
	// rather than per-vector).
	void MulAdd(const vector2d& a, const vector2d& b, float scalar);

	// Dot product.
	vec_t Dot(const vector2d& vOther) const;

	// assignment
	vector2d& operator=(const vector2d &vOther);

	// 2d
	vec_t Length2D(void) const;
	vec_t Length2DSqr(void) const;

	/// Get the component of this vector parallel to some other given vector
	vector2d  ProjectOnto(const vector2d& onto);

	// copy constructors
	// vector2d(const vector2d &vOther);

	// arithmetic operations
	vector2d operator-(void) const;

	vector2d operator+(const vector2d& v) const;
	vector2d operator-(const vector2d& v) const;
	vector2d operator*(const vector2d& v) const;
	vector2d operator/(const vector2d& v) const;
	vector2d operator*(float fl) const;
	vector2d operator/(float fl) const;

	// Cross product between two vectors.
	vector2d Cross(const vector2d &vOther) const;

	// Returns a vector with the min or max in X, Y, and Z.
	vector2d Min(const vector2d &vOther) const;
	vector2d Max(const vector2d &vOther) const;
};