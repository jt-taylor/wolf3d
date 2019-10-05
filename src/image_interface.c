/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_interface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:47:40 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/05 15:26:32 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** there isn't a way to make this cleaner in norme ,
** because norme limits the total number of variables we kinda just have to
** throw everything into a struct
*/
void		ft_mlx_draw_line(t_line *l, t_wolf *wolf)
{
	l->dx = abs(l->xfinal - l->xstart);
	l->sx = (l->xstart < l->xfinal) ? 1 : -1;
	l->dy = abs(l->yfinal - l->ystart);
	l->sy = (l->ystart < l->yfinal) ? 1 : -1;
	l->err1 = (l->dx > l->dy) ? l->dx / 2 : l->dy / 2;
	while (1)
	{
		ft_mlx_pixel_put(wolf, l->xstart, l->ystart);
		if (l->xstart == l->xfinal && l->ystart == l->yfinal)
			break ;
		l->err2 = l->err1;
		if (l->err2 > -l->dx)
		{
			l->err1 -= l->dy;
			(l->xstart != l->xfinal) ? l->xstart += l->sx : 0;
		}
		if (l->err2 < l->dy)
		{
			l->err1 += l->dx;
			(l->ystart != l->yfinal) ? l->ystart += l->sy : 0;
		}
	}
}

void		ft_mlx_pixel_put(t_wolf *wolf, int x_cord, int y_cord)
{
	int		off;

	off = (x_cord + (y_cord * WIN_W)) * 4;
	//rgb
	wolf->mlx.data_start[off] = (char)(0x17);
	wolf->mlx.data_start[off + 1] = (char)(0xf1);
	wolf->mlx.data_start[off + 2] = (char)(0x00);
}
