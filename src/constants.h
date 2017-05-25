#ifndef CONSTANTS_H
#define CONSTANTS_H

// Colors                           A    R    G    B
#define COLOR_TRANSPARENT SColor(   0,   0,   0,   0 )
#define COLOR_BLACK       SColor( 255,   0,   0,   0 )
#define COLOR_WHITE       SColor( 255, 255, 255, 255 )
#define COLOR_RED         SColor( 255, 255,   0,   0 )
#define COLOR_ORANGE      SColor( 255, 255, 127,   0 )
#define COLOR_YELLOW      SColor( 255, 255, 255,   0 )
#define COLOR_GREEN       SColor( 255,   0, 255,   0 )
#define COLOR_BLUE        SColor( 255,   0,   0, 255 )
#define COLOR_PURPLE      SColor( 255, 127,   0, 255 )
#define COLOR_PINK        SColor( 255, 255,   0, 255 )
#define COLOR_GRAY        SColor( 255, 127, 127, 127 )
#define COLOR_DKGRAY      SColor( 255,  63,  63,  63 )
#define COLOR_BROWN       SColor( 255, 127,  63,   0 )
#define COLOR_DEVGRAY     SColor( 255,  55,  57,  54 )

// Files - Assets - Fonts
#define FONT_24 "font_comic_24.xml"
#define FONT_36 "font_comic_36.xml"
#define FONT_48 "font_comic_48.xml"

// Files - Assets - Images
#define IMAGE_BACKGROUND "background.png"
#define IMAGE_TILE       "tile.png"

// Files - Assets - Meshes
#define TILE_PLANE    "plane_256x256.3ds"
#define DISPLAY_PLANE "plane_1920x1200.3ds"

// Graphics Properties
#define DRIVER_TYPE    EDT_OGLES1
#define SCREEN_WIDTH   0
#define SCREEN_HEIGHT  0
#define SCREEN_SIZE    dimension2d<u32>( SCREEN_WIDTH, SCREEN_HEIGHT )
#define BIT_DEPTH      24
#define ANTI_ALIASING  0

// Hidden Object - Enumeration
enum HiddenObject
{
    CAT,
    DOG,
    DUCK,
    HORSE,
    PIG,
    TOTAL_OBJECTS
};

// Hidden Object - Image Files
const static char* OBJECT_IMAGE[] =
{
    "cat.png",
    "dog.png",
    "duck.png",
    "horse.png",
    "pig.png"
};

// Misc Settings
#define LIGHT_RADIUS 3000

// Selection State - Enumeration
enum SelectionState
{
    NONE,
    ONE_TILE,
    TWO_TILES,
    LOCKED
};

// Strings
#define TEXT_EXIT L"Exit"

// Tile State - Enumeration
enum TileState
{
    ENABLED,
    DISABLED
};

// Tile Values
#define TILE_COLUMNS      5
#define TILE_ROWS         2
#define TILE_X_OFFSET   320.0
#define TILE_X_START   -640.0
#define TILE_Y_OFFSET   400.0
#define TILE_Y_START    280.0
#define TOTAL_TILES      10

// Widgets - Buttons
#define BUTTON_EXIT 99

// XY Values
#define EXIT_BUTTON_XY  800.0, -440.0

// Z Values
#define DISPLAY_PLANE_Z  826.0
#define MAX_Z           1000.0
#define TEXT_Z          DISPLAY_PLANE_Z - 2.0
#define TILE_Z          DISPLAY_PLANE_Z - 1.0
#define Z_OFFSET_1_250   199.0
#define Z_OFFSET_1_333   165.0
#define Z_OFFSET_1_600     0.0
#define Z_OFFSET_1_777     0.0

#endif /* CONSTANTS_H */
