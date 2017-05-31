#ifndef SOUND_H
#define SOUND_H

#include <android_native_app_glue.h>
#include <irrlicht.h>

#include "ck/ck.h"
#include "ck/sound.h"
#include "ck/bank.h"

#include "constants.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Sound
{
    public:
        Sound( android_app* ANDROID_APP );
        virtual ~Sound();
        void play( SoundEffect SOUND_EFFECT );
        void play( SoundEffect SOUND_EFFECT, int INDEX ); 
        void update();
        
    private:
        CkBank*  bank_no_match;
        CkBank*  bank_select_tile;
        CkSound* sound_no_match;
        CkSound* sound_select_tile;
        CkBank*  banks[OBJECT_TOTAL];
        CkSound* sounds[OBJECT_TOTAL];
        
        void dispose();
        void initialize( android_app* ANDROID_APP );
};

#endif /* SOUND_H */

