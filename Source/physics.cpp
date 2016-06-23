#include "physics.h"
#include"Constants.h"
/* ==================== Vector 2 Static Methods ===================== */
// Vector2 constructor

Vector2::Vector2() {
	this->x = 0.0f;
	this->y = 0.0f;
}

Vector2::Vector2(float32_t x, float32_t y){
    this->x = x;
    this->y = y;
}

// Overloaded Operations
Vector2& Vector2::operator= (const Vector2 &rhs) {
	if (this != &rhs) {	// Avoid self-assignment!
		this->x = rhs.x;
		this->y = rhs.y;
	}
	return *this;
}
Vector2 Vector2::findDiff(Vector2 rhs)
{
	Vector2 resultVector;
	resultVector.x = x - rhs.x;
	resultVector.y = y - rhs.y;
	return resultVector;
}
Vector2& Vector2::operator+= (const Vector2 &rhs) {
	this->x += rhs.x;
	this->y += rhs.y;
	return *this;
}
Vector2  Vector2::normalize()
{
	Vector2 newVector;
	float32_t len = length();

	newVector.x = x / len;
	newVector.y = y / len;

	return newVector;


}
const Vector2 Vector2::operator+ (const Vector2 &other){
	Vector2 result = *this;     // Make a copy of myself, using assignment
	result += other;            // Use += to add other to the copy.
	return result;              // All done! (Quick Tricks!)
}

Vector2& Vector2::operator-= (const Vector2 &rhs) {
	this->x -= rhs.x;
	this->y -= rhs.y;
	return *this;
}

//const Vector2 Vector2::operator- (const Vector2 &other) {
//	Vector2 result = *this;
//	result -= other;
//	return result;
//}

Vector2& Vector2::operator*= (const float32_t value) {
	this->x *= value;
	this->y *= value;
	return *this;
}

const Vector2 Vector2::operator* (const float32_t value) {
	Vector2 *result = new Vector2(*this);
	*result *= value;
	return *result;
}

Vector2& Vector2::operator/= (const float32_t value) {
	this->x *= value;
	this->y *= value;
	return *this;
}

const Vector2 Vector2::operator/ (const float32_t value) {
	Vector2 *result = new Vector2(*this);
	*result /= value;
	return *result;
}

bool8_t Vector2::operator==(const Vector2 &other) {
	return (this->x == other.x && this->y == other.y);
}

bool8_t Vector2::operator!=(const Vector2 &other) {
	return !(*this == other);
}

float32_t& Vector2::operator[] (int32_t i) {
	switch (i) {
	case X:	return this->x;
	case Y:	return this->y;
	default:
		throw 0;
	}
}

// Make a copy of this instance
Vector2 * Vector2::copy() {
    return new Vector2(this->x, this->y);
}

// Add two vectors
Vector2 * Vector2::add(Vector2 *other) {
    this->x += other->x;
    this->y += other->y;
    return this;
}

// Subtract two vectors
Vector2 * Vector2::sub(Vector2 *other) {
	this->x -= other->x;
	this->y -= other->y;
    return this;
}

// Multiply a value to the vectors
Vector2 * Vector2::mult(float32_t value) {
	this->x *= value;
	this->y *= value;
    return this;
}

// Multiply a value to the vectors
Vector2 * Vector2::div(float32_t value) {
	this->x /= value;
	this->y /= value;
	return this;
}

// Compute the length of the vector, squared
float32_t Vector2::lengthSquared() {
	return this->x * this->x + this->y * this->y;
}

// Compute the length of the vector
float32_t Vector2::length() {
	return sqrt(this->x * this->x + this->y * this->y);
}

// Compute the Dot Product of two vectors
float32_t Vector2::dotProduct(Vector2 *lhs, Vector2 *rhs) {
	return lhs->x * rhs->x + lhs->y * rhs->y;
}

