/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 13:36:44 by cchromos          #+#    #+#             */
/*   Updated: 2021/03/10 13:36:47 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grafic.h"

void	utils(t_data *image, t_player_list *player)
{
	if (player->vector_of_player == 'W')
	{
		image->dir_x = -1;
		image->dir_y = 0;
		image->plane_x = 0;
		image->plane_y = -0.66;
	}
	image->keys->w = 0;
	image->keys->s = 0;
	image->keys->a = 0;
	image->keys->d = 0;
	image->keys->r = 0;
	image->keys->l = 0;
	image->player = player->vector_of_player;
	image->to_free = player->to_free;
	image->pos_x = player->y_player + 0.5;
	image->pos_y = player->x_player + 0.5;
	return ;
}
