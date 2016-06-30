#define GAME_CPP
#include <time.h>
#include "game.h"
#include "CameraManager.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "ScoreManager.h"
#include "MainMenuManager.h"
#include "GameOverManager.h"
#include "PrincessMaanger.h"
#include "SoundManager.h"
#include "Collectible.h"
#include "FontManager.h"
#include "ScoreManager.h"
#include"LevelTextManager.h"
#include "Vector.h"
using namespace Library;
#if IS_COMP


// Declarations
const char8_t CGame::mGameTitle[]="PyroJump";
BOOL Initialize (GL_Window* window, Keys* keys)					// Any OpenGL Initialization Goes Here
{
	initOpenGLDrawing(window,keys,0.0f, 0.0f, 0.0f);
	CGame::CreateInstance();
	CGame::GetInstance()->init();
	return TRUE;						
}
#endif

CGame* CGame::sInstance=nullptr;

void CGame::init()
{
	gameover_duration = 3000;
	gameover_timer = 0;
	Renderer::init2();
	CameraManagerC::getInstance()->Init();
	BackgroundManagerC::getInstance()->init(CGame::mScreenWidth, CGame::mScreenHeight);
	FontManagerC::GetInstance()->init();
	InputManagerC::GetInstance()->init();
	MainMenuManagerC::getInstance()->init();
	GameOverManagerC::getInstance()->init();
	SoundManagerC::getInstance()->init();
	FontManagerC::GetInstance()->init();
	ScoreManagerC::GetInstance()->init();
	ScoreManagerC::GetInstance()->changeState(SCORE_DISABLED);

	currentState = MENU_STATE;
	currentLevel = 1;
}
void CGame::UpdateFrame(DWORD milliseconds)			
{
	InputManagerC::GetInstance()->update(milliseconds);
	SoundManagerC::getInstance()->update(milliseconds);
	ScoreManagerC::GetInstance()->update(milliseconds);
	Vector2 scorePosRatio;
	scorePosRatio.x = 0.66f;
	scorePosRatio.y = 0.01f;

	Vector2 scoreSizeRatio;
	scoreSizeRatio.x = 0.33f;
	scoreSizeRatio.y = 0.9f;


	switch (currentState) {
	case MENU_STATE:
		currentLevel = 1;
		if (InputManagerC::getButtonPressed(GAME_KEY_START))
		{
			currentState = LOAD_GAME_STATE;
		}
		if (InputManagerC::getButtonPressed(GAME_KEY_JUMP))
		{
			SoundManagerC::getInstance()->playSoundFX(SOUND_FX_JUMP);
		}
#if IS_XBOX
		if(InputManagerC::getButtonPressed(GAME_KEY_QUIT))
		{
			LD_LAUNCH_DASHBOARD LaunchData = { XLD_LAUNCH_DASHBOARD_MAIN_MENU };
            XLaunchNewImage( nullptr, (LAUNCH_DATA*)&LaunchData );
		}
#endif
		break;

	case LOAD_GAME_STATE:
		DiscManagerC::getInstance()->init();
		PlayerManager::getInstance()->Init();
		ScoreManagerC::GetInstance()->init();
		PrincessManager::getInstance()->init();
		Collectible::getInstance()->init();
		FontManagerC::GetInstance()->init();
		ScoreManagerC::GetInstance()->changeState(SCORE_TRACKING);
		ScoreManagerC::GetInstance()->collected = 0;
		LevelTextManager::getInstance()->init();
		LevelLoader::getInstance()->setDiscList(*DiscManagerC::getInstance()->getDiscList());
		LevelLoader::getInstance()->setFireList(*Collectible::getInstance()->getFireList());
		LevelLoader::getInstance()->setTextList(*(LevelTextManager::getInstance()->getTextList()));
		LevelLoader::getInstance()->LoadLevel(currentLevel);
		currentState = PLAY_STATE;
		break;

	case PLAY_STATE:
		checkForCollision();
        
		DiscManagerC::getInstance()->update(milliseconds);
		PlayerManager::getInstance()->Update(milliseconds);
		CameraManagerC::getInstance()->update(milliseconds);
		BackgroundManagerC::getInstance()->update(milliseconds);
		PrincessManager::getInstance()->Update(milliseconds);
		Collectible::getInstance()->update(milliseconds);
		LevelTextManager::getInstance()->update(milliseconds);
		checkForInput();
		if (PlayerManager::getInstance()->isgameOver()) {
			gameover_timer = 0;
			currentState = GAMEOVER_STATE;
		}
	
		break;
	case GAMEWON_STATE:
		gameover_timer += milliseconds;
		if (gameover_timer > gameover_duration) {
			currentState = GAMEOVER_STATE;
		}
         PrincessManager::getInstance()->Update(milliseconds);
		break;
	case GAMEOVER_STATE:
		
		if(InputManagerC::getButtonPressed(GAME_KEY_START))
		{
			currentState = LOAD_GAME_STATE;
		}
		if(InputManagerC::getButtonPressed(GAME_KEY_NEXT))
		{
			if(currentLevel < MAX_LEVELS)
			{
				++currentLevel;
				currentState = LOAD_GAME_STATE;
			}
			else
			{
				currentState = MENU_STATE;
			}
		}
		if(InputManagerC::getButtonPressed(GAME_KEY_QUIT))
		{
			   currentLevel = 1;
               currentState = MENU_STATE;
		}
		break;
	case LOAD_LEVEL_STATE:
		if (PrincessManager::getInstance()->isAnimationOver)
		{
			DiscManagerC::getInstance()->init();
			PlayerManager::getInstance()->Init();
			PrincessManager::getInstance()->init();
			Collectible::getInstance()->init();
			LevelTextManager::getInstance()->init();
			FontManagerC::GetInstance()->init();
            ScoreManagerC::GetInstance()->collected = 0;
			LevelLoader::getInstance()->setDiscList(*DiscManagerC::getInstance()->getDiscList());
			LevelLoader::getInstance()->setFireList(*Collectible::getInstance()->getFireList());
			LevelLoader::getInstance()->setTextList(*LevelTextManager::getInstance()->getTextList());
			LevelLoader::getInstance()->LoadLevel(currentLevel);
			currentState = PLAY_STATE;

		}
		PrincessManager::getInstance()->Update(milliseconds);
		break;
	default: break;
	}
}

