/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rain.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 21:20:17 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/10/21 21:20:20 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_rain.h"

void	procced_ps(t_appcore *appcore)
{
	pthread_create(&(appcore->ps_thread), NULL, next_ps_iter, (void*)appcore);
}

void	draw_ps(pthread_t *ps_thread, t_sdl2_tools *sdl)
{
	t_ps *ps;

	pthread_join(*ps_thread, (void*)&ps);
	if (ps == NULL)
		return ;
	render_ps(ps, sdl);
}
