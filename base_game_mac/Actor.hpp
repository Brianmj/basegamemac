//
//  Actor.hpp
//  base_game_mac
//
//  Created by Brian Jones on 8/25/18.
//  Copyright © 2018 Brian Jones. All rights reserved.
//

#ifndef Actor_h
#define Actor_h

#include "Game.hpp"
#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <vector>
#include <memory>
#include "mathlibrary5.hpp"

// Forward declaration
class Component;

class Actor {
public:
    
    enum class State {
        EActive,
        EPaused,
        EDead,
    };
    
    Actor(Game *game);
    virtual ~Actor();
    
    // update function called fromt he game (not overridable)
    void update(float delta_time);
    
    // updates all the components attached to the actor (not overridable)
    void update_components(float delta_time);
    
    // any actor specific update code (overridable)
    virtual void update_actor(float delta_time);
    
    void add_component(Component *component);
    void remove_component(Component *component);
    
    /*
    template<typename T>
    void add_component() {
        auto iter = components.find(typeid(T));
        
        if(std::end(components) == iter){
            components[typeid(T)] = std::make_shared<T>();
        }
        
    }
    
    template<typename T>
    void remove_component() {
        auto iter = components.find(typeid(T));
        
        if(std::end(components) != iter) {
            // we have this component
            components.erase(iter);
        }
    }*/
    
private:
    
    //std::unordered_map<std::type_index, std::shared_ptr<void>> components;
    
    State state;
    
    // transform
    knu::math::Vec2<float>  position;       // center position of the actor
    float scale;            // uniform scale of the actor (1.0f for 100%)
    float rotation;         // rotation angle (in radians)
    std::vector<std::unique_ptr<Component>> components; // components held by this actor
    Game* game;
    
};


#endif /* Actor_h */
