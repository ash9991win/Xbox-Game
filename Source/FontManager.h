#pragma once
#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H
#include"Renderer.h"

class FontManagerC
{
public:
	static FontManagerC	*CreateInstance();
	static FontManagerC	*GetInstance() { return sInstance; };
	~FontManagerC();

	void				init();
	void				DrawTextInBounds(char8_t * text, const Vector2 &pos_ratio, const Vector2 &size_ratio);
	void                DrawStaticText(char8_t *text, Vector2& pos_ratio, Vector2& size_ration);

private:
	FontManagerC();
	static FontManagerC	*sInstance;
	Renderer			*renderer;
};
#endif