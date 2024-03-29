/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_interface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:47:40 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/20 16:46:30 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static inline void	ft_mlx_pixel_put_texture(t_wolf *wolf,
		int x_cord, int y_cord, int color)
{
	int		off;
	int		red;
	int		green;
	int		blue;

	red = ((color >> 16) & 0xff);
	green = (color >> 8) & 0xff;
	blue = (color & 0xFF);
	off = (x_cord + (y_cord * WIN_W)) * 4;
	wolf->mlx.data_start[off] = (char)red;
	wolf->mlx.data_start[off + 1] = (char)green;
	wolf->mlx.data_start[off + 2] = (char)blue;
}

void				fill_skybox_floor(t_wolf *w)
{
	int		y;
	int		x;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		if (y >= WIN_H / 2)
			while (x < WIN_W)
			{
				ft_mlx_pixel_put_texture(w, x, y, 0x87ceeb);
				x++;
			}
		else
			while (x < WIN_W)
			{
				ft_mlx_pixel_put_texture(w, x, y, 0x7ec850);
				x++;
			}
		y++;
	}
}

void				ft_draw_line_textured(t_wolf *w, t_line *l, int line_height,
		int x)
{
	int		y;
	int		d;
	int		tex_c;
	int		color;

	if (w->line->ystart < 0)
		w->line->ystart = 0;
	if (w->line->ystart >= WIN_H)
		w->line->ystart = 0;
	if (w->line->yfinal < 0)
		w->line->yfinal = 0;
	if (w->line->yfinal >= WIN_H)
		w->line->yfinal = WIN_H - 1;
	y = l->ystart;
	while (y < l->yfinal)
	{
		d = y * 256 - WIN_H * 128 + line_height * 128;
		tex_c = ((d * TEX_HEIGHT) / line_height) / 256;
		color = w->tex[w->tex_code].texture[tex_c][w->r.tex_x_value];
		ft_mlx_pixel_put_texture(w, x, y, color);
		y++;
	}
}
