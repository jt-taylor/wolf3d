/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_interface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:47:40 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/17 19:53:22 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static inline void		ft_mlx_pixel_put_texture(t_wolf *wolf, int x_cord, int y_cord,
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

void		fill_skybox_floor(t_wolf *w)
{
	//ft_memset(w->mlx.data_start, 0x00fa8072, (WIN_W * WIN_H) * 4);
	int		y;
	int		x;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			ft_mlx_pixel_put_texture(w, x, y, 0x2708af);
			x++;
		}
		y++;
	}
}

void		ft_draw_line_textured(t_wolf *w, int ystart, int yend, int line_height,
		int x)
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
