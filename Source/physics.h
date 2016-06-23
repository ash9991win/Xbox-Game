#pragma once
#include "baseTypes.h"

#ifndef PHYSICS_H
#define PHYSICS_H

#define _USE_MATH_DEFINES
#include <math.h>

#define _USING_3D FALSE
//
const static byte X = 0;
const static byte Y = 1;
const static byte Z = 2;
const static byte W = 3;
enum direction
{
	UP, DOWN, LEFT, RIGHT
};
class Vector2 {
public:
    float32_t x;
    float32_t y;
    
    // Constructors
	Vector2();
	Vector2(float32_t x, float32_t y);
	~Vector2() {}
    
    // Operator overloading
	Vector2& operator= (const Vector2 &rhs);
    Vector2& operator+= (const Vector2 &rhs);   // Add
    const Vector2 operator+ (const Vector2 &other);   // Add
    Vector2& operator-= (const Vector2 &rhs);   // Sub
	const Vector2 operator- (const Vector2 &other);   // Sub
    Vector2& operator*= (const float32_t value);  // Scalar Multiply
	const Vector2 operator* (const float32_t value);  // Scalar Multiply
    Vector2& operator/= (const float32_t value);  // Scalar Divide
	const Vector2 operator/ (const float32_t value);  // Scalar Divide
    bool8_t operator==(const Vector2 &other);    // Equivalency
    bool8_t operator!=(const Vector2 &other);    // Inequivalency
	Vector2 findDiff(Vector2 rhs);
	float32_t& operator[] (int32_t i);
    // Modifier Methods
    Vector2 * copy();
    Vector2 * add(Vector2 *other);
    Vector2 * sub(Vector2 *other);
    Vector2 * mult(float32_t scalar);
    Vector2 * div(float32_t scalar);
    float32_t lengthSquared();
    float32_t length();
    Vector2 * rotateOnOrigin(radianf_t ccw);
    Vector2 * rotateOnPivot(radianf_t ccw, Vector2 *pivot);
	static void  flipTexture(TexCoord *textureToFlip,direction directionToFlip);
//	void      rotateQuad(Quad *quad, float angle,Vector2 pivotPoint);
	Vector2   normalize();
    //Vector2 * projectOnto(Vector2 *vect);
    //Vector2 * projection(Vector2 *project);
    
    static float32_t dotProduct(Vector2 *lhs, Vector2 *rhs);
    static float32_t distanceBetweenSquared(Vector2 *vect1, Vector2 *vect2);
	static float32_t distanceBetweenSquared(Vector2 vect1, Vector2 vect2);

    static float32_t distanceBetween(Vector2 *vect1, Vector2 *vect2);
	static float32_t distanceBetween(Vector2 vect1, Vector2 vect2);

    static float32_t cosineOfAngleBetween(Vector2 *vect1, Vector2 *vect2);
    static float32_t sineOfAngleBetween(Vector2 *vect1, Vector2 *vect2);
    static float32_t angleBetween(Vector2 *vect1, Vector2 *vect2);
	static void  convertImageToScreenCoordinates(Vector2 *point);
	static void  convertScreenToImageCoordinates(Vector2 *point);
	static void  convertScreenToTextureCoordinates(Vector2 *point);
	static void  convertImageToTextureCoordinates(Vector2 *point);
	void   convertToTextureCoordinates(Vector2 *point);
};

struct Circle
{
	Vector2 mCenter;
	float_t radius;
};


#if _USING_3D
// Vector3 Structure
class  Vector3 {
public:
    float32_t x;
    float32_t y;
    float32_t z;
    
	Vector3();
    Vector3(float32_t x, float32_t y, float32_t z);
    ~Vector3() {}

	// Operator overloading
	Vector3& operator= (const Vector3 &rhs);
	Vector3& operator+= (const Vector3 &rhs);   // Add
	const Vector3 operator+ (const Vector3 &other);   // Add
	Vector3& operator-= (const Vector3 &rhs);   // Sub
	const Vector3 operator- (const Vector3 &other);   // Sub
	Vector3& operator*= (const float32_t value);  // Scalar Multiply
	const Vector3 operator* (const float32_t value);  // Scalar Multiply
	Vector3& operator/= (const float32_t value);  // Scalar Divide
	const Vector3 operator/ (const float32_t value);  // Scalar Divide
	bool8_t operator==(const Vector3 &other);    // Equivalency
	bool8_t operator!=(const Vector3 &other);    // Inequivalency
	float32_t& operator[] (int32_t i);
    