// The distance between vectors 1 and 2, squared
float32_t Vector2::distanceBetweenSquared(Vector2 *vect1, Vector2 *vect2) {
	float_t distX = vect1->x - vect2->x;
	float_t distY = vect1->y - vect2->y;
	return distX * distX + distY * distY;
}
float32_t Vector2::distanceBetweenSquared(Vector2 vect1, Vector2 vect2) {
	float_t distX = vect1.x - vect2.x;
	float_t distY = vect1.y - vect2.y;
	return distX * distX + distY * distY;
}
// The distance between vectors 1 and 2
float32_t Vector2::distanceBetween(Vector2 *vect1, Vector2 *vect2) {
	float_t distX = vect1->x - vect2->x;
	float_t distY = vect1->y - vect2->y;
	return sqrtf(distX * distX + distY * distY);
}
float32_t Vector2::distanceBetween(Vector2 vect1, Vector2 vect2) {
	float_t distX = vect1.x - vect2.x;
	float_t distY = vect1.y - vect2.y;
	return sqrtf(distX * distX + distY * distY);
}
// Compute the cosine of the angle between vectors 1 and 2
float32_t Vector2::cosineOfAngleBetween(Vector2 *vect1, Vector2 *vect2) {
	float32_t dotproduct = vect1->x * vect2->x + vect1->y * vect2->y;
	float32_t den = (vect1->x * vect1->x + vect1->y * vect1->y)*(vect1->x * vect1->x + vect1->y * vect1->y);
	return dotproduct / sqrtf(den);
}

// Compute the sine of the angle between vectors 1 and 2
float32_t Vector2::sineOfAngleBetween(Vector2 *vect1, Vector2 *vect2) {
	float32_t lengthofcrossproduct = vect1->x * vect2->y - vect1->y * vect2->x;
	float32_t den = (vect1->x * vect1->x + vect1->y * vect1->y)*(vect1->x * vect1->x + vect1->y * vect1->y);
	return lengthofcrossproduct / sqrtf(den);
}

// Compute the angle between vectors 1 and 2, in radians
radianf_t Vector2::angleBetween(Vector2 *vect1, Vector2 *vect2) {
	float32_t num = vect1->x * vect2->y + vect1->y * vect2->x;
	float32_t den = (vect1->x * vect1->x + vect1->y * vect1->y)*(vect1->x * vect1->x + vect1->y * vect1->y);
	return (radianf_t) acosf(num / sqrtf(den));
}

// Rotate the vector for a given radian angle in counter-clockwise direction
Vector2 * Vector2::rotateOnOrigin(radianf_t ccw) {
	float32_t tempCos = cosf(ccw);
	float32_t tempSin = cosf(ccw);
	this->x = this->x * tempCos + this->y * tempSin;
	this->y = this->y * tempCos - this->x * tempSin;
    return this;
}

// Rotate the vector on a pivot for a given radian angle in counter-clockwise direction
Vector2 * Vector2::rotateOnPivot(radianf_t ccw, Vector2 *pivot) {
	float32_t tempCos = cosf(ccw);
	float32_t tempSin = sinf(ccw);
	float32_t tempX;
	float32_t tempY;
	this->x -= pivot->x;
	this->y -= pivot->y;
	tempX = this->x * tempCos + this->y * tempSin;
	tempY = this->y * tempCos - this->x * tempSin;
	this->x = tempX;
	this->y = tempY;
	this->x += pivot->x;
	this->y += pivot->y;
    return this;
}

void  Vector2::convertScreenToImageCoordinates(Vector2 *point)
{
	if (point->x >= 0)
	{
		point->x *= SCREEN_TO_IMAGE_X;
	}
	else
	{
		point->x = 0;
	
	}
	if (point->y >= 0)
	{
		point->y *= SCREEN_TO_IMAGE_Y;
	}
	else
	{
		point->y = 0;


	}
}
void Vector2::convertScreenToTextureCoordinates(Vector2 *point)
{
	point->x =  abs(point->x / IMAGE_WIDTH);
	point->y = abs(point->y / IMAGE_HEIGHT);
	if (point->x > 1)
	{
		point->x = 0;
	}
	if (point->y > 1)
	{
		point->y = 0;
	}
}
void Vector2::flipTexture(TexCoord *input, direction flipDir)
{
	if (flipDir == RIGHT)
	{
		input->x = input->x + input->width;
		input->y = input->y ;
		input->width = -input->width;
	

	}
	else if (flipDir == LEFT)
	{
	}
	else if (flipDir == UP)
	{
	}
	else if (flipDir == DOWN)
	{
		input->y = input->y + input->height;
		input->height = -input->height;
		input->x = input->x + input->width;
		input->width = -input->width;
	}
}
void  Vector2::convertImageToScreenCoordinates(Vector2 *point)
{
	point->x *= IMAGE_TO_SCREEN_X;
	point->y *= IMAGE_TO_SCREEN_Y;
}


