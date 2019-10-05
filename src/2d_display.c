/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 12:43:59 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/05 15:20:55 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		wolf_2d_check_adjacent(t_wolf *wolf, int x, int y)
{
	wolf->line->xstart = x * wolf->map->xco;
	wolf->line->ystart = y * wolf->map->yco;
//	if (x > 0)
//		//check left;
	if (x < wolf->map->width) //right
		if (wolf->map->map[y][x + 1] > 0)
		{
			wolf->line->xfinal = (x + 1) * wolf->map->xco;
			wolf->line->yfinal = (y) * wolf->map->yco;
			ft_mlx_draw_line(wolf->line, wolf);
		}
	if (y < wolf->map->height - 1) // up
		if (wolf->map->map[y + 1][x])
		{
			wolf->line->xstart = x * wolf->map->xco;
			wolf->line->ystart = y * wolf->map->yco;
			wolf->line->xfinal = (x) * wolf->map->xco;
			wolf->line->yfinal = (y + 1) * wolf->map->yco;
			ft_mlx_draw_line(wolf->line, wolf);
		}
//	if (y > 0)
//		//check down;
}

/* probably going to redo the map parsing but want a POC for the 2d parsing
** 	right now it works mostly the same way as fdf's parser
** want to move to something close to a series of instructions for the walls
** if
** 		(wall) 1,3 -> 3,3 to build a wall instead of passing in the int values
**
*/

void		display_2d_grid(t_wolf *wolf)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (y < wolf->map->height)
	{
		x = 0;
		while (x < wolf->map->width)
		{
			if (wolf->map->map[x][y] > 0)
				wolf_2d_check_adjacent(wolf, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(wolf->mlx.mlx_ptr, wolf->mlx.window_ptr,
		wolf->mlx.img_ptr, 0, 0);
}
