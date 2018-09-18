//
//  SpriteComponent.h
//  base_game_mac
//
//  Created by Brian Jones on 9/18/18.
//  Copyright © 2018 Brian Jones. All rights reserved.
//

#ifndef SpriteComponent_h
#define SpriteComponent_h

#include <memory>
#include <SDL2/SDL.h>
#include "Component.hpp"


class Actor;
using TEXTURE_SP = std::shared_ptr<SDL_Texture>;

class SpriteComponent : public Component {
    
    TEXTURE_SP texture;
    int draw_order;
    int tex_width;
    int tex_height;
    
public:
    SpriteComponent(std::weak_ptr<Actor> owner_, int draw_order_ = 100);
    ~SpriteComponent();
    
    virtual void draw(SDL_Renderer *renderer);
    virtual void set_texture(TEXTURE_SP new_texture);
    
    int get_draw_order() const { return draw_order; }
    int get_tex_width() const { return tex_width; }
    int get_tex_height() const { return tex_height;}
    
};

#endif /* SpriteComponent_h */
