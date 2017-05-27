#include "Application.h"

/*
 * Public Methods
 */

Application::Application( android_app* ANDROID_APP )
{
    initialize( ANDROID_APP );
    run();
}

Application::~Application()
{
    irrlicht_device->drop();
}

bool Application::OnEvent( const SEvent& EVENT )
{
    bool was_handled = false;
    
    switch( EVENT.EventType )
    {
        case EET_GUI_EVENT:
            switch( EVENT.GUIEvent.EventType )
            {
                case EGET_BUTTON_CLICKED:
                    s32 button_id = EVENT.GUIEvent.Caller->getID();
                    if( button_id == BUTTON_EXIT )
                    {
                        exit();
                        was_handled = true;
                    }
                    if( selection_state < TWO_TILES )
                    {
                        if( ( button_id > NO_ID ) && ( button_id < TOTAL_TILES ) )
                        {
                            Tile* tile = tiles[button_id];
                            tile->set_state( DISABLED );
                            tile->reveal_object( textures_hidden[tile->get_hidden_object()] );
                            selections[selection_state] = button_id;
                            selection_state ++;
                            was_handled = true;
                            if( selection_state == TWO_TILES )
                            {
                                check_for_match();
                            }
                        }
                    }
                    break;                    
            }
            break;
        case EET_TOUCH_INPUT_EVENT:
            // Simulate a mouse event
            SEvent event;
            event.EventType = EET_MOUSE_INPUT_EVENT;
            event.MouseInput.X = EVENT.TouchInput.X;
            event.MouseInput.Y = EVENT.TouchInput.Y;
            switch( EVENT.TouchInput.Event )
            {
                case ETIE_PRESSED_DOWN:
                    event.MouseInput.Event = EMIE_LMOUSE_PRESSED_DOWN;                    
                    touch_held_down = true;
                    irrlicht_device->postEventFromUser( event );
                    was_handled = true;
                    break;
                case ETIE_MOVED:
                    event.MouseInput.Event = EMIE_MOUSE_MOVED;
                    if( touch_held_down )
                    {
                        event.MouseInput.ButtonStates = EMBSM_LEFT;
                    }
                    irrlicht_device->postEventFromUser( event );
                    was_handled = true;
                    break;
                case ETIE_LEFT_UP:
                    event.MouseInput.Event = EMIE_LMOUSE_LEFT_UP;
                    touch_held_down = false;
                    irrlicht_device->postEventFromUser( event );
                    was_handled = true;
                    break;
            }
            break;
    }
    
    return was_handled;
}

/*
 * Private Methods
 */

void Application::check_for_match()
{
    Tile* selected_tile_1 = tiles[selections[FIRST]];
    Tile* selected_tile_2 = tiles[selections[SECOND]];
    
    
    if( selected_tile_1->get_hidden_object() == selected_tile_2->get_hidden_object() )
    {
        matches ++;
        if( matches == OBJECT_TOTAL )
        {
            reset_game();
        }
    }
    else
    {
        selected_tile_1->get_node()->setMaterialTexture( 0, texture_tile );
        selected_tile_2->get_node()->setMaterialTexture( 0, texture_tile );
        
        selected_tile_1->set_state( ENABLED );
        selected_tile_2->set_state( ENABLED );
    }
    
    selections[FIRST] = NO_ID;
    selections[SECOND] = NO_ID;
    selection_state = NO_TILES;
}

void Application::exit()
{
    irrlicht_device->setEventReceiver( 0 );
    irrlicht_device->closeDevice();
    irrlicht_device->run();
}

void Application::initialize( android_app* ANDROID_APP )
{
	SIrrlichtCreationParameters* parameters = new SIrrlichtCreationParameters();
	parameters->DriverType = DRIVER_TYPE;
	parameters->Bits = BIT_DEPTH;
	parameters->AntiAlias = ANTI_ALIASING;
    parameters->WindowSize = SCREEN_SIZE;
    parameters->PrivateData = ANDROID_APP;
    
    initialize_irrlicht( parameters );
    initialize_camera();
    initialize_values();
    initialize_assets();
    initialize_fonts();
    initialize_display();
    initialize_tiles();
    initialize_widgets();
}

