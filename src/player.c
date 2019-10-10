/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:42:29 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/09 17:34:37 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	wolf3d_init_player(t_wolf *wolf)
{
	wolf->player.x_cord = (double)wolf->map->xstart;
	wolf->player.y_cord = (double)wolf->map->ystart;
	wolf->player.dir_x = -1.0;
	wolf->player.dir_y = 1.0;
	wolf->player.plane_x = 0.0;
	wolf->player.plane_y = 1.0;
}
