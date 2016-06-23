#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines

#include "baseTypes.h"

#if IS_COMP
#include <windows.h>											// Header File For Windows
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include <gl\glut.h>
#include "openglframework.h"
#include "openGLStuff.h"
#endif

#include "random.h"
#include "InputManager.h"
#include "BackgroundManager.h"
#include "PlayerManager.h"
#include "DiscManagerC.h"
#include "LevelLoader.h"

typedef enum {
	INVALID_GAME_STATE = -1,
	MENU_STATE = 0,
	LOAD_GAME_STATE,
	PLAY_STATE,
	GAMEOVER_STATE,
	GAMEWON_STATE,
	LOAD_LEVEL_STATE,
	NUM_OF_GAME_STATES
}GAME_STATE;

class CGame
{
public:
	const char8_t *GetGameTitle(){return mGameTitle;}
	static CGame	*CreateInstance();
	static CGame	*GetInstance() {return sInstance;};
	~CGame();
	void DrawScene();
	void UpdateFrame(DWORD milliseconds);
	void DestroyGame();
	void init();
	void shutdown();
	void checkForCollision();
	void checkForInput();
	static const uint32_t	mScreenWidth = 1024;
	static const uint32_t	mScreenHeight = 768;
	static const uint32_t	mBitsPerPixel = 32;
	 DWORD gameover_duration ;
	DWORD gameover_timer;
private:
	static const char8_t	mGameTitle[20];
	static CGame			*sInstance;
	GAME_STATE				currentState;
	int currentLevel;

	CGame(){};
};
