#include "android_tools.h"
#include "android/window.h"

#include "Application.h"

void android_main( android_app* ANDROID_APP )
{
    app_dummy();
    
    //srand( time(NULL) );
    
    new Application( ANDROID_APP );
}
