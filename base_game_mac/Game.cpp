//
//  game.cpp
//  gameprojmac
//
//  Created by Brian Jones on 8/25/18.
//  Copyright © 2018 Brian Jones. All rights reserved.
//

#include "Game.hpp"
#include <SDL2_image/SDL_image.h>



Game::Game() :
window(nullptr, SDL_DestroyWindow),
renderer(nullptr, SDL_DestroyRenderer),
ticks_count(0),
is_running(true),
updating_actors(false)
{
}

bool Game::initialize() {
    int result = SDL_Init(SDL_INIT_VIDEO);
    
    if (0 != result) {
        SDL_Log("Unable to initialize sdl: %s", SDL_GetError());
        
        return false;
    }
    
    int img_init = IMG_Init(IMG_INIT_PNG);
    
    if(!(img_init & IMG_INIT_PNG)){
        // was unable to initialize the SDL Image library
        SDL_Log("Unable to initialize the image library: %s", SDL_GetError());
        
        return false;
    }
    
    window = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>(
                                                                       SDL_CreateWindow("Game Programming in C++ (Chapter 1)",
                                                                                        100,
                                                                                        100,
                                                                                        1024,
                                                                                        768,
                                                                                        0),
                                                                       SDL_DestroyWindow);
    
    if (!window)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        
        return false;
    }
    
    renderer = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>(
                                                                             SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
                                                                             SDL_DestroyRenderer
                                                                             );
    
    if (!renderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        
        return false;
    }
    
    
    
    ticks_count = SDL_GetTicks();
    
    return true;
}

void Game::run_loop() {
    while (is_running) {
        process_input();
        update_game();
        generate_output();
    }
}

void Game::shutdown() {
    unload_data();              // free the memory, unload all data here
    IMG_Quit();
    window.reset(nullptr);    // close the window
    SDL_Quit();                // shutdown sdl
}

void Game::add_actor(std::shared_ptr<Actor> actor){
    if(updating_actors) {
        pending_actors.emplace_back(actor);
    }else {
        actors.emplace_back(actor);
    }
}

void Game::remove_actor(std::shared_ptr<Actor> actor){
    // is it in pending actors
    auto pending_iter = std::find(std::begin(pending_actors), std::end(pending_actors), actor);
    
    if(std::end(pending_actors) != pending_iter){
        std::iter_swap(pending_iter, std::end(pending_actors) - 1);
        pending_actors.pop_back();
    }
    
    
    auto iter = std::find(std::begin(actors), std::end(actors), actor);
    
    if(std::end(actors) != iter) {
        std::iter_swap(iter, std::end(actors) -1);
        actors.pop_back();
    }
}

void Game::process_input() {
    SDL_Event event;
    
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: is_running = false; break;
                
        }
        
    }
    
    const Uint8 *scan_keys = SDL_GetKeyboardState(nullptr);
    
    if (scan_keys[SDL_SCANCODE_ESCAPE])
        is_running = false;
}

void Game::update_game() {
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), ticks_count + 16));
    
    float delta_time = (SDL_GetTicks() - ticks_count) / 1000.0f;
    
    delta_time = std::min(delta_time, 0.5f);
    
    ticks_count = SDL_GetTicks();
    
    updating_actors = true;
    for(auto &actor : actors) {
        actor->update(delta_time);
    }
    updating_actors = false;
    
    for(auto pending_actor : pending_actors) {
        actors.emplace_back(pending_actor);
    }
    
    pending_actors.clear();
    
    // erase remove idiom   // get rid of the dead actors
    actors.erase(std::remove_if(std::begin(actors), std::end(actors), [](auto &sp){
        return sp->get_state() == Actor::State::EDead;
    }), std::end(actors));
}

void Game::generate_output() {
    SDL_SetRenderDrawColor(renderer.get(), 0, 170, 255, 255);
    SDL_RenderClear(renderer.get());
    
    
    SDL_RenderPresent(renderer.get());
    
}

void Game::load_data() {
    
}

void Game::unload_data() {
    if(!actors.empty())
        actors.clear();
    
}

TEXTURE_SP Game::get_texture(std::string texture_name) {
    auto iter = textures.find(texture_name);
    
    if(std::end(textures) != iter) {
        // we have the texture
        auto found_texture = iter->second;
        
        return found_texture;
    }
    
    // no texture found named "texture_name", try and load it
    auto surface = std::shared_ptr<SDL_Surface>(IMG_Load(texture_name.c_str()),
                                                 SDL_FreeSurface);
    
    if(nullptr == surface) {
        SDL_Log("Could not load image file by name of: %s", texture_name.c_str());
        return nullptr;
    }
    
    // success
    auto tex = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(renderer.get(), surface.get()), SDL_DestroyTexture);
    
    // add the new texture to the map
    textures.emplace(texture_name, tex);
    
    return tex;
}

