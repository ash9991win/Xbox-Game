#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#if IS_XBOX
#include <XBApp.h>
#include <XAct.h>
#include <XBUtil.h>
#include <dsstdfx.h>
#endif

typedef enum {
	INVALID_GAME_MUSIC = -1,
	MUSIC_MENU,
	MUSIC_BACKGROUND,
	NUM_OF_GAME_MUSIC
}GAME_MUSIC;

typedef enum {
	INVALID_GAME_SOUND_FX = -1,
	SOUND_FX_JUMP,
	NUM_OF_GAME_SOUND_FX
}GAME_SOUND_FX;

class SoundManagerC
{
public:
	static SoundManagerC	*getInstance() {
		if (sInstance == nullptr)
			sInstance = new SoundManagerC();
			return sInstance; };
	void					init();
	void					update(DWORD milliseconds);

	 void				playSoundFX(GAME_SOUND_FX soundfx);
	 void				playMusic(GAME_MUSIC music, bool8_t loop);
private:
	SoundManagerC() {};
	bool isFxPlaying ;
	static SoundManagerC *sInstance;
	
#if IS_XBOX
	float_t fxTime ;
	char	soundFXMap[NUM_OF_GAME_SOUND_FX][10];
	char	musicMap[NUM_OF_GAME_MUSIC][10];
	HRESULT                 hr;        // Return code
    IXACTEngine*            pXACT;         // XACT Engine instance
    IXACTWaveBank*          pStreamingWaveBank;         // XACT Wave Bank
    IXACTSoundBank*         pSoundBank;         // XACT Sound Bank
    IXACTSoundSource*       pSoundSource;         // XACT Sound Source
	XACT_RUNTIME_PARAMETERS xrParams;
	HANDLE hStreamingWaveBank;
	XACT_WAVEBANK_STREAMING_PARAMETERS wbParams;
	BYTE* pbSoundBank;
	DWORD dwFileSize;
	DSEFFECTIMAGELOC EffectLoc;
	DWORD dwSoundCueIndex;
	DWORD dwFxCueIndex;
	XACT_NOTIFICATION_DESCRIPTION xactNotificationDesc;
	XACT_NOTIFICATION xactNotification;
#endif
};
#endif