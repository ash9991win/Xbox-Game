#include "baseTypes.h"
#include<string.h>

#include "physics.h"
#include "SoundManager.h"
//#include "XBApp.h"


SoundManagerC* SoundManagerC::sInstance = NULL;
//FMOD::Sound *	SoundManagerC::soundFXMap[NUM_OF_GAME_SOUND_FX];
//FMOD::Sound *	SoundManagerC::musicMap[NUM_OF_GAME_MUSIC];

SoundManagerC *SoundManagerC::CreateInstance()
{
	if (sInstance != NULL)	return sInstance;
	else

		sInstance = new SoundManagerC();
	return sInstance;
}

void SoundManagerC::init() {
	
#if IS_XBOX
	// Initialize our Instance with 36 Channels
	//soundSystem->init(36, FMOD_INIT_NORMAL, NULL);


	//// Create Sounds
	//FMOD::Sound *jump;
	//FMOD::Sound *menu_music;
	//FMOD::Sound *bg_music;

	//soundSystem->createSound("assets/jump.wav", FMOD_DEFAULT, 0, &jump);
	//soundSystem->createSound("assets/Danger_Storm.mp3", FMOD_DEFAULT, 0, &menu_music);
	//soundSystem->createSound("assets/Rhinoceros.mp3", FMOD_DEFAULT, 0, &bg_music);

	//soundFXMap[SOUND_FX_JUMP] = jump;
	//musicMap[MUSIC_MENU] = menu_music;
	//musicMap[MUSIC_MENU] = bg_music;
	isFxPlaying = false;


	 hr                  = S_OK;         // Return code
     pXACT               = NULL;         // XACT Engine instance
	 pStreamingWaveBank  = NULL;         // XACT Wave Bank
     pSoundBank          = NULL;         // XACT Sound Bank
     pSoundSource        = NULL;         // XACT Sound Source

	 sprintf(musicMap[MUSIC_BACKGROUND],"BgMusic");
	 sprintf(soundFXMap[SOUND_FX_JUMP],"jump");

//    xrParams = 0;
    xrParams.dwMax2DHwVoices         = 128; // Maximum number of 2D hardware voices/streams XACT engine will use
    xrParams.dwMax3DHwVoices         = 32;  // Maximum number of 3D hardware voices/streams XACT engine will use, between 0 and 64
    xrParams.dwMaxConcurrentStreams  = 16;  // Maximum number of 2D voices XACT may use for streaming from the hard drive/DVD
    xrParams.dwMaxNotifications      = 0;   // Maximum number of notifications, 0 = default
	 if( FAILED( hr = XACTEngineCreate( &xrParams, &pXACT ) ) )
    {
       throw 0;
    }

    hStreamingWaveBank = CreateFile( "D:\\media\\sounds\\XactSounds_streaming.xwb",
                                            GENERIC_READ, FILE_SHARE_READ, NULL,
                                            OPEN_EXISTING, FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING, NULL );
	 if( INVALID_HANDLE_VALUE == hStreamingWaveBank )
    {
        throw 0;
    }
//	wbParams = 0;
    wbParams.hFile                        = hStreamingWaveBank;
    wbParams.dwOffset                     = 0;
    wbParams.dwPacketSizeInMilliSecs      = 400;
    wbParams.dwPrimePacketSizeInMilliSecs = 400;

	/*if( FAILED(*/ hr = pXACT->RegisterStreamedWaveBank( &wbParams, &pStreamingWaveBank ) ;/*) )*/
       /* throw 0;*/
    pbSoundBank = NULL;
	dwFileSize  = 0;

	if( FAILED( hr = XBUtil_LoadFile( "D:\\media\\sounds\\XactSounds.xsb", (VOID **)&pbSoundBank, &dwFileSize ) ) )
        throw 0;

    // Register the sound bank with XACT
    if( FAILED( hr = pXACT->CreateSoundBank( pbSoundBank, dwFileSize, &pSoundBank ) ) )
        throw 0;

	
    EffectLoc.dwI3DL2ReverbIndex = GraphI3DL2_I3DL2Reverb;
    EffectLoc.dwCrosstalkIndex   = GraphXTalk_XTalk;
    if( FAILED( XAudioDownloadEffectsImage( "d:\\media\\dsstdfx.bin", 
                                            &EffectLoc, 
                                            XAUDIO_DOWNLOADFX_EXTERNFILE, 
                                            NULL ) ) )
        throw 0;
 
    // Create a 3D sound source to play our cues on 
    /*if( FAILED( hr = pXACT->CreateSoundSource( XACT_FLAG_SOUNDSOURCE_3D, &pSoundSource ) ) )
        throw 0;*/

	dwSoundCueIndex = 0;
    if( FAILED( hr = pSoundBank->GetSoundCueIndexFromFriendlyName( "hit",             // Null-terminated string representing the friendly
                                                                   &dwSoundCueIndex ) ) )   // Pointer to the returned SoundCue index for friendly name
    {
        throw 0;
    }
	//dwSoundCueIndex = 1;
	if( FAILED( hr = pSoundBank->GetSoundCueIndexFromFriendlyName( "BgMusic",             // Null-terminated string representing the friendly
                                                                   &dwSoundCueIndex ) ) )   // Pointer to the returned SoundCue index for friendly name
    {
        throw 0;
    }

//	xactNotificationDesc = 0;
    xactNotificationDesc.wType              = eXACTNotification_Stop;
    xactNotificationDesc.wFlags             = XACT_FLAG_NOTIFICATION_USE_SOUNDCUE_INDEX;
    xactNotificationDesc.u.pSoundBank       = pSoundBank;
    xactNotificationDesc.dwSoundCueIndex    = dwSoundCueIndex;
    xactNotificationDesc.hEvent             = NULL;

	if( FAILED( hr = pXACT->RegisterNotification( &xactNotificationDesc ) ) )
       throw 0;

    // Play the sound cue
   if( FAILED( hr = pSoundBank->Play( dwSoundCueIndex, pSoundSource, XACT_FLAG_SOUNDCUE_AUTORELEASE, NULL) ) )
        throw 0;

  fxTime = 0;
#endif
}

