#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

typedef enum  {
	INVALID_GAME_BUTTONS = -1,
	GAME_KEY_JUMP = 0,
	GAME_KEY_NEXT ,
	GAME_KEY_START,
	GAME_KEY_QUIT,
	GAME_KEY_FULL_SCREEN,
	NUM_OF_GAME_BUTTONS
}GAME_BUTTON;

typedef struct {
	int32_t pressure;
	float_t duration;
	bool8_t isKeyDown;
}ButtonState;

class InputManagerC
{
public:
	static InputManagerC	*CreateInstance();
	static InputManagerC	*GetInstance() {return sInstance;};
	void					init();
	void					update(DWORD milliseconds);
	static bool8_t			getButtonPressed(GAME_BUTTON button_type);
	static void				getButtonPressureRaw(GAME_BUTTON button_type, int32_t &pressure);
	static void				getButtonPressure(GAME_BUTTON button_type, float_t &pressure);
	static void				getButtonDuration(GAME_BUTTON button_type, float_t &duration);
	static void				getButtonState(GAME_BUTTON button_type, ButtonState &state);

private:
	const static int32_t ANALOG_THRESHOLD = 0;

	static ButtonState gameButtonState[NUM_OF_GAME_BUTTONS];

#if IS_XBOX

#define NUM_PORTS   4       // Number of controller ports.
	HANDLE g_hPads[NUM_PORTS];

	DWORD gameControllerDeviceState;
	DWORD prevButtonState;

	void HandleDeviceChanges( XPP_DEVICE_TYPE *pxdt, DWORD dwInsert, DWORD dwRemove );
#endif

	InputManagerC(){};
	static InputManagerC *sInstance;
};
#endif
