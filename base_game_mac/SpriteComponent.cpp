//
//  SpriteComponent.cpp
//  base_game_mac
//
//  Created by Brian Jones on 9/18/18.
//  Copyright © 2018 Brian Jones. All rights reserved.
//

#include "SpriteComponent.h"
#include "Actor.hpp"
#include "Game.hpp"

SpriteComponent::SpriteComponent(std::weak_ptr<Actor> owner_, int draw_order_):
Component(owner_),
texture(nullptr),
draw_order(draw_order_),
tex_width(0),
tex_height(0) {
    owner_.lock()->get_game()->add_sprite(this);
}

SpriteComponent::~SpriteComponent() {
    get_owner()->get_game()->remove_sprite(this);
}

void SpriteComponent::draw(SDL_Renderer *renderer) {
    if(texture) {
        SDL_Rect r;
        r.w = static_cast<int>(tex_width *  get_owner()->get_scale());
        r.h = static_cast<int>(tex_height * get_owner()->get_scale());
        r.x = static_cast<int>(get_owner()->get_position().x - r.w / 2);
        
        
        SDL_RenderCopyEx(renderer,
                         texture.get(),
                         nullptr,       // draw the whole texture
                         &r,            // rect to draw onto
                         -knu::math::utility::radians_to_degrees(get_owner()->get_rotation()), nullptr,  // nullptr means center SDL_Point for rotation
                         SDL_FLIP_NONE);
    }
    
}

void SpriteComponent::set_texture(TEXTURE_SP new_texture) {
    texture = new_texture;
    
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &tex_width, &tex_height);
}

