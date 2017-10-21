/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprites_from_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:32:09 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/16 19:11:29 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprite.h"

static inline uint32_t	get_matching_texture_index(char *texture_name)
{
	if (ft_strequ(texture_name, "barrel"))
		return (barrel);
	return (0);
}

/*
** parsing one line of data readed from file
*/

static inline void		get_sprite_info(t_sprite *sprite, char **info)
{
	ssize_t i;

	i = 0;
	if (info == NULL)
		perror("get_sprites_from_file.c: get_sprite_info(): info == NULL");
	while (info[i])
		++i;
	if (i < SPRITEINFO_COLUMNS)
		perror("get_sprites_from_file.c: get_sprite_info(): info is lost");
	sprite->pos.x = atoi(info[x]);
	sprite->pos.y = atoi(info[y]);
	sprite->texture_index = get_matching_texture_index(info[texture]);
	ft_ppdel(&info);
}

/*
** Open file that contain info about sprites
*/

static inline void		parse_file(t_sprite_container *sprites, char *path)
{
	int		fd;
	int		count;
	char	*line;

	line = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		perror("get_sprites_from_file.c: parse_file(): could not open a file");
	if (read(fd, line, 0) == -1)
		perror("get_sprites_from_file.c: parse_file(): could not read a file");
	count = 0;
	while (get_next_line(fd, &line) > 0 && count < MAX_SPRITES_NUMBER)
	{
		get_sprite_info(&(sprites->container[count]), ft_strsplit(line, ' '));
		++count;
		free(line);
	}
	sprites->count = count;
	close(fd);
}

/*
** fill sprites based on file specified
*/

void					get_sprites_from_file(t_sprite_container *sprites,
																size_t info)
{
	char path[256];
	char *path_num;

	ft_memset(path, 0, 256);
	ft_memcpy(path, "./sprite/pos_files/", ft_strlen("./sprite/pos_files/"));
	path_num = ft_itoa(info, 10);
	ft_strcat(path, path_num);
	free(path_num);
	ft_strcat(path, "_lvl.sdf");
	parse_file(sprites, path);
}
