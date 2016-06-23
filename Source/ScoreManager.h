#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H
#include"Renderer.h"

typedef enum {
	INVALID_SCORE_STATE = -1,
	SCORE_DISABLED,
	SCORE_TRACKING,
	SCORE_RESULTS,
	NUM_OF_SCORE_STATES
}SCORE_STATE;

class ScoreManagerC
{
public:
	static ScoreManagerC	*CreateInstance();
	static ScoreManagerC	*GetInstance() { return sInstance; };
	~ScoreManagerC();
	
	void changeState(SCORE_STATE newState);
	void					init();
	void					update(DWORD milliseconds);
	void					render();
    int  totalCollectibles;
	int  collected;
private:
	ScoreManagerC();
	DWORD				beginTime;
	const static DWORD	BAR_ANIMATION_DURATION;
	SCORE_STATE			scoreState;

	// Transition Menu elements to display on screen, in order of back-to-front 
	typedef enum  {
		INVALID_TRANS_ELEMENT = -1,
		GRAY_BAR = 0,
		STAR_BAR,
		DISPLAY_SCREEN,
		DISPLAY_SCORE,
		BUTTON_REPLAY,
		BUTTON_MENU,
		BUTTON_NEXT,
		STAR_ONE,
		STAR_TWO,
		STAR_THREE,
		NUM_OF_TRANS_ELEMENTS
	}_TRANS_ELEMENTS;


	FixedRect				transElementsMenuPlacement[NUM_OF_TRANS_ELEMENTS];
	TexCoord				transElementsTextureCoord[NUM_OF_TRANS_ELEMENTS];

	static ScoreManagerC	*sInstance;
	static Renderer			*renderer;
};
#endif
