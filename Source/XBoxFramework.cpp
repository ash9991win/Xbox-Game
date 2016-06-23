#include"baseTypes.h"
#include"physics.h"
#include "Renderer.h"
#include "game.h"
#if IS_XBOX
//-----------------------------------------------------------------------------
// Name: main()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
void __cdecl main()
{
	CGame::CreateInstance();
	CGame::GetInstance()->init();

	bool8_t isRunning = true;
	DWORD timeDiffInMillis;
	DWORD lastStoredTime, currentStoredTime = 0;
	while(isRunning){
		// Time Difference
		lastStoredTime = currentStoredTime;
		currentStoredTime = GetTickCount();
		timeDiffInMillis = currentStoredTime - lastStoredTime;

		// Process Application Loop
		CGame::GetInstance()->UpdateFrame(timeDiffInMillis);	// Update The Counter
		CGame::GetInstance()->DrawScene();						// Draw Our Scene
	}

	// Application Is Finished
	CGame::GetInstance()->shutdown();										// User Defined DeInitialization
	CGame::GetInstance()->DestroyGame();

	/*
	Renderer::init2();
	Renderer *game = new Renderer(TEXT_BACKGROUND);
	Renderer *sprite = new Renderer(TEXT_DISC);

	Vector2 pos;
	Vector2 rot;
	TexCoord texture;
	texture.x = 0;
	texture.y = 0;
    while( TRUE )
	{
		Renderer::Begin();

		pos.x = 0;
		pos.y = 0;
		texture.width = 1;
		texture.height = 1;
		game->DrawSprite(pos, 1, 1, texture, 0 , pos);
//640 x 480
		pos.x = 0;
		pos.y = 0;
		texture.width = 125.0f / 1024;
		texture.height = 125.0f / 1024;
		rot = pos;
		rot.x += 66;
		rot.y += 66;
		sprite->DrawSprite(pos, 1, 1, texture, timeGetTime()/4000.0f , rot);

		Renderer::End();
	}
	*/
}
#endif