void Application::initialize_assets()
{
    video_driver->setTextureCreationFlag( ETCF_CREATE_MIP_MAPS, false );
    
    texture_background = video_driver->getTexture( IMAGE_BACKGROUND );
    texture_tile = video_driver->getTexture( IMAGE_TILE );
    
    u32 total = ( u32 ) OBJECT_TOTAL;
    for( u32 i = 0; i < total; i ++ )
    {
        textures_hidden[i] = video_driver->getTexture( OBJECT_IMAGES[i] );
    }
}

void Application::initialize_camera()
{
    // Lights...
    light = scene_manager->addLightSceneNode();
    light->setLightType( ELT_POINT );
    light->setRadius( LIGHT_RADIUS );
    
    // Camera...
    camera = scene_manager->addCameraSceneNode();
    camera->setFarValue( MAX_Z );
    camera->setPosition( vector3df( 0, 0, 0 ) );
    camera->setTarget( vector3df( 0, 0, 1 ) );
    
    // ACTION!
}

void Application::initialize_display()
{
    z_offset = 0.0;
    
    f32 screen_ratio = (f32) ( (f32) screen_width / (f32) screen_height );
    
    if( ( screen_ratio >= 1 ) && ( screen_ratio < 1.3 ) )
    {
        z_offset = Z_OFFSET_1_250;
    }
    else if( ( screen_ratio >= 1.3 ) && ( screen_ratio < 1.47 ) )
    {
        z_offset = Z_OFFSET_1_333;
    }
    else if( ( screen_ratio >= 1.47 ) && ( screen_ratio < 1.69 ) )
    {
        z_offset = Z_OFFSET_1_600;
    }
    else if( ( screen_ratio >= 1.69 ) && ( screen_ratio < 1.86 ) )
    {
        z_offset = Z_OFFSET_1_777;
    }
    
    node_display_plane = scene_manager->addMeshSceneNode( scene_manager->getMesh( DISPLAY_PLANE ) );
    node_display_plane->setMaterialFlag( EMF_LIGHTING, true );
    node_display_plane->setPosition( vector3df( 0, 0, ( DISPLAY_PLANE_Z + z_offset ) ) );
    node_display_plane->setMaterialTexture( 0, texture_background );
}

void Application::initialize_fonts()
{
    s32 screen_diagonal = squareroot( ( screen_width * screen_width ) + ( screen_height * screen_height ) );
    
    if( screen_diagonal < 1200 )
    {
        font_main = gui_environment->getFont( FONT_24 );
    }
    else if( screen_diagonal > 1800 )
    {
        font_main = gui_environment->getFont( FONT_36 );
    }
    else
    {
        font_main = gui_environment->getFont( FONT_48 );
    }
    
    IGUISkin* skin = gui_environment->getSkin();
    
    skin->setFont( font_main );
    skin->setColor( EGDC_BUTTON_TEXT, *color_white );
}

void Application::initialize_irrlicht( SIrrlichtCreationParameters* PARAMETERS )
{
    irrlicht_device = createDeviceEx( *PARAMETERS );
    irrlicht_device->setEventReceiver( this );
    
    video_driver = irrlicht_device->getVideoDriver();
    scene_manager = irrlicht_device->getSceneManager();
    gui_environment = irrlicht_device->getGUIEnvironment();
    
    screen_width = video_driver->getScreenSize().Width;
    screen_height = video_driver->getScreenSize().Height;
}

