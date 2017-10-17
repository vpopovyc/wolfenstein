/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_game_from_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 16:31:15 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/17 16:31:17 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static inline void 	  parse_map_line(int *map_line, char **info, int hard_check)
{
	int	i;

	i = 0;
	if (info == NULL)
		perror("get_game_from_file.c: parse_map_line(): map info == NULL");
	while (info[i] && i < map_width)
	{
		map_line[i] = atoi(info[i]);
		if (hard_check && map_line[i] == 0)
			map_line[i] = 1;
		++i;
	}
	if (i != map_width)
		perror("get_game_from_file.c: parse_map_line(): some map info is lost");
	if (map_line[first] == 0)
		map_line[first] = 1;
	if (map_line[last] == 0)
		map_line[last] = 1;
	ft_ppdel(&info);
}

static inline void    parse_map(t_game *new_game, int fd)
{
    int     	i;
    char    	*line;
    t_world_map *new_map;

    i = 0;
    line = NULL;
    new_map = malloc(sizeof(t_world_map));
    ft_memset(new_map, 0, sizeof(t_world_map));
    while (get_next_line(fd, &line) > 0 && i < map_height)
    {
    	parse_map_line(new_map->world_map[i], ft_strsplit(line, ' '), (i == first || i == last) ? 1 : 0);
    	free(line);
    	line = NULL;
    	++i;
    }
    new_game->map = new_map;
}

static inline void 	  parse_header(t_game *new_game, int fd)
{
	int  		i;
	char 		*line;
	char 		**info;

	i = 0;
	line = NULL;
    get_next_line(fd, &line);
	info = ft_strsplit(line, ' ');
	if (info == NULL)
        perror("get_game_from_file.c: parse_header(): game info == NULL");
	while (info[i])
		++i;
	if (i < info_columns)
		perror("get_game_from_file.c: parse_header(): some game info is lost");
	new_game->pos.x = abs(atoi(info[1]));
	new_game->pos.y = abs(atoi(info[3]));
	ft_ppdel(&info);
	free(line);
}

static inline void    parse_file(t_game *new_game, char *path)
{
    int     fd;
    char 	*line;

    line = NULL;
    fd = open(path, O_RDONLY);
    if (fd == -1)
        perror("get_game_from_file.c: parse_file(): ");
    if (read(fd, line, 0) == -1)
        perror("get_game_from_file.c: parse_file(): ");
    parse_header(new_game, fd);
    parse_map(new_game, fd);
    close(fd);
}

void	get_game_from_file(t_game *game, size_t info)
{
    char path[256];
    char *path_num;

    ft_memset(path, 0, 256);
    ft_memcpy(path, "./game/pos_files/", ft_strlen("./game/pos_files/"));
    path_num = ft_itoa(info, 10);
    ft_strcat(path, path_num);
    free(path_num);
    ft_strcat(path, "_lvl.mpf");
    parse_file(game, path);
}
