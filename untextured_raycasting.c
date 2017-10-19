/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   untextured_raycasting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 16:51:39 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/08/16 17:36:08 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

#define mapWidth    24
#define mapHeight   24
#define texWidth    64
#define texHeight   64

#include <stdio.h>
int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


int     main(void)
{
    t_sdl2_tools    mySDL2;

    sdl2_initialize(&mySDL2, WWIDTH, WHEIGTH);
    
    /*
    ** x and y start position
    */
    t_doubleVec2    pos;
    pos.x = 22;
    pos.y = 12;
    /*
    ** initial direction vector
    */
    t_doubleVec2    dir;
    dir.x = -1;
    dir.y = 0;
    /*
    ** the 2d raycaster version of camera plane
    */
    t_doubleVec2    plane;
    plane.x = 0;
    plane.y = 0.66;
    /*
    ** time of current frame && time of previous frame
    */
    t_doubleVec2    myTime;
    myTime.x = 0;
    myTime.y = 0;
    double          frameTime;

    /*
    ** variables for inner while loop 
    */
    int             x; 

    t_doubleVec2    rayPos;
    t_doubleVec2    rayDir;
    double          cameraX;

    t_intVec2       map;
    t_intVec2       step;
    t_doubleVec2    sideDist;
    t_doubleVec2    deltaDist;
    
    double          perpWallDist;
    int             hit;
    int             side;

    int             lineHeight;
    int             drawStart;
    int             drawEnd;
    int             color;

    double          moveSpeed;
    double          rotSpeed;

    double          oldDirX;
    double          oldPlaneX;

    while (1)
    {
        x = 0;
        while (x < WWIDTH)
        {
            cameraX = 2 * x / (double)WWIDTH - 1; // ??
            rayPos.x = pos.x;
            rayPos.y = pos.y;
            rayDir.x = dir.x + plane.x * cameraX;
            rayDir.y = dir.y + plane.y * cameraX;

            map.x = (int)rayPos.x;
            map.y = (int)rayPos.y;

            deltaDist.x = sqrt(1 + (rayDir.y * rayDir.y) / (rayDir.x * rayDir.x));
            deltaDist.y = sqrt(1 + (rayDir.x * rayDir.x) / (rayDir.y * rayDir.y));

            /*
            ** calculate step and initial sideDist
            */
            if (rayDir.x < 0)
            {
                step.x = -1;
                sideDist.x = (rayPos.x - map.x) * deltaDist.x;
            }
            else
            {
                step.x = 1;
                sideDist.x = (map.x + 1.0 - rayPos.x) * deltaDist.x;
            }
            if (rayDir.y < 0)
            {
                step.y = -1;
                sideDist.y = (rayPos.y - map.y) * deltaDist.y;
            }
            else
            {
                step.y = 1;
                sideDist.y = (map.y + 1.0 - rayPos.y) * deltaDist.y;
            }
            /*
            ** DDA
            */
            hit = 0;

            while (hit == 0)
            {
                if (sideDist.x < sideDist.y)
                {
                    sideDist.x += deltaDist.x;
                    map.x += step.x;
                    side = 0;
                }
                else
                {
                    sideDist.y += deltaDist.y;
                    map.y += step.y;
                    side = 1;
                }
                if (worldMap[map.x][map.y] > 0)
                    hit = 1;
            }

            if (side == 0)
                perpWallDist = (map.x - rayPos.x + (1 - step.x) / 2) / rayDir.x;
            else
                perpWallDist = (map.y - rayPos.y + (1 - step.y) / 2) / rayDir.y;

            lineHeight = (int) (WHEIGTH / perpWallDist);
            
            drawStart = -lineHeight / 2 + WHEIGTH / 2;
            if (drawStart < 0)
                drawStart = 0;
            drawEnd = lineHeight / 2 + WHEIGTH / 2;
            if (drawEnd >= WHEIGTH)
                drawEnd = WHEIGTH - 1;

            switch (worldMap[map.x][map.y])
            {
                case 1: color = 0x820202; break;
                case 2: color = 0x028202; break;
                case 3: color = 0x020282; break;
                case 4: color = 0xababab; break;
                default: color = 0x828202; break;
            }

            if (side == 1) 
                color = color / 2;
            
            sdl2_plotVerLine(&mySDL2, x, 0, drawStart, 0x000000);
            sdl2_plotVerLine(&mySDL2, x, drawStart, drawEnd, color);
            sdl2_plotVerLine(&mySDL2, x, drawEnd, WHEIGTH, 0x000000);

            ++x;
        }

        myTime.y = myTime.x;
        myTime.x = SDL_GetTicks();
        frameTime = (myTime.x - myTime.y) / 1000.0;

        SDL_RenderPresent(mySDL2.renderer);

        moveSpeed = 0.500042;
        rotSpeed = 0.100042;
        while (1) {
            SDL_PollEvent(&mySDL2.event);
            if ((mySDL2.event.type == SDL_QUIT) || (mySDL2.event.key.keysym.sym == SDLK_ESCAPE))
                exit (0);
            if (mySDL2.event.type == SDL_KEYDOWN)
            {
                if (mySDL2.event.key.keysym.sym == SDLK_UP)
                {
                    if (worldMap[(int)(pos.x + dir.x * moveSpeed)][(int)(pos.y)] == 0)
                        pos.x += dir.x * moveSpeed;
                    if (worldMap[(int)(pos.x)][(int)(pos.y + dir.y * moveSpeed)] == 0)
                        pos.y += dir.y * moveSpeed;
                    break ;
                }
                if (mySDL2.event.key.keysym.sym == SDLK_DOWN)
                {
                    if (worldMap[(int)(pos.x - dir.x * moveSpeed)][(int)(pos.y)] == 0)
                        pos.x -= dir.x * moveSpeed;
                    if (worldMap[(int)(pos.x)][(int)(pos.y - dir.y * moveSpeed)] == 0)
                        pos.y -= dir.y * moveSpeed;
                    break ;
                }
                if (mySDL2.event.key.keysym.sym == SDLK_RIGHT)
                {
                    oldDirX = dir.x;
                    dir.x = dir.x * cos(-rotSpeed) - dir.y * sin(-rotSpeed);
                    dir.y = oldDirX * sin(-rotSpeed) + dir.y * cos(-rotSpeed);
                    oldPlaneX = plane.x;
                    plane.x = plane.x * cos(-rotSpeed) - plane.y * sin(-rotSpeed);
                    plane.y = oldPlaneX * sin(-rotSpeed) + plane.y * cos(-rotSpeed);
                    break ;
                }
                if (mySDL2.event.key.keysym.sym == SDLK_LEFT)
                {
                    oldDirX = dir.x;
                    dir.x = dir.x * cos(rotSpeed) - dir.y * sin(rotSpeed);
                    dir.y = oldDirX * sin(rotSpeed) + dir.y * cos(rotSpeed);
                    oldPlaneX = plane.x;
                    plane.x = plane.x * cos(rotSpeed) - plane.y * sin(rotSpeed);
                    plane.y = oldPlaneX * sin(rotSpeed) + plane.y * cos(rotSpeed);
                    break ;
                }
            }
        }
    }

    sdl2_release(&mySDL2);
    
    return (0);
}