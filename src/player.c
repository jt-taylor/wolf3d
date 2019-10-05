/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:42:29 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/05 15:12:47 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	wolf3d_init_player(t_wolf *wolf)
{
	wolf->player.x_cord = 5;
	wolf->player.y_cord = 2;
	wolf->player.dir_x = -1;
	wolf->player.dir_y = 0;
	wolf->player.plane_x = 0;
	wolf->player.plane_y = .66;
}
