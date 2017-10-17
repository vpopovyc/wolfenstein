/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 20:39:55 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/05/15 20:40:27 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sounds.h"

static inline Uint32	*audio_len(void)
{
	static Uint32 *len;

	if (len == NULL)
	{
		len = malloc(sizeof(Uint32));
	}
	return (len);
}

static inline Uint8		**audio_pos(void)
{
	static Uint8 **pos;

	if (pos == NULL)
	{
		pos = malloc(sizeof(Uint8*));
	}
	return (pos);
}

void	my_audio_callback(void *userdata, Uint8 *stream, int len)
{
	Uint32 tmp_len;

	tmp_len = len;
	if (*audio_len() == 0)
		return ;
	else if (tmp_len > *audio_len())
		len = *audio_len();
	userdata = NULL;
	SDL_memcpy(stream, *audio_pos(), len);
	SDL_MixAudio(stream, *audio_pos(), len, SDL_MIX_MAXVOLUME);
	*audio_pos() += len;
	*audio_len() -= len;
}

void	play_wav_track(SDL_AudioSpec *wav_spec)
{
	if (SDL_OpenAudio(wav_spec, NULL) < 0)
		return ;
	else
	{
		SDL_PauseAudio(0);
		while (*audio_len() > 0)
			SDL_Delay(100);
	}
}

void	sound(char *track)
{
	static Uint8			*wav_buffer;
	static Uint32			wav_length;
	static SDL_AudioSpec	wav_spec;

	if (SDL_LoadWAV(track, &wav_spec, &wav_buffer, &wav_length) == NULL)
		return ;
	else
	{
		wav_spec.callback = my_audio_callback;
		wav_spec.userdata = NULL;
		*audio_pos() = wav_buffer;
		*audio_len() = wav_length;
		play_wav_track(&wav_spec);
		SDL_CloseAudio();
		SDL_FreeWAV(wav_buffer);
	}
}
