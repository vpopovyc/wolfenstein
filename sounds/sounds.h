/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 20:40:33 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/05/15 20:40:36 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SOUNDS_H
# define __SOUNDS_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_audio.h>

# define OK 	"sounds/flow.wav"
# define BLASTER_PEEP "sounds/blaster.wav"
# define PISTOL_PEEP "sounds/pistol.wav"
# define SABER_PEEP "sounds/saber.wav"

typedef enum 	e_peep_types
{
	get_peep,
	pistol, 
	blaster,
	saber
}				t_peep_types;

void		my_audio_callback(void *userdata, Uint8 *stream, int len);
void		play_wav_track(SDL_AudioSpec *wav_spec);
void		sound(char *track);
#endif
