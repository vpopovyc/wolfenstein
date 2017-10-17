/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textured_ray->asting.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 16:51:39 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/19 18:52:52 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "thread_init.h"
#include "sounds/sounds.h"
#include <pthread.h>

void    create_appcore(t_appcore *appcore)
{
        // Game context init
    appcore->myGame = get_game(single_player, 1);
        // Map init
    ft_memcpy(appcore->myMap, appcore->myGame->map->world_map, map_height * map_width * sizeof(int));
        // SDL2
    appcore->mySDL2 = sdl2_init(WWIDTH, WHEIGTH);
        // Sprites
    appcore->mySprites = get_sprites(single_player, 1);
        // Textures load
    appcore->myTexture = load_textures();
        // Doors
    appcore->door = get_door(single_player, 1);
    set_doors_on_map(appcore->door, appcore->myMap);
        // Enemies
    appcore->enemies = get_enemies(single_player, 1);
}

void    create_worldrender(t_draw_world *worldrender)
{
    worldrender->ray = malloc(sizeof(t_ray_info));
    worldrender->mapped_ray = malloc(sizeof(t_ray_on_map));   
    worldrender->dda = malloc(sizeof(t_dda));
}

void    create_engine(t_engine *engine)
{
    t_appcore appcore;
    t_draw_world worldrender;

    create_appcore(&appcore);
    create_worldrender(&worldrender);
    engine->appcore = appcore;
    engine->worldrender = worldrender;
}

void    render_frame(t_appcore *appcore, t_draw_world *worldrender)
{
    register int             x;
    register int             xmax;
    register int             door_id;

    x = worldrender->render_range.x;
    xmax = worldrender->render_range.y;

    /*
    ** Particle-system calculation
    */

    procced_ps(appcore);

    /*
    ** Main loop
    */

    while (x < xmax)
    {
        /*
        ** create ray
        */

        set_ray_data(worldrender->ray, appcore, x);

        /*
        ** calculate step and initial side_dist
        */
        
        map_ray_to_world(worldrender->ray, worldrender->mapped_ray);

        /*
        ** DDA
        */

        run_dda(worldrender->ray, worldrender->mapped_ray, worldrender->dda, appcore);

        /*
        ** Worldaround
        */
        if (worldrender->dda->hit == 1 || worldrender->dda->door_hit) 
        {
            /*
            ** Texturing calculations
            */

            draw_world(appcore, worldrender, x, 0);
        }            

        /*
        ** Door texturing
        */

        if (worldrender->dda->hit == 2 || worldrender->dda->door_hit) 
        {
            while (stack_size(&(worldrender->dda->doors_stack)))
            {
                /*
                ** Pasrse door info and get back its index
                */

                door_id = parse_doors_stack(worldrender, appcore);

                /*
                ** Texturing calculations
                */

                draw_world(appcore, worldrender, x, door_id + 1);
            }
        }
        ++x;
    }
    /*
    ** Sprites
    */
        /*
        ** Sorting
        */

    sort_sprites(appcore->mySprites, appcore->myGame->pos);

        /*
        ** Drawing
        */

    draw_sprites(appcore->myGame, appcore->mySDL2, appcore->mySprites, appcore->myTexture);
    
    /*
    ** Particle-system draw
    */

    draw_ps(&appcore->ps_thread, appcore->mySDL2);

    /*
    ** Fresh frame
    */
}

void    set_render_range(t_draw_world *worldrender, int xmin, int xmax)
{
    worldrender->render_range.x = xmin;
    worldrender->render_range.y = xmax;
}

void    engine_execute(t_engine *engine)
{
    register t_appcore   *appcore = &engine->appcore;
    register t_draw_world *worldrender = &engine->worldrender;

    while (1)
    {

        SDL_UpdateTexture(appcore->mySDL2->texture, NULL, appcore->mySDL2->pixels, WWIDTH * sizeof(uint32_t));

        set_render_range(worldrender, 0, WWIDTH);

        render_frame(appcore, worldrender);

        SDL_RenderClear(appcore->mySDL2->renderer);
        SDL_RenderCopy(appcore->mySDL2->renderer, appcore->mySDL2->texture, NULL, NULL);
        SDL_RenderPresent(appcore->mySDL2->renderer);
        appcore->myGame->time.y = appcore->myGame->time.x;
        appcore->myGame->time.x = SDL_GetTicks();
        eventManagment(appcore->myGame, appcore->mySDL2, appcore->door, appcore->myMap);
    }
}

void    *music_thread_init(void *args)
{
    (void)args;
    while (1)
    {
        sound(OK);
    }
    pthread_exit(NULL);
}

void    turn_on_music(void)
{
    pthread_t music_thread;

    pthread_create(&music_thread, NULL, music_thread_init, NULL);
    pthread_detach(music_thread);
}

int     main(void)
{
    /*
    ** variables for inner whie loop 
    */
    time_t t;
    t_engine engine;

    srand((unsigned)time(&t));

    turn_on_music();

    create_engine(&engine);

    engine_execute(&engine);

    sdl2_release(engine.appcore.mySDL2);
    
    return (0);
}
