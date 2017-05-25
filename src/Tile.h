#ifndef TILE_H
#define TILE_H

#include <irrlicht.h>

#include "constants.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Tile
{
    public:
        Tile( u32 ID, IMeshSceneNode* NODE, HiddenObject HIDDEN_OBJECT );
        virtual ~Tile();
        u32 get_id();
        HiddenObject get_hidden_object();
        IMeshSceneNode* get_node();
        TileState get_state();
        void set_hidden_object( HiddenObject HIDDEN_OBJECT );
        void set_node( IMeshSceneNode* NODE );
        void set_state( TileState TILE_STATE );
        
    private:
        HiddenObject    hidden_object;
        u32             id;
        IMeshSceneNode* node;
        TileState       state;
        
        void initialize( u32 ID, IMeshSceneNode* NODE, HiddenObject HIDDEN_OBJECT );
};

#endif /* TILE_H */

