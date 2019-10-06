/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:42:29 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/06 13:19:11 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	wolf3d_init_player(t_wolf *wolf)
{
	wolf->player.x_cord = 22.0;
	wolf->player.y_cord = 12.0;
	wolf->player.dir_x = -1.0;
	wolf->player.dir_y = 1.0;
	wolf->player.plane_x = 0.0;
	wolf->player.plane_y = 1.0;
}
