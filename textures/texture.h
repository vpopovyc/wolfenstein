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
# include "../lodepng.h"

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

uint32_t                    **load_textures(void);

#endif