//handles keyboard processing
void	SoundManagerC::update(DWORD milliseconds) {
#if IS_XBOX
     XACTEngineDoWork();
	 if(isFxPlaying)
	 {
		 fxTime += milliseconds / 1000.0f;
		 //if(fxTime > 1.25f)
		 //{ 
			// /*if(FAILED(*/hr = pSoundBank->Stop(dwFxCueIndex,XACT_FLAG_SOUNDCUE_IMMEDIATE,NULL);
			// /*{*/
			///*	 throw 0;
			// }*/
			// isFxPlaying = false;
		 //}
	 }
#endif
}

void	SoundManagerC::playSoundFX(GAME_SOUND_FX soundfx) {
	
#if IS_XBOX
	if( FAILED( hr = pSoundBank->GetSoundCueIndexFromFriendlyName( soundFXMap[soundfx],             // Null-terminated string representing the friendly
																	   &dwSoundCueIndex ) ) )   // Pointer to the returned SoundCue index for friendly name
	{
		throw 0;
	}
	if (FAILED(hr = pSoundBank->Play(dwSoundCueIndex, pSoundSource, XACT_FLAG_SOUNDCUE_AUTORELEASE, NULL))) 
	{
		throw 0;
	}
	
#endif
}


void	SoundManagerC::playMusic(GAME_MUSIC music, bool8_t loop) {
#if IS_XBOX
	//	assert(music > INVALID_GAME_MUSIC && music < NUM_OF_GAME_MUSIC);
	dwSoundCueIndex = 0;
	if( FAILED( hr = pSoundBank->GetSoundCueIndexFromFriendlyName( musicMap[music],             // Null-terminated string representing the friendly
																	   &dwSoundCueIndex ) ) )   // Pointer to the returned SoundCue index for friendly name
		{
			throw 0;
		}
#endif

}
