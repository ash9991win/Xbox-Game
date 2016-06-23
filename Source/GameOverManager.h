#include"Renderer.h"
class GameOverManagerC
{
public:
	static GameOverManagerC* getInstance() { return sInstance; };
	static GameOverManagerC* createInstance();
	void init();
	void render();

private:
	static GameOverManagerC* sInstance;
	GameOverManagerC() {};
	Renderer *renderer;
};
