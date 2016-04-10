#pragma once
#include"Renderer.h"
class MainMenuManagerC
{
public:
	static MainMenuManagerC* getInstance() { return sInstance; };
	static MainMenuManagerC* createInstance();
	bool hasPlayBeenSelected();
	void init();
	void render();
	
private:
	static MainMenuManagerC* sInstance;
	MainMenuManagerC() {};
	Renderer *menurenderer;
};