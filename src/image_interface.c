/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_interface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:47:40 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/14 21:30:37 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//static inline int	calc_position
/*
** this is the standard bresenham line drawing alg
** will need to replace this to handle textures .
*/

void		ft_mlx_draw_line(t_line *l, t_wolf *wolf)
{
	int		y;

	y = 0;
	l->dx = abs(l->xfinal - l->xstart);
	l->sx = (l->xstart < l->xfinal) ? 1 : -1;
	l->dy = abs(l->yfinal - l->ystart);
	l->sy = (l->ystart < l->yfinal) ? 1 : -1;
	l->err1 = (l->dx > l->dy) ? l->dx / 2 : l->dy / 2;
	while (1)
	{
		ft_mlx_pixel_put_texture(wolf, l->xstart, l->ystart, wolf->tex[3].texture[32][y]);
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
		y = (y < TEX_SIZE - 1) ? y + 1 : 0;
	}
}

void		ft_mlx_pixel_put(t_wolf *wolf, int x_cord, int y_cord)
{
	int		off;

	off = (x_cord + (y_cord * WIN_W)) * 4;
	wolf->mlx.data_start[off] = (char)(0xff);
	wolf->mlx.data_start[off + 1] = (char)(0x00);
	wolf->mlx.data_start[off + 2] = (char)(0xff);
}

void		ft_mlx_pixel_put_texture(t_wolf *wolf, int x_cord, int y_cord,
		int texture_code)
{
	int		off;
	int		red = ((texture_code >> 16) & 0xff);
	int		green = (texture_code >> 8) & 0xff;
	int		blue = (texture_code & 0xFF);

	//printf("tex_code == %d\tred = %d; green = %d;blue = %d\n", texture_code, red, green, blue);
	off = (x_cord + (y_cord * WIN_W)) * 4;
	wolf->mlx.data_start[off] = (char)red;
	wolf->mlx.data_start[off + 1] = (char)green;
	wolf->mlx.data_start[off + 2] = (char)blue;
}