#if _USING_3D
/* ==================== Vector 3 Static Methods ===================== */
// Vector3 constructor
Vector3::Vector3() {
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

Vector3::Vector3(float32_t x, float32_t y, float32_t z){
    this->x = x;
    this->y = y;
    this->z = z;
}

// Overloaded Operations
Vector3& Vector3::operator= (const Vector3 &rhs) {
	if (this != &rhs) {	// Avoid self-assignment!
		this->x = rhs.x;
		this->y = rhs.y;
		this->z = rhs.z;
	}
	return *this;
}

Vector3& Vector3::operator+= (const Vector3 &rhs) {
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;
	return *this;
}

const Vector3 Vector3::operator+ (const Vector3 &other) {
	Vector3 result = *this;     // Make a copy of myself, using assignment
	result += other;            // Use += to add other to the copy.
	return result;              // All done! (Quick Tricks!)
}

Vector3& Vector3::operator-= (const Vector3 &rhs) {
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;
	return *this;
}

const Vector3 Vector3::operator- (const Vector3 &other) {
	Vector3 result = *this;
	result -= other;
	return result;
}

Vector3& Vector3::operator*= (const float32_t value) {
	this->x *= value;
	this->y *= value;
	this->z *= value;
	return *this;
}

const Vector3 Vector3::operator* (const float32_t value) {
	Vector3 result = *this;
	result *= value;
	return result;
}

Vector3& Vector3::operator/= (const float32_t value) {
	this->x /= value;
	this->y /= value;
	this->z /= value;
	return *this;
}

const Vector3 Vector3::operator/ (const float32_t value) {
	Vector3 result = *this;
	result /= value;
	return result;
}

bool8_t Vector3::operator==(const Vector3 &other) {
	return (this->x == other.x && this->y == other.y && this->z == other.z);
}

bool8_t Vector3::operator!=(const Vector3 &other) {
	return !(*this == other);
}

float32_t& Vector3::operator[] (int32_t i) {
	switch (i) {
	case X:	return this->x;
	case Y:	return this->y;
	case Z:	return this->z;
	default:
		throw 0;
	}
}

// Make a copy of this instance
Vector3 * Vector3::copy() {
    return new Vector3(this->x, this->y, this->z);
}

// Add two vectors
Vector3 * Vector3::add(Vector3 *other) {
    this->x += other->x;
    this->y += other->y;
    this->z += other->z;
    return this;
}

// Subtract two vectors
Vector3 * Vector3::sub(Vector3 *other) {
    this->x -= other->x;
    this->y -= other->y;
    this->z -= other->z;
    return this;
}

// Multiply a value to the vectors
Vector3 * Vector3::mult(float32_t value) {
    this->x *= value;
    this->y *= value;
    this->z *= value;
    return this;
}

// Multiply a value to the vectors
Vector3 * Vector3::div(float32_t value) {
	this->x /= value;
	this->y /= value;
	this->z /= value;
	return this;
}

// Compute the length of the vector, squared
float32_t Vector3::lengthSquared() {
	return this->x * this->x + this->y * this->y + this->z * this->z;
}

// Compute the length of the vector
float32_t Vector3::length() {
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

// Compute the Dot Product of two vectors and return the result in "output"
float32_t Vector3::dotProduct(Vector3 *lhs, Vector3 *rhs) {
	return lhs->x * rhs->x + lhs->y * rhs->y + lhs->z * rhs->z;
}

// Subtract two vectors
Vector3 * Vector3::crossProduct(Vector3 *lhs, Vector3 *rhs) {
    return new Vector3(lhs->y * rhs->z - lhs->z * rhs->y,
                       lhs->x * rhs->z - lhs->z * rhs->x,
                       lhs->x * rhs->y - lhs->y * rhs->x);
}

// The distance between vectors 1 and 2, squared
float32_t Vector3::distanceBetweenSquared(Vector3 *vect1, Vector3 *vect2) {
	float_t distX = vect1->x - vect2->x;
	float_t distY = vect1->y - vect2->y;
	float_t distZ = vect1->z - vect2->z;
	return distX * distX + distY * distY + distZ * distZ;
}

// The distance between vectors 1 and 2
float32_t Vector3::distanceBetween(Vector3 *vect1, Vector3 *vect2) {
	float_t distX = vect1->x - vect2->x;
	float_t distY = vect1->y - vect2->y;
	float_t distZ = vect1->z - vect2->z;
	return sqrtf(distX * distX + distY * distY + distZ * distZ);
}

// Compute the cosine of the angle between vectors 1 and 2
float32_t Vector3::cosineOfAngleBetween(Vector3 *vect1, Vector3 *vect2) {
	float32_t dotproduct = vect1->x * vect2->x + vect1->y * vect2->z + vect1->z * vect2->z;
	float32_t den = (vect1->x * vect1->x + vect1->y * vect1->y + vect1->z * vect1->z)*(vect1->x * vect1->x + vect1->y * vect1->y + vect1->z * vect1->z);
	return dotproduct / sqrtf(den);
}

// Compute the sine of the angle between vectors 1 and 2 (6 more multiplies than cosine)
float32_t Vector3::sineOfAngleBetween(Vector3 *vect1, Vector3 *vect2) {
	Vector3 crossproduct = {
		vect1->y * vect2->z - vect1->z * vect2->y,
		vect1->x * vect2->z - vect1->z * vect2->x,
		vect1->x * vect2->y - vect1->y * vect2->x
	};
	float32_t num = crossproduct.x * crossproduct.x + crossproduct.y * crossproduct.y + crossproduct.z * crossproduct.z;
	float32_t den = (vect1->x * vect1->x + vect1->y * vect1->y + vect1->z * vect1->z)*(vect1->x * vect1->x + vect1->y * vect1->y + vect1->z * vect1->z);
	return sqrtf(num / den);
}

// Compute the angle between vectors 1 and 2, in radians
radianf_t Vector3::angleBetween(Vector3 *vect1, Vector3 *vect2) {
	float32_t dotproduct = vect1->x * vect2->x + vect1->y * vect2->z + vect1->z * vect2->z;
	float32_t den = (vect1->x * vect1->x + vect1->y * vect1->y + vect1->z * vect1->z)*(vect1->x * vect1->x + vect1->y * vect1->y + vect1->z * vect1->z);
	return (radianf_t) acosf(dotproduct / sqrt(den));
}


/* ==================== Vector 4 Static Methods ===================== */
// Vector3 constructor
Vector4::Vector4() {
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	this->w = 0.0f;
}

Vector4::Vector4(float32_t x, float32_t y, float32_t z, float32_t w){
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

// Overloaded Operations
Vector4& Vector4::operator= (const Vector4 &rhs) {
	if (this != &rhs) {	// Avoid self-assignment!
		this->x = rhs.x;
		this->y = rhs.y;
		this->z = rhs.z;
		this->w = rhs.w;
	}
	return *this;
}

Vector4& Vector4::operator+= (const Vector4 &rhs) {
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;
	this->w += rhs.w;
	return *this;
}

const Vector4 Vector4::operator+ (const Vector4 &other) {
	Vector4 result = *this;     // Make a copy of myself, using assignment
	result += other;            // Use += to add other to the copy.
	return result;              // All done! (Quick Tricks!)
}

Vector4& Vector4::operator-= (const Vector4 &rhs) {
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;
	this->w -= rhs.w;
	return *this;
}

const Vector4 Vector4::operator- (const Vector4 &other) {
	Vector4 result = *this;
	result -= other;
	return result;
}

Vector4& Vector4::operator*= (const float32_t value) {
	this->x *= value;
	this->y *= value;
	this->z *= value;
	this->w *= value;
	return *this;
}

const Vector4 Vector4::operator* (const float32_t value) {
	Vector4 result = *this;
	result *= value;
	return result;
}

Vector4& Vector4::operator/= (const float32_t value) {
	this->x /= value;
	this->y /= value;
	this->z /= value;
	this->w /= value;
	return *this;
}

const Vector4 Vector4::operator/ (const float32_t value) {
	Vector4 result = *this;
	result /= value;
	return result;
}

bool8_t Vector4::operator==(const Vector4 &other) {
	return (this->x == other.x && this->y == other.y && this->z == other.z);
}

bool8_t Vector4::operator!=(const Vector4 &other) {
	return !(*this == other);
}

float32_t& Vector4::operator[] (int32_t i) {
	switch (i) {
	case X:	return this->x;
	case Y:	return this->y;
	case Z:	return this->z;
	case W:	return this->w;
	default:
		throw 0;
	}
}

// Make a copy of the instance
Vector4* Vector4::copy() {
	return new Vector4(this->x, this->y, this->z, this->w);
}

// Add two vectors
Vector4 * Vector4::add(Vector4 *other) {
    this->x += other->x;
    this->y += other->y;
    this->z += other->z;
    this->w += other->w;
    return this;
}

// Subtract two vectors
Vector4 * Vector4::sub(Vector4 *other) {
    this->x -= other->x;
    this->y -= other->y;
    this->z -= other->z;
    this->w -= other->w;
    return this;
}

// Multiply a value to the vectors
Vector4 * Vector4::mult(float32_t value) {
    this->x *= value;
    this->y *= value;
    this->z *= value;
    this->w *= value;
    return this;
}

// Multiply a value to the vectors
Vector4 * Vector4::div(float32_t value) {
    this->x /= value;
    this->y /= value;
    this->z /= value;
    this->w /= value;
    return this;
}

// Compute the Dot Product of two vectors
float32_t Vector4::dotProduct(Vector4 *lhs, Vector4 *rhs) {
	return lhs->x * rhs->x + lhs->y * rhs->y + lhs->z * rhs->z + lhs->w * rhs->w;
}

// Compute the length of the vector, squared
float32_t Vector4::lengthSquared() {
	return this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w;
}

// Compute the length of the vector
float32_t Vector4::length() {
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
}
#endif

/* ==================== PhysicsEntity2D Static Methods ===================== */
/*
// Apply Universal Gravitation Formula (a = F / m1 = (G * m2) / d^2  where G = Gravitational Constant)
float32_t PhysicsEntity2D_UniversalGravitationalAcceleration(PhysicsEntity2D *ent1, PhysicsEntity2D *ent2, float32_t G) {
	float32_t num = G * ent2->prop.mass;
	float32_t den = Vector2_DistanceBetweenSquared(&(ent1->space.pos), &(ent2->space.pos));
	return fabsf(num / den);
}

bool8_t PhysicsEntity2D_TestCollision(PhysicsEntity2D *ent1, PhysicsEntity2D *ent2) {
	if (ent1->type == ent2->type) {
		if (ent1->type == PHY2D_CIRCLE) {
			return PhysicsEntity2D_TestCollision((PhysicsCircle *)ent1, (PhysicsCircle *)ent2);
		} else if (ent1->type == PHY2D_RECT) {
			return PhysicsEntity2D_TestCollision((PhysicsRect *)ent1, (PhysicsRect *)ent2);
		}
	} else {
		if (ent1->type == PHY2D_CIRCLE) {
			if (ent2->type == PHY2D_RECT)
				return PhysicsEntity2D_TestCollision((PhysicsCircle *)ent1, (PhysicsRect *)ent2);
		} else if (ent1->type == PHY2D_RECT) {
			if (ent2->type == PHY2D_CIRCLE)
				return PhysicsEntity2D_TestCollision((PhysicsCircle *)ent2, (PhysicsRect *)ent2);
		}
	}
	return FALSE;
}

bool8_t PhysicsEntity2D_TestCollision_CC(PhysicsCircle *circle1, PhysicsCircle *circle2) {
	float32_t distSquared = Vector2_DistanceBetweenSquared(&(circle1->phy.space.pos), &(circle2->phy.space.pos));
	float32_t min_dist = (circle1->radius + circle2->radius);
	return min_dist * min_dist > distSquared;
}

bool8_t PhysicsEntity2D_TestCollision_CR(PhysicsCircle *circle, PhysicsRect *rect) {
	// Rotate to orientation (relative to rectangle)
	Vector2 circlePos;
	Vector2_Copy(&circlePos, &(circle->phy.space.pos));
	Vector2 rectPos = rect->phy.space.pos;
	Vector2_RotateOnPivot(&circlePos, rect->ccwAngle, &rectPos);
	// Test if within bounding-box
	float32_t rectCircleXDiff = circlePos.x - rectPos.x;
	float32_t rectCircleYDiff = circlePos.y - rectPos.y;
	float32_t rectCircleWidthDiff = (rect->width / 2) + circle->radius;
	float32_t rectCircleHeightDiff = (rect->height / 2) + circle->radius;
	bool8_t answer = FALSE;
	if (rectCircleXDiff <= rectCircleWidthDiff && rectCircleXDiff >= -rectCircleWidthDiff
	&& rectCircleYDiff <= rectCircleHeightDiff && rectCircleYDiff >= -rectCircleHeightDiff) {
		answer = TRUE;
	}
	// Return results
	return answer;
}

bool8_t PhysicsEntity2D_TestCollision_RR(PhysicsRect ent1, PhysicsRect ent2) {
	return FALSE;
}
*/
