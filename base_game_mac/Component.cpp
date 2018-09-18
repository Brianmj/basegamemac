//
//  Component.cpp
//  base_game_mac
//
//  Created by Brian Jones on 8/26/18.
//  Copyright © 2018 Brian Jones. All rights reserved.
//

#include "Component.hpp"

Component::Component(std::weak_ptr<Actor> owner_, int update_order_):
owner(owner_),
update_order(update_order_)
{
    
}

Component::~Component() {
    
}

// virtual function meant to be overriden by derived classes
void Component::update(float delta_time) {
    
}
