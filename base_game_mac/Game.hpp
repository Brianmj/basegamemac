//
//  game.hpp
//  gameprojmac
//
//  Created by Brian Jones on 8/25/18.
//  Copyright © 2018 Brian Jones. All rights reserved.
//

#ifndef game_h
#define game_h

#include <SDL2/SDL.h>
#include <memory>
#include <unordered_map>
#include "Actor.hpp"

using TEXTURE_SP = std::shared_ptr<SDL_Texture>;

class Game {
public:
    Game();
    
    bool initialize();
    void run_loop();
    void shutdown();
    
    void add_actor(std::shared_ptr<Actor> actor);
    void remove_actor(std::shared_ptr<Actor> actor);
    
private:
    void process_input();
    void update_game();
    void generate_output();
    void load_data();
    void unload_data();
    TEXTURE_SP get_texture(std::string texture_name);
    
private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;
    
    Uint32 ticks_count;
    bool is_running;
    bool updating_actors;
    
    // all the actors in the game
    std::vector<std::shared_ptr<Actor>> actors;
    
    // pending actors to be inserted
    std::vector<std::shared_ptr<Actor>> pending_actors;
    
    // a map of strings to shared_ptr SDL_Textures
    std::unordered_map<std::string, TEXTURE_SP> textures;
    
};

#endif /* game_h */
