#ifndef BASETYPES_H
#define BASETYPES_H

typedef float float_t;
typedef char char8_t;
typedef short int16_t;
typedef int int32_t;


typedef unsigned char uchar8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef char* string;
typedef uchar8_t byte;
typedef uchar8_t bool8_t;
typedef uchar8_t bool8_t;
typedef uint16_t bool16_t;
typedef uint32_t bool32_t;

typedef float_t float32_t;
typedef float_t radianf_t;
typedef float_t degreef_t;

#define FALSE	0
#define TRUE	1

#define IS_XBOX	FALSE
#define IS_COMP	TRUE

 typedef struct
{
	float_t x;
	float_t y;
	float_t width;
	float_t height;
}FixedRect;


 typedef struct Quadilateral
 {
	 float x;
	 float y;
	 float height;
	 float width;
	 float angle;
 } Rect;

 typedef FixedRect TexCoord;
 typedef FixedRect TextureCoordinates;


#if IS_COMP
#include<Windows.h>
#else
#include <xtl.h>
#endif
#endif
