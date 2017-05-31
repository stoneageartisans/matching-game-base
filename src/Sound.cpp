#include "Sound.h"

/*
 * Public Methods
 */

Sound::Sound( android_app* ANDROID_APP )
{
    initialize( ANDROID_APP );
}

Sound::~Sound()
{
    dispose();
    CkShutdown();
}

void Sound::play( SoundEffect SOUND_EFFECT )
{
    switch( SOUND_EFFECT )
    {
        case NO_SOUND:
            break;
        case SELECT_TILE:
            sound_barn->play();
            break;
    }
}

void Sound::update()
{
    CkUpdate();
}

/*
 * Private Methods
 */

void Sound::dispose()
{
    sound_barn->destroy();
    bank_barn->destroy();
}

void Sound::initialize( android_app* ANDROID_APP )
{
    CkConfig config( ANDROID_APP->activity->vm, ANDROID_APP->activity->clazz );
    CkInit( &config );
    
    bank_barn = CkBank::newBank( SOUND_BARN );
    sound_barn = CkSound::newBankSound( bank_barn, "barn" );
}