    Vector3 * copy();
    Vector3 * add(Vector3 *other);
    Vector3 * sub(Vector3 *other);
    Vector3 * mult(float32_t scalar);
    Vector3 * div(float32_t scalar);
    float32_t lengthSquared();
    float32_t length();
    //Vector3 * rotateOnOrigin(radianf_t ccw);
    //Vector3 * rotateOnPivot(radianf_t ccw, Vector3 *pivot);	// Requires Quaternion

    //Vector3 * projectOnto(Vector3 *vect);
    //Vector3 * projection(Vector3 *project);
    
    static float32_t dotProduct(Vector3 *lhs, Vector3 *rhs);
    static Vector3 * crossProduct(Vector3 *lhs, Vector3 *rhs);
    static float32_t distanceBetweenSquared(Vector3 *vect1, Vector3 *vect2);
    static float32_t distanceBetween(Vector3 *vect1, Vector3 *vect2);
    static float32_t cosineOfAngleBetween(Vector3 *vect1, Vector3 *vect2);
    static float32_t sineOfAngleBetween(Vector3 *vect1, Vector3 *vect2);
    static float32_t angleBetween(Vector3 *vect1, Vector3 *vect2);
};

// Vector4 Structure
struct Vector4 {
public:
    float32_t x;
    float32_t y;
    float32_t z;
    float32_t w;
    
	Vector4();
    Vector4(float32_t x, float32_t y, float32_t z, float32_t w);
    ~Vector4() {}

	// Operator overloading
	Vector4& operator= (const Vector4 &rhs);
	Vector4& operator+= (const Vector4 &rhs);   // Add
	const Vector4 operator+ (const Vector4 &other);   // Add
	Vector4& operator-= (const Vector4 &rhs);   // Sub
	const Vector4 operator- (const Vector4 &other);   // Sub
	Vector4& operator*= (const float32_t value);  // Scalar Multiply
	const Vector4 operator* (const float32_t value);  // Scalar Multiply
	Vector4& operator/= (const float32_t value);  // Scalar Divide
	const Vector4 operator/ (const float32_t value);  // Scalar Divide
	bool8_t operator==(const Vector4 &other);    // Equivalency
	bool8_t operator!=(const Vector4 &other);    // Inequivalency
	float32_t& operator[] (int32_t i);
    
    Vector4 * copy();
    Vector4 * add(Vector4 *other);
    Vector4 * sub(Vector4 *other);
    Vector4 * mult(float32_t scalar);
    Vector4 * div(float32_t scalar);
    float32_t lengthSquared();
    float32_t length();
    
    static float32_t dotProduct(Vector4 *lhs, Vector4 *rhs);
};
#endif
/*
//
struct PhysicsSpace2D{
public:
	Vector2 pos;
	Vector2 vel;
	Vector2 intVel;
	Vector2 acc;
	Vector2 intAcc;
};

struct PhysicsProperties{
public:
	float32_t mass;
	float32_t friction;
	float32_t elasticity;
};

// Different Shapes
class PhysicsCircle;
class PhysicsRect;

// PhysicsEntity2D Prototypes
class PhysicsEntity2D{
public:
	PhysicsSpace2D space;
    radianf_t ccwAngle;
    
    static bool8_t testCollision(PhysicsEntity2D *ent1, PhysicsEntity2D *ent2);
    static bool8_t testCollision(PhysicsCircle *ent1, PhysicsCircle *ent2);
    static bool8_t testCollision(PhysicsCircle *ent1, PhysicsRect *ent2);
    static bool8_t testCollision(PhysicsRect *ent1, PhysicsRect *ent2);
};

float32_t PhysicsEntity2D_UniversalGravitationalForce(PhysicsEntity2D *ent1, PhysicsEntity2D *ent2);


// PhysicsCircle class
class PhysicsCircle : public PhysicsEntity2D{
public:
    float32_t radius;
    
    PhysicsCircle(Vector2 *position, float32_t radius);
    PhysicsCircle(PhysicsSpace2D *space, float32_t radius);
    ~PhysicsCircle();
};

// PhysicsCircle Prototypes
class PhysicsRect : public PhysicsEntity2D{
	PhysicsEntity2D phy;
	float32_t width;
	float32_t height;
    
    PhysicsRect(Vector2 *position, float32_t width, float32_t height, radianf_t ccw);
    PhysicsRect(PhysicsSpace2D *space, float32_t width, float32_t height, radianf_t ccw);
    PhysicsRect(Vector2 *position, Vector2 *width, float32_t height);
    PhysicsRect(PhysicsSpace2D *space, PhysicsProperties *prop, Vector2 *width, float32_t height);
    ~PhysicsRect();
};
*/

#endif