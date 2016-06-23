#pragma once
#ifndef  DISC_MANAGER
#define DISC_MANAGER
#include "baseTypes.h"	//New for XBox

#include"physics.h"
#include"LinkedList.h"
#include"tinyxml.h"
#include"Renderer.h"
//#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations

#if IS_COMP
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library

#include <gl\glut.h>
#endif

#include"random.h"
#include"Constants.h"
const int JUMPABLE_DISC = 0x00;
const int ENEMY_DISC = 0x01;
const int MEGA_JUMP = 0x02;
const int TELEPORT_DISC = 0x03;
const int TNT_DISC = 0x04;

class Discs
{
public:

	int discType;
	Vector2 position;
	Vector2 center;
	Vector2 smilePosition;
	Vector2 eyePosition;
	Vector2 spokePosition;
	float speed;
	float radius;
	float spokeRadius;
	float smileWidth;
	float smileHeight;
	float eyeWidth;
	float eyeHeight;
	float currentAngle;
	bool direction;
	bool isVisible;
	bool canSeePlayer;
	bool isVisited;
	TexCoord eyeCoordinates;
	TexCoord smileCoordinates;
	TexCoord discCoordinates;
	TexCoord spokeCoordinates;
	Circle   collider;
};
class DiscManagerC
{
public:
	static DiscManagerC* createInstance();
	static DiscManagerC* getInstance();
	Vector2  getPosition();
	//float    getRotationSpeed();
	float    getRadius();
	Vector2  getCenter();
	bool     getDirection();
	void init();
	~DiscManagerC();
	void     update(DWORD currentTime);
	//TexCoord getRandomDiscCoordinates();
	void     render();
	void     rotateDiscs(DWORD deltaTime);
	

	ListIterator<Discs*>* getDiscs();
	LinkedList<Discs*>*   getDiscList();
	void loadLevelData();
private:
	DiscManagerC();
	static DiscManagerC* sInstance;
	Vector2 mPosition;
	float   mRotationSpeed;
	float mRadius;
	Vector2 mCenter;
	bool    mDirection;
	LinkedList<Discs*> *discList;
	ListIterator<Discs*> *discIterator;
	float    mAngle;
	float    startTime;
	float    currentTime;
	TiXmlDocument coordinateDocument;
	Renderer *renderer;
	float    minDistance;
	bool     firstDisc;
	float    randomIterator;
	float    lastRadius;
};
#endif
