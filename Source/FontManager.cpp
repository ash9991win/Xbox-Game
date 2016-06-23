#include <assert.h>
#include "baseTypes.h"
#include "physics.h"
#include"CameraManager.h"
#include "FontManager.h"
FontManagerC*	FontManagerC::sInstance = NULL;

FontManagerC *FontManagerC::CreateInstance()
{
	if (sInstance != NULL)	return sInstance;
	else

		sInstance = new FontManagerC();
	return sInstance;
}

FontManagerC::FontManagerC()
{
	renderer = NULL;
}

FontManagerC::~FontManagerC()
{
	if (renderer != NULL) {
		delete renderer;
	}
}

void FontManagerC::init()
{
	if (renderer == NULL) {
		renderer = new Renderer(TEXT_SCORE_FONT);
	}
}


void FontManagerC::DrawTextInBounds(char8_t * text, const Vector2 &pos_ratio, const Vector2 &size_ratio) {
	Vector2 screen_pos;
	screen_pos.x = 0;
	screen_pos.y = 0;
	Vector2 screen_size;
	CameraManagerC::getInstance()->getCameraSize(screen_size);

	screen_pos.x += screen_size.x * (pos_ratio.x + size_ratio.x);
	screen_pos.y += screen_size.y * pos_ratio.y;

	int32_t len = strlen(text);
	Vector2 font_size;
	font_size.x = screen_size.x * (size_ratio.x / len);
	font_size.y = screen_size.y * (size_ratio.y);

	const static int32_t FONT_COL_COUNT = 16;
	const static int32_t FONT_ROW_COUNT = 10;
	const static float_t FONT_SIZE_WIDTH = 1.0f / FONT_COL_COUNT;
	const static float_t FONT_SIZE_HEIGHT = 1.0f / FONT_ROW_COUNT;

	TextureCoordinates texture;
	texture.width = FONT_SIZE_WIDTH;
	texture.height = FONT_SIZE_HEIGHT;

	bool non_zero = false;
	int32_t i;
	int32_t value;
	for (i = len - 1; i >= 0; i--) {
		screen_pos.x -= font_size.x;

		value = text[i] - ' ';

		if (value >= 0 || value < FONT_COL_COUNT * FONT_ROW_COUNT) {
			texture.x = (value % FONT_COL_COUNT) * FONT_SIZE_WIDTH;
			texture.y = ((int32_t)(value / FONT_COL_COUNT)) * FONT_SIZE_HEIGHT;
			
			// Draw Digit
			renderer->DrawSprite(screen_pos, font_size.x, font_size.y, texture);
		}
	}
}

void FontManagerC::DrawStaticText(char8_t *text, Vector2& pos_ratio, Vector2& size_ratio)
{
	Vector2 screen_pos;
	CameraManagerC::getInstance()->getCameraPosition(screen_pos);

	Vector2 screen_size;
	CameraManagerC::getInstance()->getCameraSize(screen_size);
	Vector2 convertedPosition;
	convertedPosition.x = pos_ratio.x * SCREEN_WIDTH;
	convertedPosition.y = pos_ratio.y * SCREEN_HEIGHT;


	int32_t len = strlen(text);
	Vector2 font_size;
	font_size.x = screen_size.x * (size_ratio.x / len);
	font_size.y = screen_size.y * (size_ratio.y);

	const static int32_t FONT_COL_COUNT = 16;
	const static int32_t FONT_ROW_COUNT = 10;
	const static float_t FONT_SIZE_WIDTH = 1.0f / FONT_COL_COUNT;
	const static float_t FONT_SIZE_HEIGHT = 1.0f / FONT_ROW_COUNT;

	TextureCoordinates texture;
	texture.width = FONT_SIZE_WIDTH;
	texture.height = FONT_SIZE_HEIGHT;

	bool non_zero = false;
	int32_t i;
	int32_t value;
	for (i = len - 1; i >= 0; i--) {
		convertedPosition.x -= font_size.x ;
		value = text[i] - ' ';
		if (value >= 0 || value < FONT_COL_COUNT * FONT_ROW_COUNT) {
			texture.x = (value % FONT_COL_COUNT) * FONT_SIZE_WIDTH;
			texture.y = ((int32_t)(value / FONT_COL_COUNT)) * FONT_SIZE_HEIGHT;
			// Draw Digit
			renderer->DrawSprite(convertedPosition.findDiff(screen_pos), font_size.x, font_size.y, texture);
		}
	}
}