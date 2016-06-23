#pragma once
#include <stdlib.h>
#include "baseTypes.h"
//#include<gl/glut.h>

#if IS_COMP
#include <Windows.h>

#else
#include <xtl.h>
#endif

#include"Constants.h"
class CameraManagerC
{
public:
	static CameraManagerC* createInstance();
	static CameraManagerC* getInstance();
	void   Init();
	//void   Update(DWORD ms);
	 void   render();
	void   update(DWORD newMS);
	void getCameraPosition(Vector2 &position);
	void getCameraSize(Vector2 &size);
	
private:
	static CameraManagerC* sInstance;
	CameraManagerC() {};
	Vector2 mPosition;
	float width;
	float height;
};
