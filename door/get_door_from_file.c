/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_door_from_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 21:19:23 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/20 21:19:24 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "door.h"
#include "e_door_parse.h"

static inline uint32_t	get_matching_texture_index(char *texture_name)
{
	if (ft_strequ(texture_name, "door3"))
		return (door3);
	return (0);
}

static inline void		get_door_info(t_door *door, char **info)
{
	ssize_t i;

	i = 0;
	if (info == NULL)
		perror("get_door_from_file.c: get_door_info(): door info == NULL");
	while (info[i])
		++i;
	if (i < DOORINFO_COLUMNS)
		perror("get_door_from_file.c: get_door_info(): door info is lost");
	door->pos.x = atoi(info[x]);
	door->pos.y = atoi(info[y]);
	door->is_open = ft_strequ(info[status], "yes") ? 1 : 0;
	door->texture_index = get_matching_texture_index(info[texture]);
	ft_ppdel(&info);
}

/*
** Open file that contain info about doors
*/

static inline void		parse_file(t_door *new_door, char *path)
{
	int		fd;
	char	*line;
	int		i;

	line = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		perror("get_door_from_file.c: parse_file(): ");
	if (read(fd, line, 0) == -1)
		perror("get_door_from_file.c: parse_file(): ");
	i = 0;
	while (get_next_line(fd, &line) > 0 && i < MAX_DOORS_NUMBER)
	{
		get_door_info(&(new_door[i]), ft_strsplit(line, ' '));
		++i;
		free(line);
	}
	close(fd);
}

void					get_door_from_file(t_door *door, size_t info)
{
	char path[256];
	char *path_num;

	ft_memset(path, 0, 256);
	ft_memcpy(path, "./door/pos_files/", ft_strlen("./door/pos_files/"));
	path_num = ft_itoa(info, 10);
	ft_strcat(path, path_num);
	free(path_num);
	ft_strcat(path, "_lvl.dpf");
	parse_file(door, path);
}
