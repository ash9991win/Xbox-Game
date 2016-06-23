#include <assert.h>
//#include <windows.h>											// Header File For Windows
#include "baseTypes.h"
#include "physics.h"
#include "InputManager.h"

#if IS_COMP
#include "openglframework.h"														// Header File For The NeHeGL Basecode
#else
#include <xtl.h>
#endif

InputManagerC* InputManagerC::sInstance = NULL;
ButtonState InputManagerC::gameButtonState[NUM_OF_GAME_BUTTONS];

InputManagerC *InputManagerC::CreateInstance()
{
	if(sInstance!=NULL)	return sInstance;
	else
		
	sInstance = new InputManagerC();
	return sInstance;
}

void InputManagerC::init(){
	// Clear Key Pressed Array
	int i;
	for(i = 0; i < NUM_OF_GAME_BUTTONS; i++){
		gameButtonState[i].duration = 0;
		gameButtonState[i].pressure = 0;
	}

#if IS_XBOX
	XDEVICE_PREALLOC_TYPE xdpt;
	xdpt.DeviceType = XDEVICE_TYPE_GAMEPAD;
	xdpt.dwPreallocCount = 4;

	// Initialize the peripherals.
    XInitDevices( sizeof(XDEVICE_PREALLOC_TYPE), &xdpt );

	// Set device handles to invalid.
    ZeroMemory( g_hPads, sizeof(g_hPads) );

    // Get initial state of all connected devices.
    gameControllerDeviceState = XGetDevices( XDEVICE_TYPE_GAMEPAD );
    HandleDeviceChanges( XDEVICE_TYPE_GAMEPAD, gameControllerDeviceState, 0 );

#endif
}

