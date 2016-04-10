#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "baseTypes.h"
#include "physics.h"
#include "CameraManager.h"
#include "ScoreManager.h"
#include "FontManager.h"

ScoreManagerC*	ScoreManagerC::sInstance = NULL;
Renderer*		ScoreManagerC::renderer;
const DWORD		ScoreManagerC::BAR_ANIMATION_DURATION = 1000;

ScoreManagerC *ScoreManagerC::CreateInstance()
{
	if (sInstance != NULL)	return sInstance;
	else

		sInstance = new ScoreManagerC();
	return sInstance;
}

ScoreManagerC::ScoreManagerC() 
{
	renderer = NULL;
}

ScoreManagerC::~ScoreManagerC() 
{
	if (renderer != NULL) {
		delete renderer;
	}
}

void ScoreManagerC::init()
{
	if (renderer == NULL) {
		renderer = new Renderer(TEXT_TRANSITION);
	}

	collected = 0;
	totalCollectibles = 0;
	
	// Constant Menu Positioning for each element displayed
	transElementsMenuPlacement[DISPLAY_SCREEN].x		= 0.1671;
	transElementsMenuPlacement[DISPLAY_SCORE].x			= 0.3816;
	transElementsMenuPlacement[BUTTON_REPLAY].x			= 0.24;			// Modifiable
	transElementsMenuPlacement[BUTTON_MENU].x			= 0.41;			// Modifiable
	transElementsMenuPlacement[BUTTON_NEXT].x			= 0.58;			// Modifiable
	transElementsMenuPlacement[STAR_ONE].x				= 0.3565;
	transElementsMenuPlacement[STAR_TWO].x				= 0.4791;
	transElementsMenuPlacement[STAR_THREE].x			= 0.6016;
	transElementsMenuPlacement[STAR_BAR].x				= 0.2924;
	transElementsMenuPlacement[GRAY_BAR].x				= 0.2924;

	transElementsMenuPlacement[DISPLAY_SCREEN].y		= 0;
	transElementsMenuPlacement[DISPLAY_SCORE].y			= 0.2685;
	transElementsMenuPlacement[BUTTON_REPLAY].y			= 0.7176;
	transElementsMenuPlacement[BUTTON_MENU].y			= 0.7176;
	transElementsMenuPlacement[BUTTON_NEXT].y			= 0.6806;
	transElementsMenuPlacement[STAR_ONE].y				= 0.1019;
	transElementsMenuPlacement[STAR_TWO].y				= 0.0750;	//0.0787
	transElementsMenuPlacement[STAR_THREE].y			= 0.0463;
	transElementsMenuPlacement[STAR_BAR].y				= 0.0463;
	transElementsMenuPlacement[GRAY_BAR].y				= 0.0463;

	transElementsMenuPlacement[DISPLAY_SCREEN].width	= 0.6630;
	transElementsMenuPlacement[DISPLAY_SCORE].width		= 0.2618;
	transElementsMenuPlacement[BUTTON_REPLAY].width		= 0.1355;
	transElementsMenuPlacement[BUTTON_MENU].width		= 0.1355;
	transElementsMenuPlacement[BUTTON_NEXT].width		= 0.1806;
	transElementsMenuPlacement[STAR_ONE].width			= 0.07;		//0.0696
	transElementsMenuPlacement[STAR_TWO].width			= 0.0863;
	transElementsMenuPlacement[STAR_THREE].width		= 0.1031;
	transElementsMenuPlacement[STAR_BAR].width			= 0.3510;
	transElementsMenuPlacement[GRAY_BAR].width			= 0.3510;

	transElementsMenuPlacement[DISPLAY_SCREEN].height	= 1.0;
	transElementsMenuPlacement[DISPLAY_SCORE].height	= 0.1520;
	transElementsMenuPlacement[BUTTON_REPLAY].height	= 0.1806;
	transElementsMenuPlacement[BUTTON_MENU].height		= 0.1806;
	transElementsMenuPlacement[BUTTON_NEXT].height		= 0.2407;
	transElementsMenuPlacement[STAR_ONE].height			= 0.1170;	//0.1111
	transElementsMenuPlacement[STAR_TWO].height			= 0.14;		//0.1343
	transElementsMenuPlacement[STAR_THREE].height		= 0.1667;
	transElementsMenuPlacement[STAR_BAR].height			= 0.1667;
	transElementsMenuPlacement[GRAY_BAR].height			= 0.1667;


	// Constant Menu Positioning for each element displayed
	transElementsTextureCoord[DISPLAY_SCREEN].x		= 0	  / 1024.0f;
	transElementsTextureCoord[DISPLAY_SCORE].x		= 0;				// Not used in loop
	transElementsTextureCoord[BUTTON_REPLAY].x		= 824 / 1024.0f;
	transElementsTextureCoord[BUTTON_MENU].x		= 824 / 1024.0f;
	transElementsTextureCoord[BUTTON_NEXT].x		= 824 / 1024.0f;
	transElementsTextureCoord[STAR_ONE].x			= 824 / 1024.0f;
	transElementsTextureCoord[STAR_TWO].x			= 824 / 1024.0f;
	transElementsTextureCoord[STAR_THREE].x			= 824 / 1024.0f;
	transElementsTextureCoord[STAR_BAR].x			= 824 / 1024.0f;
	transElementsTextureCoord[GRAY_BAR].x			= 924 / 1024.0f;

	transElementsTextureCoord[DISPLAY_SCREEN].y		= 0   / 1024.0f;
	transElementsTextureCoord[DISPLAY_SCORE].y		= 0;				// Not used in loop
	transElementsTextureCoord[BUTTON_REPLAY].y		= 400 / 1024.0f;
	transElementsTextureCoord[BUTTON_MENU].y		= 600 / 1024.0f;
	transElementsTextureCoord[BUTTON_NEXT].y		= 200 / 1024.0f;
	transElementsTextureCoord[STAR_ONE].y			= 0	  / 1024.0f;
	transElementsTextureCoord[STAR_TWO].y			= 0   / 1024.0f;
	transElementsTextureCoord[STAR_THREE].y			= 0   / 1024.0f;
	transElementsTextureCoord[STAR_BAR].y			= 800 / 1024.0f;
	transElementsTextureCoord[GRAY_BAR].y			= 800 / 1024.0f;

	transElementsTextureCoord[DISPLAY_SCREEN].width	= 824 / 1024.0f;
	transElementsTextureCoord[DISPLAY_SCORE].width  = 0;
	transElementsTextureCoord[BUTTON_REPLAY].width	= 200 / 1024.0f;
	transElementsTextureCoord[BUTTON_MENU].width	= 200 / 1024.0f;
	transElementsTextureCoord[BUTTON_NEXT].width	= 200 / 1024.0f;
	transElementsTextureCoord[STAR_ONE].width		= 200 / 1024.0f;
	transElementsTextureCoord[STAR_TWO].width		= 200 / 1024.0f;
	transElementsTextureCoord[STAR_THREE].width		= 200 / 1024.0f;
	transElementsTextureCoord[STAR_BAR].width		= 100 / 1024.0f;
	transElementsTextureCoord[GRAY_BAR].width		= 100 / 1024.0f;

	transElementsTextureCoord[DISPLAY_SCREEN].height= 1024 / 1024.0f;
	transElementsTextureCoord[DISPLAY_SCORE].height = 0;				// Not used in loop
	transElementsTextureCoord[BUTTON_REPLAY].height = 200 / 1024.0f;
	transElementsTextureCoord[BUTTON_MENU].height	= 200 / 1024.0f;
	transElementsTextureCoord[BUTTON_NEXT].height	= 200 / 1024.0f;
	transElementsTextureCoord[STAR_ONE].height		= 200 / 1024.0f;
	transElementsTextureCoord[STAR_TWO].height		= 200 / 1024.0f;
	transElementsTextureCoord[STAR_THREE].height	= 200 / 1024.0f;
	transElementsTextureCoord[STAR_BAR].height		= 100 / 1024.0f;
	transElementsTextureCoord[GRAY_BAR].height		= 100 / 1024.0f;
}

