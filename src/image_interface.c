/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_interface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:47:40 by jtaylor           #+#    #+#             */
/*   Updated: 2019/09/25 19:28:54 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		test(t_wolf *wolf)
{
	wolf->line->xstart = 50;
	wolf->line->ystart = 50;
	wolf->line->xfinal = 50;
	wolf->line->yfinal = 100;
	ft_mlx_draw_line(wolf->line, wolf);
	wolf->shape = malloc(sizeof(t_shape));
	wolf->shape->q1x = 200;
	wolf->shape->q1y = 200;
	wolf->shape->q2x = 354;
	wolf->shape->q2y = 400;
	wolf->shape->q3x = 350;
	wolf->shape->q3y = 500;
	wolf->shape->q4x = 200;
	wolf->shape->q4y = 350;
	ft_mlx_draw_quad(wolf, wolf->shape);
	mlx_put_image_to_window(wolf->mlx.mlx_ptr, wolf->mlx.window_ptr,
		wolf->mlx.img_ptr, 0, 0);
}

/*
** is it worth it to make this a generic function that takes a queue ?
*/

void		ft_mlx_draw_quad(t_wolf *wolf, t_shape *shape)
{
	(void)shape;
	wolf->line->xstart = wolf->shape->q1x;
	wolf->line->ystart = wolf->shape->q1y;
	wolf->line->xfinal = wolf->shape->q2x;
	wolf->line->yfinal = wolf->shape->q2y;
	ft_mlx_draw_line(wolf->line, wolf);
	wolf->line->xstart = wolf->shape->q2x;
	wolf->line->ystart = wolf->shape->q2y;
	wolf->line->xfinal = wolf->shape->q3x;
	wolf->line->yfinal = wolf->shape->q3y;
	ft_mlx_draw_line(wolf->line, wolf);
	wolf->line->xstart = wolf->shape->q3x;
	wolf->line->ystart = wolf->shape->q3y;
	wolf->line->xfinal = wolf->shape->q4x;
	wolf->line->yfinal = wolf->shape->q4y;
	ft_mlx_draw_line(wolf->line, wolf);
	wolf->line->xstart = wolf->shape->q4x;
	wolf->line->ystart = wolf->shape->q4y;
	wolf->line->xfinal = wolf->shape->q1x;
	wolf->line->yfinal = wolf->shape->q1y;
	ft_mlx_draw_line(wolf->line, wolf);
}

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
