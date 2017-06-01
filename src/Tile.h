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
        Tile( u32 ID,
              IMeshSceneNode* NODE,
              IParticleSystemSceneNode* PARTICLE_NODE,
              u32 HIDDEN_OBJECT );
        virtual ~Tile();
        u32 get_id();
        IGUIButton* get_button();
        u32 get_hidden_object();
        IMeshSceneNode* get_node();
        TileState get_state();
        void reveal_object( ITexture* TEXTURE );
        void set_button( IGUIButton* BUTTON );
        void set_hidden_object( u32 HIDDEN_OBJECT );
        void set_node( IMeshSceneNode* NODE );
        void set_state( TileState TILE_STATE );
        
    private:
        IGUIButton*               button;
        u32                       hidden_object;
        u32                       id;
        IMeshSceneNode*           node;
        IParticleSystemSceneNode* particle_node;
        TileState                 state;
        
        void initialize( u32 ID,
                         IMeshSceneNode* NODE,
                         IParticleSystemSceneNode* PARTICLE_NODE,
                         u32 HIDDEN_OBJECT );
};

#endif /* TILE_H */