void CGame::DrawScene(void)											
{
	Renderer::Begin();
	
	switch (currentState) {
	case MENU_STATE:
	{
		MainMenuManagerC::getInstance()->render();

		Vector2 pos;
		pos.x = 0.3;
		pos.y = 0.65;

		Vector2 size;
		size.x = 0.4;
		size.y = 0.05;

		FontManagerC::GetInstance()->DrawTextInBounds("PRESS START TO PLAY", pos, size);
		pos.y += 0.075;
		FontManagerC::GetInstance()->DrawTextInBounds("PRESS BACK TO EXIT", pos, size);
		break;
	}
	case LOAD_GAME_STATE:
		BackgroundManagerC::getInstance()->renderBackground();
		break;
	case GAMEWON_STATE:
	case PLAY_STATE:
		CameraManagerC::getInstance()->render();

		BackgroundManagerC::getInstance()->renderBackground();

	
		
	
		DiscManagerC::getInstance()->render();
		PlayerManager::getInstance()->Render();
		PrincessManager::getInstance()->render();
		LevelTextManager::getInstance()->render();

		Collectible::getInstance()->render();
		ScoreManagerC::GetInstance()->render();
		break;
	case GAMEOVER_STATE:
		ScoreManagerC::GetInstance()->changeState(SCORE_RESULTS);
		GameOverManagerC::getInstance()->render();
		BackgroundManagerC::getInstance()->renderBackground();
		ScoreManagerC::GetInstance()->render();
		break;
	
		

	case LOAD_LEVEL_STATE:
		CameraManagerC::getInstance()->render();

		BackgroundManagerC::getInstance()->renderBackground();
		LevelTextManager::getInstance()->render();
		PlayerManager::getInstance()->Render();
		DiscManagerC::getInstance()->render();
		PrincessManager::getInstance()->render();
		break;
	default: break;
	}
	
	Renderer::End();
}

