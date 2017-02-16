/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 00:39:09 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/16 14:31:16 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	init_sound(t_sound *sound)
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
	Mix_AllocateChannels(1);
	Mix_Volume(1, MIX_MAX_VOLUME);
	sound->chunk = Mix_LoadWAV("./media/sound/screenshot.wav");
	sound->music = Mix_LoadMUS("./media/sound/Music2.mp3");
}
