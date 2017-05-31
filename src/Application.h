#ifndef APPLICATION_H
#define APPLICATION_H

#include <android_native_app_glue.h>
#include <irrlicht.h>

#include "constants.h"
#include "Sound.h"
#include "Tile.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Application : public IEventReceiver
{
    public:
        Application( android_app* ANDROID_APP );
        ~Application();
        bool OnEvent( const SEvent& EVENT );
        
    private:
        ICameraSceneNode* camera;
        SColor*           color_background;
        SColor*           color_white;
        dimension2d<u32>* dimension_screen;
        IGUIFont*         font_main;
        IGUIEnvironment*  gui_environment;
        ITexture*         textures_hidden[OBJECT_TOTAL];
        IrrlichtDevice*   irrlicht_device;
        ILightSceneNode*  light;
        u32               matches;
        ANativeWindow*    native_window;
        IMeshSceneNode*   node_display_plane;
        ISceneManager*    scene_manager;        
        s32               screen_height;
        s32               screen_width;
        u32               selection_state;
        u32               selection[2];
        Sound*            sound;
        ITexture*         texture_background;
        ITexture*         texture_tile;
        ITimer*           timer;
        array<Tile*>      tiles;
        u32               timer_delay;
        bool              timer_running;
        u32               timer_start;
        bool              touch_held_down;
        IVideoDriver*     video_driver;
        f32               z_offset;
        
        void check_for_match();
        void check_timer();
        void continue_round();
        void exit();
        void initialize( android_app* ANDROID_APP );
        void initialize_assets();
        void initialize_camera();
        void initialize_display();
        void initialize_fonts();
        void initialize_irrlicht( android_app* ANDROID_APP );
        void initialize_sound( android_app* ANDROID_APP );
        void initialize_tiles();
        void initialize_values();
        void initialize_widgets();
        void reset_game();
        void run();
        void shuffle( u32 ARRAY[], u32 SIZE );
        void start_timer( u32 DURATION );
        void stop_timer();
};

#endif /* APPLICATION_H */