void   CGame::checkForCollision()
{
	bool checkForCollision = true;
	auto discList = DiscManagerC::getInstance()->getDiscList();
	for(auto currentDisc :*discList)
	{
	if (CollisionManager::getInstance()->checkForCollision(currentDisc->collider, PlayerManager::getInstance()->getCollider()))
		{
				if (currentDisc->discType == JUMPABLE_DISC)
				{
					if (PlayerManager::getInstance()->getRotatingPoint() != currentDisc->center)
					{
						PlayerManager::getInstance()->setRotationPoint(currentDisc->center, currentDisc->spokeRadius  );
						PlayerManager::getInstance()->setRotationSpeed(currentDisc->speed);
						PlayerManager::getInstance()->setDirection(currentDisc->direction);
						PlayerManager::getInstance()->setDiscCollider(currentDisc->collider);
						PlayerManager::getInstance()->discRadius = currentDisc->spokeRadius;
						PlayerManager::getInstance()->isMegajump = false;
						PlayerManager::getInstance()->changeCurrentState(ROTATING_STATE);
						currentDisc->canSeePlayer = true;
						currentDisc->isVisited = true;
						break;
					}
				}
				else if (currentDisc->discType == ENEMY_DISC)
					{
						currentState = GAMEOVER_STATE;
						gameover_timer = 0;
						break;
					}
					else if (currentDisc->discType == MEGA_JUMP)
					{
						if (PlayerManager::getInstance()->getRotatingPoint() != currentDisc->center)
						{
							PlayerManager::getInstance()->setRotationPoint(currentDisc->center, currentDisc->spokeRadius);
							PlayerManager::getInstance()->setRotationSpeed(currentDisc->speed);
							PlayerManager::getInstance()->setDirection(currentDisc->direction);
							PlayerManager::getInstance()->setDiscCollider(currentDisc->collider);
							PlayerManager::getInstance()->discRadius = currentDisc->spokeRadius;
							PlayerManager::getInstance()->isMegajump = true;
							PlayerManager::getInstance()->changeCurrentState(ROTATING_STATE);
							currentDisc->canSeePlayer = true;
							currentDisc->isVisited = true;
						}
					}
				}
			}
		if (CollisionManager::getInstance()->checkForCollision(PlayerManager::getInstance()->getCollider(), PrincessManager::getInstance()->collider))
		{
			
			PrincessManager::getInstance()->amBurnt = true;
			currentLevel++;
			
				if (currentLevel > MAX_LEVELS)
				{
					currentLevel = 1;
					currentState = MENU_STATE;
				}
				else
				{
					currentState = GAMEWON_STATE;
					gameover_timer  = 0;
				}
			
		}
		auto fireList = Collectible::getInstance()->getFireList();
		for(auto current : *fireList)
		{

			if (CollisionManager::getInstance()->checkForCollision(PlayerManager::getInstance()->getCollider(), current->collider) && current->isVisible)
			{
				current->isVisible = false;
				ScoreManagerC::GetInstance()->collected++;

			}
		}
}

void CGame::checkForInput()
{
	if (InputManagerC::getButtonPressed(GAME_KEY_JUMP) &&  PlayerManager::getInstance()->isRotating())
	{
		SoundManagerC::getInstance()->playSoundFX(SOUND_FX_JUMP);
		PlayerManager::getInstance()->changeCurrentState(JUMPING_STATE);
	}
}
CGame *CGame::CreateInstance()
{
	sInstance = new CGame();
	return sInstance;
}
void CGame::shutdown()
{
}
void CGame::DestroyGame(void)
{
}
