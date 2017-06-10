#include "tile.h"

/*
 * Public Methods
 */

Tile::Tile( u32 ID,
            IMeshSceneNode* NODE,
            IParticleSystemSceneNode* PARTICLE_NODE,
            u32 HIDDEN_OBJECT )
{
    initialize( ID, NODE, PARTICLE_NODE, HIDDEN_OBJECT );
}

Tile::~Tile()
{
    // TODO
}

IGUIButton* Tile::get_button()
{
    return button;
}

u32 Tile::get_id()
{
    return id;
}

u32 Tile::get_hidden_object()
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

void Tile::reveal_object( ITexture* TEXTURE )
{
    node->setMaterialTexture( 0, TEXTURE );
}

void Tile::set_button( IGUIButton* BUTTON )
{
    button = BUTTON;
}

void Tile::set_hidden_object( u32 HIDDEN_OBJECT )
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
    
    switch( state )
    {
        case ENABLED:
            button->setEnabled( true );
            break;
        case DISABLED:
            button->setEnabled( false );
            break;
    }
}

/*
 * Private Methods
 */

void Tile::initialize( u32 ID,
                       IMeshSceneNode* NODE,
                       IParticleSystemSceneNode* PARTICLE_NODE,
                       u32 HIDDEN_OBJECT )
{
    id = ID;
    node = NODE;
    particle_node = PARTICLE_NODE;
    hidden_object = HIDDEN_OBJECT;
    
    state = DISABLED;
    button = NULL;
    
    particle_node->setParent( node );
    particle_node->setEmitter( particle_node->createPointEmitter( vector3df( 0.0, 0.05, -0.05 ) ) );
}
