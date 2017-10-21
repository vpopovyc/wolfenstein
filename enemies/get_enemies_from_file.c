/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_enemies_from_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 15:03:11 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/10/16 15:03:12 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemies.h"

static inline uint32_t	get_matching_texture_index(char *texture_name)
{
	if (ft_strequ(texture_name, "officer"))
		return (officer);
	return (0);
}

/*
** parsing one line of data readed from file
*/

static inline void		get_enemy_info(t_enemy *enemy, char **info)
{
	ssize_t	i;

	i = 0;
	if (info == NULL)
		perror("get_enemies_from_file.c: get_enemy_info(): enemy info == NULL");
	while (info[i])
		++i;
	if (i < ENEMIES_INFO_COLUMNS)
		perror("get_enemies_from_file.c: get_enemy_info(): enemy info is lost");
	enemy->pos.x = atoi(info[pos_x]);
	enemy->pos.y = atoi(info[pos_y]);
	enemy->dir.x = atoi(info[dir_x]);
	enemy->dir.y = atoi(info[dir_y]);
	enemy->texture_index = get_matching_texture_index(info[texture]);
	ft_ppdel(&info);
}

/*
** Open file that contain info about enemies
*/

static inline void		parse_file(t_enemy *enemies, const char *path)
{
	int		fd;
	int		count;
	char	*line;

	line = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		perror("get_enemies_from_file.c: parse_file(): could not open a file");
	if (read(fd, line, 0) == -1)
		perror("get_enemies_from_file.c: parse_file(): could not read a file");
	count = 0;
	while (get_next_line(fd, &line) > 0 && count < MAX_NUMBER_ENEMIES)
	{
		get_enemy_info(&(enemies[count]), ft_strsplit(line, ' '));
		++count;
		free(line);
	}
}

/*
** Get enemies based on file specified
*/

void					get_enemies_from_file(t_enemy *enemies, size_t info)
{
	char path[256];
	char *path_num;

	ft_memset(path, 0, 256);
	ft_memcpy(path, "./enemies/pos_files/", ft_strlen("./enemies/pos_files/"));
	path_num = ft_itoa(info, 10);
	ft_strcat(path, path_num);
	free(path_num);
	ft_strcat(path, "_lvl.epf");
	parse_file(enemies, path);
}
