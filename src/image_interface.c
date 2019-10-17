/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_interface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:47:40 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/17 14:18:24 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//static inline int	calc_position
/*
** this is the standard bresenham line drawing alg
** will need to replace this to handle textures .
*/

void		ft_mlx_draw_line(t_line *l, t_wolf *w)
{
	l->dx = abs(l->xfinal - l->xstart);
	l->sx = (l->xstart < l->xfinal) ? 1 : -1;
	l->dy = abs(l->yfinal - l->ystart);
	l->sy = (l->ystart < l->yfinal) ? 1 : -1;
	l->err1 = (l->dx > l->dy) ? l->dx / 2 : l->dy / 2;
	while (1)
	{
		ft_mlx_pixel_put_texture(w, l->xstart, l->ystart, w->tex[w->tex_code].texture[w->tex[w->tex_code].y][w->tex[w->tex_code].y]);
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
		//calc which picel to load from the texture array
		w->tex[w->tex_code].y = (w->tex[w->tex_code].y < TEX_HEIGHT - 1) ? w->tex[w->tex_code].y + 1 : 0;
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
		int color)
{
	int		off;
	int		red = ((color >> 16) & 0xff);
	int		green = (color >> 8) & 0xff;
	int		blue = (color & 0xFF);

	//printf("tex_code == %d\tred = %d; green = %d;blue = %d\n", texture_code, red, green, blue);
	off = (x_cord + (y_cord * WIN_W)) * 4;
	wolf->mlx.data_start[off] = (char)red;
	wolf->mlx.data_start[off + 1] = (char)green;
	wolf->mlx.data_start[off + 2] = (char)blue;
}

void		ft_draw_line_textured(t_wolf *w, int ystart, int yend, int line_height, int x)
{
	int		y;
	int		d;
	int		tex_c;
	int		color;

	y = ystart;
	while (y < yend)
	{
		d = y * 256 - WIN_H * 128 + line_height * 128;
		tex_c = ((d * TEX_HEIGHT) / line_height) / 256;
		color = w->tex[w->tex_code].texture[tex_c][w->r.tex_x_value];
		ft_mlx_pixel_put_texture(w, x, y, color);
		y++;
	}
}
