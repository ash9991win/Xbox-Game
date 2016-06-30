#pragma once
#include"Renderer.h"
class MainMenuManagerC
{
public:
	static MainMenuManagerC* getInstance() {
		if (sInstance == nullptr)
			sInstance = new MainMenuManagerC();
		return sInstance; };
	void init();
	void render();
	
private:
	static MainMenuManagerC* sInstance;
	MainMenuManagerC() {};
	Renderer *menurenderer;
};