/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 19:44:13 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/10/15 19:44:15 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_rain.h"

static inline int		*ps_size(void)
{
	static int *ps_size;

	if (ps_size == NULL)
	{
		ps_size = malloc(sizeof(int));
		(*ps_size) = 0;
	}
	return (ps_size);
}

static inline void	emit(t_ps *ps)
{
	int i;

	i = 0;
	while (ps->next)
		ps = ps->next;
	ps->next = malloc(sizeof(t_ps));
	ps = ps->next;
	ps->parts = malloc(sizeof(t_part) * NODE_SIZE);
	ps->next = NULL;
	while (i < NODE_SIZE)
	{
		ps->parts[i].pos.x = rand() % 800;
		ps->parts[i].pos.y = rand() % 42;
		ps->parts[i].color = 0xf1a9a8;
		++i;
	}
	*ps_size() += 1;
}

static inline void	de_emit(t_ps **ps)
{
	t_ps *temp_ps;

	temp_ps = *ps;
	*ps = (*ps)->next;
	free(temp_ps->parts);
	temp_ps->parts = NULL;
	free(temp_ps);
	temp_ps = NULL;
	*ps_size() -= 1;
}

void	render_ps(t_ps *ps, t_sdl2_tools *mySDL2)
{
	int i;

	while (ps)
	{
		i = 0;
		while (i < NODE_SIZE)
		{
			sdl2_put_pixel(mySDL2, ps->parts[i].color, ps->parts[i].pos.x, ps->parts[i].pos.y);
			sdl2_put_pixel(mySDL2, ps->parts[i].color, ps->parts[i].pos.x, ps->parts[i].pos.y + 2);
			sdl2_put_pixel(mySDL2, ps->parts[i].color, ps->parts[i].pos.x, ps->parts[i].pos.y + 3);
			ps->parts[i].pos.y += ps->parts[i].pos.y < 550 ? rand() % 42 : -(rand() % 400);
			++i;
		}
		ps = ps->next;
	}
}

void	*next_ps_iter(void *arg)
{
	static t_ps	*ps;
	int		i;
	t_appcore *appcore;

	appcore = (t_appcore*)arg;
	if (ps == NULL)
	{
		ps = malloc(sizeof(t_ps));
		ps->parts = malloc(sizeof(t_part) * NODE_SIZE);
		ps->next = NULL;
		i = 0;
		while (i < NODE_SIZE)
		{
			ps->parts[i].pos.x = rand() % 800;
			ps->parts[i++].pos.y = rand() % 42;
		}
		*ps_size() += 1;
	}
	emit(ps);
	while (*ps_size() > appcore->myGame->ps_density)
		de_emit(&ps);
	pthread_exit((void*)ps);
}

void	procced_ps(t_appcore *appcore)
{
	pthread_create(&(appcore->ps_thread), NULL, next_ps_iter, (void*)appcore);
}

void	draw_ps(pthread_t *ps_thread, t_sdl2_tools *mySDL2)
{
	t_ps *ps;

	pthread_join(*ps_thread, (void*)&ps);
	if (ps == NULL)
		return ;
	render_ps(ps, mySDL2);
}