void ScoreManagerC::update(DWORD milliseconds){
	
	switch(scoreState){
	case SCORE_RESULTS:
		// Moving Bar animation counter
		beginTime += milliseconds;
		if(beginTime > BAR_ANIMATION_DURATION) {
			beginTime = BAR_ANIMATION_DURATION;
		}
		break;
	case SCORE_TRACKING:
		// No code here
		break;
	case SCORE_DISABLED:
		break;
	default: throw 0;
	}

}

void ScoreManagerC::render() 
{

	Vector2 screenPosition;
	screenPosition.x = 0;
	screenPosition.y = 0;
	//CameraManagerC::getInstance()->getCameraPosition(screenPosition);

	Vector2 screenSize;
	CameraManagerC::getInstance()->getCameraSize(screenSize);

	Vector2 position;
	Vector2 size;
	int32_t i;
	char8_t text[20];
    char8_t scoreText[10];
	Vector2 scorePosition;
	scorePosition.x  = 0.75f;
	scorePosition.y = 0.05f;
    Vector2 scoreWidth;
	scoreWidth.x = 0.2f;
	scoreWidth.y = 0.125f;
	switch (scoreState) {
	case SCORE_TRACKING:
		sprintf(scoreText,"%d / %d",collected,totalCollectibles);
		FontManagerC::GetInstance()->DrawTextInBounds(scoreText,scorePosition,scoreWidth);
		break;
	case SCORE_RESULTS:
		// Draw Transition Menu Display
		for (i = 0; i < NUM_OF_TRANS_ELEMENTS; i++) {
		
			if (i == DISPLAY_SCORE) {
				position.x = transElementsMenuPlacement[i].x;
				position.y = transElementsMenuPlacement[i].y;
				size.x = transElementsMenuPlacement[i].width;
				size.y = transElementsMenuPlacement[i].height;

				sprintf(text, "%2d/%2d", collected , totalCollectibles);
				FontManagerC::GetInstance()->DrawTextInBounds(text, position, size);
			}
			else {
				// Only display the stars earned based on count to total count ratio
				if ((i == STAR_ONE && collected * 3 < totalCollectibles)
					||  (i == STAR_TWO && collected * 3 < 2 * totalCollectibles)
				||  (i == STAR_THREE && collected < totalCollectibles) ) {
					continue;
				}

				// If criterias met, draw menu element
				position.x = screenPosition.x + screenSize.x * transElementsMenuPlacement[i].x;
				position.y = screenPosition.y + screenSize.y * transElementsMenuPlacement[i].y;
				size.x = transElementsMenuPlacement[i].width * screenSize.x;
				size.y = transElementsMenuPlacement[i].height * screenSize.y;
				if (i == STAR_BAR) {
					// Width of bar is affect by the score in the level
					size.x *= (collected * beginTime) / (float_t) (totalCollectibles * BAR_ANIMATION_DURATION);
				}
				renderer->DrawSprite(position, size.x, size.y, transElementsTextureCoord[i]);
			}
		}
		break;
	default:
		throw 0;
	}

	// Draw Sprites
}

void ScoreManagerC::changeState(SCORE_STATE newState){
	if(scoreState == newState) return;

	switch(newState){
	case SCORE_RESULTS:
		beginTime = 0;
		break;
	case SCORE_TRACKING:
		// No code here
		break;
	case SCORE_DISABLED:
		break;
	default: throw 0;
	}
	scoreState = newState;
}

