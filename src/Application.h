#ifndef APPLICATION_H
#define APPLICATION_H

#include <android_native_app_glue.h>
#include <irrlicht.h>

#include "constants.h"
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
        IGUIButton*       button_exit;
        ICameraSceneNode* camera;
        SColor*           color_background;
        SColor*           color_white;
        dimension2d<u32>* dimension_screen;
        IGUIFont*         font_main;
        IGUIEnvironment*  gui_environment;
        ITexture*         textures_hidden[OBJECT_TOTAL];
        IrrlichtDevice*   irrlicht_device;
        ILightSceneNode*  light;
        ANativeWindow*    native_window;
        IMeshSceneNode*   node_display_plane;
        ISceneManager*    scene_manager;        
        s32               screen_height;
        s32               screen_width;
        u32               selection_state;
        ITexture*         texture_background;
        ITexture*         texture_tile;
        array<Tile*>      tiles;
        bool              touch_held_down;
        IVideoDriver*     video_driver;
        f32               z_offset;
        
        void exit();
        void initialize( android_app* ANDROID_APP );
        void initialize_assets();
        void initialize_camera();
        void initialize_display();
        void initialize_fonts();
        void initialize_irrlicht( SIrrlichtCreationParameters* PARAMETERS );
        void initialize_tiles();
        void initialize_values();
        void initialize_widgets();
        void run();
        void shuffle( u32 ARRAY[], u32 SIZE );
};

#endif /* APPLICATION_H */
