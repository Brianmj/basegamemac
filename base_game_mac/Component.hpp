//
//  Component.hpp
//  base_game_mac
//
//  Created by Brian Jones on 8/26/18.
//  Copyright © 2018 Brian Jones. All rights reserved.
//

#ifndef Component_h
#define Component_h

#include <memory>
#include "Actor.hpp"

class Component {
    
public:
    Component(std::weak_ptr<Actor> owner_, int update_order_ = 100);
    
    virtual ~Component();
    
    virtual void update(float delta_time);
    
    int get_update_order() const { return update_order; }
    
    std::shared_ptr<Actor> get_owner() { return owner.lock(); }
    
private:
    std::weak_ptr<Actor> owner;
    int update_order;
};


#endif /* Component_h */
