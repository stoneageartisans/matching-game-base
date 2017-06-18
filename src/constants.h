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

// Graphics Properties
#define DRIVER_TYPE    EDT_OGLES1
#define SCREEN_WIDTH   0
#define SCREEN_HEIGHT  0
#define SCREEN_SIZE    dimension2d<u32>( SCREEN_WIDTH, SCREEN_HEIGHT )
#define BIT_DEPTH      24
#define ANTI_ALIASING  0

// Files - Assets - Meshes
#define MESH_BACKGROUND "plane_1920x1200.3ds"
#define MESH_TILE       "plane_256x256.3ds"

// Themes
#define FARM   0
#define SPACE  1
#define THEMES 2

// Misc Settings & Values
#define LIGHT_RADIUS   3000
#define COMPARE_DELAY  2000
#define NO_ID            -1
#define OBJECT_TOTAL      5
#define WIN_DELAY      3000

// Background Image Files
const static char* IMAGES_BACKGROUND[] =
{
    "pasture.png", // FARM Theme
    "space.png"    // SPACE Theme
};

// Tile Image Files
const static char* IMAGES_TILE[] =
{
    "barn.png",    // FARM Theme
    "asteroid.png" // SPACE Theme
};

// Completed Sound Files
const static char* SOUNDS_COMPLETED[] =
{
    "fiddle.ckb", // FARM Theme
    "2001.ckb"    // SPACE Theme
};

// No Match Sound Files
const static char* SOUNDS_NO_MATCH[] =
{
    "banjo.ckb", // FARM Theme
    "klaxon.ckb" // SPACE Theme
};

// Select Tile Sound Files
const static char* SOUNDS_SELECT_TILE[] =
{
    "barn.ckb", // FARM Theme
    "laser.ckb" // SPACE Theme
};

// Hidden Object Image Files
const static char* OBJECT_IMAGES[THEMES][OBJECT_TOTAL] =
{
    {   // FARM Theme
        "cat.png",
        "dog.png",
        "duck.png",
        "horse.png",
        "pig.png"
    },
    {   // SPACE Theme
        "planet.png",
        "rocket.png",
        "satellite.png",
        "astronaut.png",
        "alien.png"
    }
};

// Hidden Object Sound Names
const static char* OBJECT_NAMES[THEMES][OBJECT_TOTAL] =
{
    {   // FARM Theme
        "cat",
        "dog",
        "duck",
        "horse",
        "pig"
    },
    {   // SPACE Theme
        "planet",
        "rocket",
        "satellite",
        "astronaut",
        "alien"
    }
};

// Hidden Object Sound Files
const static char* OBJECT_SOUNDS[THEMES][OBJECT_TOTAL] =
{
    {   // FARM Theme
        "cat.ckb",
        "dog.ckb",
        "duck.ckb",
        "horse.ckb",
        "pig.ckb"
    },
    {   // SPACE Theme
        "planet.ckb",
        "rocket.ckb",
        "satellite.ckb",
        "astronaut.ckb",
        "alien.ckb"
    }
};

// Selection States
#define NO_TILES  0
#define ONE_TILE  1
#define TWO_TILES 2
#define LOCKED    3

// Selections
#define FIRST  0
#define SECOND 1

// Sound Effects - Enumeration
enum SoundEffect
{
    SELECT_TILE,
    NO_MATCH,
    GOT_MATCH,
    COMPLETED
};

// Tile State - Enumeration
enum TileState
{
    ENABLED,
    DISABLED
};

// Tile Values
#define TILE_BUTTON_HEIGHT  80
#define TILE_BUTTON_WIDTH   80
#define TILE_COLUMNS         5
#define TILE_ROWS            2
#define TILE_X_OFFSET      320.0
#define TILE_X_START      -640.0
#define TILE_Y_OFFSET      400.0
#define TILE_Y_START       200.0
#define TOTAL_TILES         10

// XY Values
#define EXIT_BUTTON_XY  800.0, -440.0

// Z Values
#define BACKGROUND_Z    826.0
#define MAX_Z           1000.0
#define TEXT_Z          BACKGROUND_Z - 2.0
#define TILE_Z          BACKGROUND_Z - 1.0
#define Z_OFFSET_1_250   199.0
#define Z_OFFSET_1_333   165.0
#define Z_OFFSET_1_600     0.0
#define Z_OFFSET_1_777     0.0

#endif /* CONSTANTS_H */