void Application::initialize_tiles()
{
    u32 hidden_objects[TOTAL_TILES];
    
    for( u32 i = 0, obj = 0; i < TOTAL_TILES; i ++ )
    {
        hidden_objects[i] = obj;
        obj ++;
        if( obj == OBJECT_TOTAL )
        {
            obj = 0;
        }
    }
    
    shuffle( hidden_objects, TOTAL_TILES );
    
    IAnimatedMesh* mesh = scene_manager->getMesh( TILE_PLANE );
    
    u32 i = 0;
    f32 y = TILE_Y_START;
    
    for( u32 row = 0; row < TILE_ROWS; row ++ )
    {
        f32 x = TILE_X_START;

        for( u32 column = 0; column < TILE_COLUMNS; column ++ )
        {
            tiles.insert( new Tile( i,
                                    scene_manager->addMeshSceneNode( mesh,
                                                                     0,
                                                                     i,
                                                                     vector3df( x, y, ( TILE_Z + z_offset ) ),
                                                                     vector3df( 0, 0, 180.0 ) ), // Blender flipped the .3ds z-axis
                                    hidden_objects[i] ),
                          i ); 
            tiles[i]->get_node()->setMaterialType( EMT_TRANSPARENT_ALPHA_CHANNEL );
            tiles[i]->get_node()->setMaterialFlag( EMF_LIGHTING, true );
            tiles[i]->get_node()->setMaterialTexture( 0, texture_tile );
            
            i ++;
            
            x = x + TILE_X_OFFSET;
        }
        
        y = y - TILE_Y_OFFSET;
    }
}

void Application::initialize_values()
{
    color_background = new COLOR_BLACK;
    color_white = new COLOR_WHITE;
    touch_held_down = false;
    matches = 0;
    selection_state = NO_TILES;
    selections[FIRST] = NO_ID;
    selections[SECOND] = NO_ID;
}

void Application::initialize_widgets()
{
    ISceneCollisionManager* collision_manager = scene_manager->getSceneCollisionManager();
    
    u32 button_width;
    u32 button_height;    
    position2d<s32> screen_coordinates;
    
    // The Exit Button
    button_width = font_main->getDimension( L"Exit" ).Width * 2;
    button_height = font_main->getDimension( L"Exit" ).Height * 2;
    screen_coordinates = collision_manager->getScreenCoordinatesFrom3DPosition( vector3df( EXIT_BUTTON_XY, TILE_Z + z_offset ) );
    screen_coordinates.X = screen_coordinates.X - ( button_width / 2 );
    screen_coordinates.Y = screen_coordinates.Y - ( button_height / 2 );
    button_exit = gui_environment->addButton( rect<s32>( screen_coordinates,
                                                         dimension2d<u32>( button_width, button_height ) ),
                                              0,
                                              BUTTON_EXIT,
                                              TEXT_EXIT );
    button_exit->setDrawBorder( false );
    
    // The Tile Buttons
    button_width = TILE_BUTTON_WIDTH;
    button_height = TILE_BUTTON_HEIGHT;
    for( u32 i = 0; i < TOTAL_TILES; i ++ )
    {
        screen_coordinates = collision_manager->getScreenCoordinatesFrom3DPosition( tiles[i]->get_node()->getPosition() );
        screen_coordinates.X = screen_coordinates.X - ( button_width / 2 );
        screen_coordinates.Y = screen_coordinates.Y - ( button_height / 2 );
        tiles[i]->set_button( gui_environment->addButton( rect<s32>( screen_coordinates,
                                                                     dimension2d<u32>( button_width, button_height ) ),
                                                          0,
                                                          i,
                                                          L"" ) );
        tiles[i]->get_button()->setDrawBorder( false );
    }    
}

void Application::reset_game()
{
    matches = 0;
    selection_state = NO_TILES;
    selections[FIRST] = NO_ID;
    selections[SECOND] = NO_ID;
    
    for( u32 i = 0; i < TOTAL_TILES; i ++ )
    {
        tiles[i]->get_node()->setMaterialTexture( 0, texture_tile );
        tiles[i]->set_state( ENABLED );
    }
}

void Application::run()
{    
    while( irrlicht_device->run() )
    {
        video_driver->beginScene( true, true, *color_background );
        scene_manager->drawAll();
        gui_environment->drawAll();
        video_driver->endScene();
    }
}

void Application::shuffle( u32 ARRAY[], u32 SIZE )
{
    //srand( time( NULL ) );
 
    for( u32 i = SIZE - 1; i > 0; i -- )
    {
        u32 r = rand() % ( i + 1 ); 
        int temp = ARRAY[i];
        ARRAY[i] = ARRAY[r];
        ARRAY[r] = temp;
    }
}
