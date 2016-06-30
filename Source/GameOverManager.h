#include"Renderer.h"
class GameOverManagerC
{
public:
	static GameOverManagerC* getInstance() {
		if (sInstance == nullptr)
			sInstance = new GameOverManagerC();
		return sInstance; };
	void init();
	void render();

private:
	static GameOverManagerC* sInstance;
	GameOverManagerC() {};
	Renderer *renderer;
};
