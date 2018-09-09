//
//  Actor.cpp
//  base_game_mac
//
//  Created by Brian Jones on 8/26/18.
//  Copyright © 2018 Brian Jones. All rights reserved.
//

#include "Actor.hpp"
#include "Game.hpp"
#include "Component.hpp"
#include <algorithm>

Actor::Actor(Game *game_):
state(State::EActive),
position({0.0f, 0.0f}),
scale(1.0f),
rotation(0.0f),
components{},
game(game_)
{

}

Actor::~Actor() {
    
}

void Actor::update(float delta_time)
{
    if(State::EActive == state){
        update_components(delta_time);
        update_actor(delta_time);
    }
}

void Actor::update_components(float delta_time)
{
    for (auto &cp : components) {
        cp->update(delta_time);
    }
}

void Actor::update_actor(float delta_time)
{
    
}

void Actor::add_component(std::shared_ptr<Component> component){
    components.push_back(component);
    
    std::sort(components.begin(), components.end(), [](auto &ptr1, auto &ptr2) {
        return ptr1->get_update_order() < ptr2->get_update_order(); });
}

void Actor::remove_component(std::shared_ptr<Component> component) {
    auto iter = std::find(std::begin(components), std::end(components), component);
    
    if(std::end(components) != iter)
        components.erase(iter);
}
