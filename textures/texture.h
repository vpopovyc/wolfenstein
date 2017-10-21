/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 11:37:50 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/19 12:48:00 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TEXTURE_H
# define __TEXTURE_H

# include <stdint.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../lodepng/lodepng.h"

/*
** Max number of different textures that can be loaded
*/

# define MAX_TEX_NUMBER     62

/*
** Layout in array of textures that represents different module textures
*/

# define WALLS_INDX         0
# define SPRITE_INDX        12
# define DOORS_INDX         24
# define ENEMY_INDX         32

/*
** Max number of diff textures
*/

# define MAX_WALLS          12
# define MAX_SPRITE         12
# define MAX_DOORS          12
# define MAX_ENEMY          12

/*
** Loads all scpecified textures in memory
*/

uint32_t	**load_textures(void);

/*
** Paths
*/

/*
** Doors
*/

# define DOOR_PATH_1	"./textures/refs/doors/door3.png"

/*
** Objects
*/

# define OBJ_PATH_1		"./textures/refs/sprites/barrel.png"

/*
** Walls
*/

# define WALL_PATH_1	"./textures/refs/worldaround/cell_w_skeleton.png"
# define WALL_PATH_2	"./textures/refs/worldaround/greybrickw-cell.png"
# define WALL_PATH_3	"./textures/refs/worldaround/greybrickw-swastika.png"
# define WALL_PATH_4	"./textures/refs/worldaround/wall6.png"

/*
** Enemies
*/

# define ENEM_PATH_1_1	"./textures/refs/enemies/officer_front.png"
# define ENEM_PATH_1_2	"./textures/refs/enemies/officer_back.png"
# define ENEM_PATH_1_3	"./textures/refs/enemies/officer_side_left.png"
# define ENEM_PATH_1_4	"./textures/refs/enemies/officer_side_right.png"

#endif
