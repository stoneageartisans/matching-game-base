#include "android_tools.h"
#include "android/window.h"

#include "application.h"

void android_main( android_app* ANDROID_APP )
{
    Application( ANDROID_APP ).run();
}
