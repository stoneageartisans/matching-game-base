#include "application.h"

/*
 * Public Methods
 */

Application::Application( android_app* ANDROID_APP )
{
    initialize( ANDROID_APP );
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
                    if( selection_state < TWO_TILES )
                    {
                        if( ( button_id > NO_ID ) && ( button_id < TOTAL_TILES ) )
                        {
                            sound->play( SELECT_TILE );
                            tiles[button_id]->set_state( DISABLED );
                            tiles[button_id]->reveal_object( textures_hidden[tiles[button_id]->get_hidden_object()] );
                            selection[selection_state] = button_id;
                            selection_state ++;
                            if( selection_state == TWO_TILES )
                            {
                                check_for_match();
                            }
                            was_handled = true;
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

void Application::run()
{    
    while( irrlicht_device->run() )
    {
        video_driver->beginScene( true, true, color_background );
        scene_manager->drawAll();
        gui_environment->drawAll();
        video_driver->endScene();        
        if( timer_running )
        {
            check_timer();
        }
        irrlicht_device->yield();
        sound->update();
    }
    
    exit();
}

/*
 * Private Methods
 */

void Application::check_for_match()
{    
    if( tiles[selection[FIRST]]->get_hidden_object() == tiles[selection[SECOND]]->get_hidden_object() )
    {
        sound->play( GOT_MATCH, ( int ) tiles[selection[FIRST]]->get_hidden_object() );
        matches ++;
        if( matches == OBJECT_TOTAL )
        {
            start_timer( WIN_DELAY );    
            sound->play( COMPLETED );
        }
        else
        {
            selection[FIRST] = NO_ID;
            selection[SECOND] = NO_ID;
            selection_state = NO_TILES;
        }
    }
    else
    {
        start_timer( COMPARE_DELAY );
        sound->play( NO_MATCH );
    }
}

void Application::check_timer()
{
    if( timer_running )
    {
        if( ( timer->getRealTime() - timer_start ) > timer_delay )
        {
            stop_timer();
        }
    }
}

void Application::continue_round()
{
    tiles[selection[FIRST]]->get_node()->setMaterialTexture( 0, texture_tile );
    tiles[selection[SECOND]]->get_node()->setMaterialTexture( 0, texture_tile );

    tiles[selection[FIRST]]->set_state( ENABLED );
    tiles[selection[SECOND]]->set_state( ENABLED );
    
    selection_state = NO_TILES;
    
    selection[FIRST] = NO_ID;
    selection[SECOND] = NO_ID;
}

void Application::exit()
{
    irrlicht_device->setEventReceiver( 0 );
    irrlicht_device->closeDevice();
    irrlicht_device->run();
}

void Application::initialize( android_app* ANDROID_APP )
{
    initialize_irrlicht( ANDROID_APP );
    initialize_camera();
    initialize_values();
    initialize_assets();
    initialize_display();
    initialize_tiles();
    initialize_sound( ANDROID_APP );
    initialize_widgets();
}

void Application::initialize_assets()
{
    video_driver->setTextureCreationFlag( ETCF_CREATE_MIP_MAPS, false );
    
    texture_background = video_driver->getTexture( IMAGES_BACKGROUND[current_theme] );
    texture_tile = video_driver->getTexture( IMAGES_TILE[current_theme] );
    
    u32 total = ( u32 ) OBJECT_TOTAL;
    for( u32 i = 0; i < total; i ++ )
    {
        textures_hidden[i] = video_driver->getTexture( OBJECT_IMAGES[current_theme][i] );
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
    
    node_background = scene_manager->addMeshSceneNode( scene_manager->getMesh( MESH_BACKGROUND ) );
    node_background->setMaterialFlag( EMF_LIGHTING, true );
    node_background->setPosition( vector3df( 0, 0, ( BACKGROUND_Z + z_offset ) ) );
    node_background->setMaterialTexture( 0, texture_background );
}

void Application::initialize_irrlicht( android_app* ANDROID_APP )
{
    SIrrlichtCreationParameters parameters;
    
	parameters.DriverType = DRIVER_TYPE;
	parameters.Bits = BIT_DEPTH;
	parameters.AntiAlias = ANTI_ALIASING;
    parameters.WindowSize = SCREEN_SIZE;
    parameters.PrivateData = ANDROID_APP;
    
    irrlicht_device = createDeviceEx( parameters );
    irrlicht_device->setEventReceiver( this );
    
    video_driver = irrlicht_device->getVideoDriver();
    scene_manager = irrlicht_device->getSceneManager();
    gui_environment = irrlicht_device->getGUIEnvironment();
    
    screen_width = video_driver->getScreenSize().Width;
    screen_height = video_driver->getScreenSize().Height;
    
    timer = irrlicht_device->getTimer();
}

void Application::initialize_sound( android_app* ANDROID_APP )
{
    sound = new Sound( ANDROID_APP, current_theme );
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
    
    IAnimatedMesh* mesh = scene_manager->getMesh( MESH_TILE );
    
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
    color_background = COLOR_BLACK;
    color_white = COLOR_WHITE;
    current_theme = FARM;
    touch_held_down = false;
    matches = 0;
    selection_state = NO_TILES;
    selection[FIRST] = NO_ID;
    selection[SECOND] = NO_ID;
    timer_delay = 0;
    timer_running = false;    
    timer_start = 0;
}

void Application::initialize_widgets()
{
    ISceneCollisionManager* collision_manager = scene_manager->getSceneCollisionManager();
    
    u32 button_width;
    u32 button_height;    
    position2d<s32> screen_coordinates;
    
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
    selection[FIRST] = NO_ID;
    selection[SECOND] = NO_ID;
    
    for( u32 i = 0; i < TOTAL_TILES; i ++ )
    {
        tiles[i]->get_node()->setMaterialTexture( 0, texture_tile );
        tiles[i]->set_state( ENABLED );
    }
    
    u32 hidden_objects[TOTAL_TILES];
    
    for( u32 i = 0; i < TOTAL_TILES; i ++ )
    {
        hidden_objects[i] = tiles[i]->get_hidden_object();
    }
    
    shuffle( hidden_objects, TOTAL_TILES );
    
    for( u32 i = 0; i < TOTAL_TILES; i ++ )
    {
        tiles[i]->set_hidden_object( hidden_objects[i] );
    }
}

void Application::shuffle( u32 ARRAY[], u32 SIZE )
{
    srand( time( NULL ) );
 
    for( u32 i = SIZE - 1; i > 0; i -- )
    {
        u32 r = rand() % ( i + 1 ); 
        int temp = ARRAY[i];
        ARRAY[i] = ARRAY[r];
        ARRAY[r] = temp;
    }
}

void Application::start_timer( u32 DURATION )
{
    selection_state = LOCKED;
    timer_delay = DURATION;
    timer_start = timer->getRealTime();
    timer_running = true;
}

void Application::stop_timer()
{
    if( matches == OBJECT_TOTAL )
    {
        reset_game();
    }
    else
    {
        continue_round();
    }
    
    timer_running = false;
    timer_delay = 0;
    timer_start = 0;
}