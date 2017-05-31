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
        case SELECT_TILE:
            sound_barn->play();
            break;
        case NO_MATCH:
            sound_banjo->play();
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
    sound_banjo->destroy();
    sound_barn->destroy();
    
    bank_banjo->destroy();
    bank_barn->destroy();
}

void Sound::initialize( android_app* ANDROID_APP )
{
    CkConfig config( ANDROID_APP->activity->vm, ANDROID_APP->activity->clazz );
    CkInit( &config );
    
    bank_banjo = CkBank::newBank( SOUND_BANJO );
    sound_banjo = CkSound::newBankSound( bank_banjo, "banjo" );
            
    bank_barn = CkBank::newBank( SOUND_BARN );
    sound_barn = CkSound::newBankSound( bank_barn, "barn" );
}