//handles keyboard processing
void InputManagerC::update(DWORD milliseconds){
#if IS_COMP
	//	GAME_KEY_JUMP
	if (g_keys->keyDown[VK_SPACE])								// Is SPACE Being Pressed?
	{
		gameButtonState[GAME_KEY_JUMP].isKeyDown = (gameButtonState[GAME_KEY_JUMP].duration == 0
												&& gameButtonState[GAME_KEY_JUMP].isKeyDown == FALSE);
		gameButtonState[GAME_KEY_JUMP].duration += milliseconds;
		gameButtonState[GAME_KEY_JUMP].pressure = INT_MAX;
	}
	else {
		gameButtonState[GAME_KEY_JUMP].isKeyDown = FALSE;
		gameButtonState[GAME_KEY_JUMP].duration = 0;
		gameButtonState[GAME_KEY_JUMP].pressure = 0;
	}

	//	GAME_KEY_START
	if (g_keys->keyDown[VK_RETURN])								// Is Return Being Pressed?
	{
		gameButtonState[GAME_KEY_START].isKeyDown = (gameButtonState[GAME_KEY_START].duration == 0
												&& gameButtonState[GAME_KEY_START].isKeyDown == FALSE);
		gameButtonState[GAME_KEY_START].duration += milliseconds;
		gameButtonState[GAME_KEY_START].pressure = INT_MAX;
	}
	else {
		gameButtonState[GAME_KEY_START].isKeyDown = FALSE;
		gameButtonState[GAME_KEY_START].duration = 0;
		gameButtonState[GAME_KEY_START].pressure = 0;
	}

	//	GAME_KEY_QUIT
	if (g_keys->keyDown[VK_ESCAPE])								// Is ESC Being Pressed?
	{
		gameButtonState[GAME_KEY_QUIT].isKeyDown = (gameButtonState[GAME_KEY_QUIT].duration == 0
			&& gameButtonState[GAME_KEY_QUIT].isKeyDown == FALSE);
		gameButtonState[GAME_KEY_QUIT].duration += milliseconds;
		gameButtonState[GAME_KEY_QUIT].pressure = INT_MAX;

	}
	else {
		gameButtonState[GAME_KEY_QUIT].isKeyDown = FALSE;
		gameButtonState[GAME_KEY_QUIT].duration = 0;
		gameButtonState[GAME_KEY_QUIT].pressure = 0;
	}

	//	GAME_KEY_FULL_SCREEN
	if (g_keys->keyDown[VK_F1])									// Is F1 Being Pressed?
	{
		//ToggleFullscreen(g_window);							// Toggle Fullscreen Mode
		gameButtonState[GAME_KEY_FULL_SCREEN].isKeyDown = (gameButtonState[GAME_KEY_FULL_SCREEN].duration == 0
			&& gameButtonState[GAME_KEY_FULL_SCREEN].isKeyDown == FALSE);
		gameButtonState[GAME_KEY_FULL_SCREEN].duration += milliseconds;
		gameButtonState[GAME_KEY_FULL_SCREEN].pressure = INT_MAX;
	} else {
		gameButtonState[GAME_KEY_FULL_SCREEN].isKeyDown = FALSE;
		gameButtonState[GAME_KEY_FULL_SCREEN].duration = 0;
		gameButtonState[GAME_KEY_FULL_SCREEN].pressure = 0;
	}
	if (g_keys->keyDown[VK_RIGHT])									// Is F1 Being Pressed?
	{
		//ToggleFullscreen(g_window);							// Toggle Fullscreen Mode
		gameButtonState[GAME_KEY_NEXT].isKeyDown = (gameButtonState[GAME_KEY_NEXT].duration == 0
			&& gameButtonState[GAME_KEY_NEXT].isKeyDown == FALSE);
		gameButtonState[GAME_KEY_NEXT].duration += milliseconds;
		gameButtonState[GAME_KEY_NEXT].pressure = INT_MAX;
	}
	else {
		gameButtonState[GAME_KEY_NEXT].isKeyDown = FALSE;
		gameButtonState[GAME_KEY_NEXT].duration = 0;
		gameButtonState[GAME_KEY_NEXT].pressure = 0;
	}
#else
    DWORD dwInsert, dwRemove;

    // Check device type to see if any changes have occurred.
    if( XGetDeviceChanges( XDEVICE_TYPE_GAMEPAD, &dwInsert, &dwRemove ) )
    {
        // Call handler to service the insertion and/or removal.
        HandleDeviceChanges( XDEVICE_TYPE_GAMEPAD, dwInsert, dwRemove );

        // Update new device state.
		gameControllerDeviceState &= ~dwRemove;
        gameControllerDeviceState |= dwInsert;
    }

    XINPUT_STATE xis;

    // Find first connected controller.
	HANDLE hPad = NULL;
    int i;
	bool8_t noController = TRUE;
    // Check the global gamepad state for a connected device.
    for( i = 0; noController && i < NUM_PORTS; i++ )
    {
        if( gameControllerDeviceState & 1 << i && g_hPads[i] ) {
            hPad = g_hPads[i];
            noController = FALSE;
        }
    }
    if(noController)
    {
        return;
    }

    // Query latest state.
    XInputGetState( hPad, &xis );

	// Read state
	//	GAME_KEY_JUMP
	if (xis.Gamepad.bAnalogButtons[XINPUT_GAMEPAD_A] > 0)					// Is (A) Being Pressed?
	{
		gameButtonState[GAME_KEY_NEXT].isKeyDown = (gameButtonState[GAME_KEY_NEXT].duration == 0 
												&& gameButtonState[GAME_KEY_NEXT].isKeyDown == FALSE);

		gameButtonState[GAME_KEY_NEXT].duration += milliseconds;
		gameButtonState[GAME_KEY_NEXT].pressure = xis.Gamepad.bAnalogButtons[XINPUT_GAMEPAD_A];
	}
	else {
		gameButtonState[GAME_KEY_NEXT].isKeyDown = FALSE;
		gameButtonState[GAME_KEY_NEXT].duration = 0;
		gameButtonState[GAME_KEY_NEXT].pressure = 0;
	}

	//	GAME_KEY_START
	if (xis.Gamepad.wButtons & XINPUT_GAMEPAD_START)						// Is ESC Being Pressed?
	{
		gameButtonState[GAME_KEY_START].isKeyDown = (gameButtonState[GAME_KEY_START].duration == 0 
												&& gameButtonState[GAME_KEY_START].isKeyDown == FALSE);
		gameButtonState[GAME_KEY_START].duration += milliseconds;
		gameButtonState[GAME_KEY_START].pressure = INT_MAX;
	}
	else {
		gameButtonState[GAME_KEY_START].isKeyDown = FALSE;
		gameButtonState[GAME_KEY_START].duration = 0;
		gameButtonState[GAME_KEY_START].pressure = 0;
	}

	//	GAME_KEY_QUIT
	if (xis.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)								// Is ESC Being Pressed?
	{
		gameButtonState[GAME_KEY_QUIT].isKeyDown = (gameButtonState[GAME_KEY_QUIT].duration == 0 
												&& gameButtonState[GAME_KEY_QUIT].isKeyDown == FALSE);
		gameButtonState[GAME_KEY_QUIT].duration += milliseconds;
		gameButtonState[GAME_KEY_QUIT].pressure = INT_MAX;

	}
	else {
		gameButtonState[GAME_KEY_QUIT].isKeyDown = FALSE;
		gameButtonState[GAME_KEY_QUIT].duration = 0;
		gameButtonState[GAME_KEY_QUIT].pressure = 0;
	}
	
	//	GAME_KEY_FULL_SCREEN
	gameButtonState[GAME_KEY_FULL_SCREEN].duration = 0;
	gameButtonState[GAME_KEY_FULL_SCREEN].pressure = 0;
#endif
}

