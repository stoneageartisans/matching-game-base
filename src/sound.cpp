#include "sound.h"

/*
 * Public Methods
 */

Sound::Sound( android_app* ANDROID_APP, u32 CURRENT_THEME )
{
    initialize( ANDROID_APP, CURRENT_THEME );
}

Sound::~Sound()
{
    dispose();
    CkShutdown();
}

void Sound::play( SoundEffect SOUND_EFFECT, int INDEX )
{
    switch( SOUND_EFFECT )
    {
        case SELECT_TILE:
            sound_select_tile->play();
            break;
        case NO_MATCH:
            sound_no_match->play();
            break;
        case GOT_MATCH:
            sound_objects[INDEX]->play();
            break;
        case COMPLETED:
            sound_completed->play();
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
    for( int i = 0; i < OBJECT_TOTAL; i ++ )
    {
        sound_objects[i]->destroy();
    }
    
    sound_no_match->destroy();
    sound_select_tile->destroy();
    
    for( int i = 0; i < OBJECT_TOTAL; i ++ )
    {
        bank_objects[i]->destroy();
    }
    
    bank_no_match->destroy();
    bank_select_tile->destroy();
}

void Sound::initialize( android_app* ANDROID_APP, u32 CURRENT_THEME )
{
    CkConfig config( ANDROID_APP->activity->vm, ANDROID_APP->activity->clazz );
    CkInit( &config );
    
    bank_completed = CkBank::newBank( SOUNDS_COMPLETED[CURRENT_THEME] );
    sound_completed = CkSound::newBankSound( bank_completed, "fiddle" );
    
    bank_no_match = CkBank::newBank( SOUNDS_NO_MATCH[CURRENT_THEME] );
    sound_no_match = CkSound::newBankSound( bank_no_match, "banjo" );
            
    bank_select_tile = CkBank::newBank( SOUNDS_SELECT_TILE[CURRENT_THEME] );
    sound_select_tile = CkSound::newBankSound( bank_select_tile, "barn" );
    
    for( int i = 0; i < OBJECT_TOTAL; i ++ )
    {
        bank_objects[i] = CkBank::newBank( OBJECT_SOUNDS[CURRENT_THEME][i] );
        sound_objects[i] = CkSound::newBankSound( bank_objects[i], OBJECT_NAMES[CURRENT_THEME][i] );
    }
}
