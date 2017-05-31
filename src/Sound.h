#ifndef SOUND_H
#define SOUND_H

#include <android_native_app_glue.h>

#include "ck/ck.h"
#include "ck/sound.h"
#include "ck/bank.h"

#include "constants.h"

class Sound
{
    public:
        Sound( android_app* ANDROID_APP );
        virtual ~Sound();
        void play( SoundEffect SOUND_EFFECT );
        void update();
        
    private:
        CkBank*  bank_banjo;
        CkBank*  bank_barn;
        CkSound* sound_banjo;
        CkSound* sound_barn;
        
        void dispose();
        void initialize( android_app* ANDROID_APP );
};

#endif /* SOUND_H */