#if IS_XBOX
void InputManagerC::HandleDeviceChanges( XPP_DEVICE_TYPE *pxdt, DWORD dwInsert, DWORD dwRemove )
{
    DWORD iPort;
    char szDrive[] = "X:\\";

    if( XDEVICE_TYPE_GAMEPAD == pxdt)
    {
        for( iPort = 0; iPort < NUM_PORTS; iPort++ )
        {
            // Close removals.
            if( (1 << iPort & dwRemove) && g_hPads[iPort] )
            {
                XInputClose( g_hPads[iPort] );
                g_hPads[iPort] = 0;
            }

            // Open insertions.
            if( 1 << iPort & dwInsert )
            {
                g_hPads[iPort] = XInputOpen( pxdt, iPort, XDEVICE_NO_SLOT, NULL );
            }
        }
    }
    
    return;
}
#endif


void	InputManagerC::getButtonPressureRaw(GAME_BUTTON button_type, int32_t &pressure) {
	assert(button_type > INVALID_GAME_BUTTONS && button_type < NUM_OF_GAME_BUTTONS);
	pressure = gameButtonState[button_type].pressure;
}

void	InputManagerC::getButtonPressure(GAME_BUTTON button_type, float_t &pressure) {
	assert(button_type > INVALID_GAME_BUTTONS && button_type < NUM_OF_GAME_BUTTONS);
	pressure = gameButtonState[button_type].pressure / (float_t)INT_MAX;
}

void	InputManagerC::getButtonDuration(GAME_BUTTON button_type, float_t &duration) {
	assert(button_type > INVALID_GAME_BUTTONS && button_type < NUM_OF_GAME_BUTTONS);
	duration = gameButtonState[button_type].duration;
}

void	InputManagerC::getButtonState(GAME_BUTTON button_type, ButtonState &state) {
	assert(button_type > INVALID_GAME_BUTTONS && button_type < NUM_OF_GAME_BUTTONS);
	state.duration = gameButtonState[button_type].duration;
	state.pressure = gameButtonState[button_type].pressure;
}

bool8_t	InputManagerC::getButtonPressed(GAME_BUTTON button_type) {
	assert(button_type > INVALID_GAME_BUTTONS && button_type < NUM_OF_GAME_BUTTONS);
	return gameButtonState[button_type].isKeyDown;
}
