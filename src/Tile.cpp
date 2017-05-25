#include "Tile.h"

/*
 * Public Methods
 */

Tile::Tile( u32 ID, IMeshSceneNode* NODE, HiddenObject HIDDEN_OBJECT )
{
    initialize( ID, NODE, HIDDEN_OBJECT );
}

Tile::~Tile()
{
    // TODO
}

u32 Tile::get_id()
{
    return id;
}

HiddenObject Tile::get_hidden_object()
{
    return hidden_object;
}

IMeshSceneNode* Tile::get_node()
{
    return node;
}

TileState Tile::get_state()
{
    return state;
}

void Tile::set_hidden_object( HiddenObject HIDDEN_OBJECT )
{
    hidden_object = HIDDEN_OBJECT;
}

void Tile::set_node( IMeshSceneNode* NODE )
{
    node = NODE;
}

void Tile::set_state( TileState TILE_STATE )
{
    state = TILE_STATE;
}

/*
 * Private Methods
 */

void Tile::initialize( u32 ID, IMeshSceneNode* NODE, HiddenObject HIDDEN_OBJECT )
{
    id = ID;
    node = NODE;
    hidden_object = HIDDEN_OBJECT;
    state = DISABLED;
}
