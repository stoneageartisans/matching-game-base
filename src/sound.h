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
        Sound( android_app* ANDROID_APP, u32 CURRENT_THEME );
        virtual ~Sound();
        void load_theme( u32 CURRENT_THEME );
        void play( SoundEffect SOUND_EFFECT, int INDEX = -1 );
        void update();
        
    private:
        CkBank*  bank_completed;
        CkBank*  bank_no_match;
        CkBank*  bank_objects[OBJECT_TOTAL];
        CkBank*  bank_select_tile;
        CkSound* sound_completed;
        CkSound* sound_no_match;
        CkSound* sound_objects[OBJECT_TOTAL];
        CkSound* sound_select_tile;
        
        void dispose();
        void initialize( android_app* ANDROID_APP, u32 CURRENT_THEME );
};

#endif /* SOUND_H */

