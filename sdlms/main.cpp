#include "Systems/Systems.h"
#include "Core/Core.h"
#include "Entities/Entities.h"
#include "PlayerSkill/PlayerSkill.h"
#include "UI/UI.h"
#include "Resources/Wz.h"
#include "entt/entt.hpp"

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int width = 1366;
int height = 768;

SDL_AppResult SDL_AppIterate(void *appstate)
{
    Window::tick_delta_time();
    Window::clear();
    cooldown_run();
    animate_run();
    attack_run();
    player_statemachine_run();
    mob_statemachine_run();
    drop_run();
    ball_run();
    ui_run();
    world_run();
    camera_run();
    render_run();
    Window::update();
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    if (argc == 3)
    {
        width = SDL_atoi(argv[1]);
        height = SDL_atoi(argv[2]);
    }

    Camera::w = width;
    Camera::h = height;

    Wz::init("./Data/");
    Window::create_window("sdlMS", width, height);
    Character::init();
    Tomb::init();
    Damage::init();
    Cursor::init();
    Sound::init();
    Drop::init();
    PlayerSkill::init();

    // World::load_map(222020111);
    World::load_map(100010000);

    Player::ent = World::registry->create();
    load_character(0, 0, true, Player::ent);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    return (event->type == SDL_EVENT_QUIT) ? SDL_APP_SUCCESS : SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    SDL_Quit();
}