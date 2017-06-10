#include "android_tools.h"
#include "android/window.h"

#include "application.h"

void android_main( android_app* ANDROID_APP )
{
    app_dummy();
    
    ( new Application( ANDROID_APP ) )->run();
}
