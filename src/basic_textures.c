/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:26:21 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/19 13:11:08 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** these patterns assume  a TEX_HEIGHT and TEX_WIDTH of 64 feel free to change
** the macros in the header for them to change the scaling of the texture
** the texture is only calculated for each set of x values so thinner lines get
** 	will get rounded over depending on the distance // angle
** flat colors are much less effort to get lookng nice cause the don't distort
*/

/*
** because the textures in this file are static you have to run them but
** you can just overwrite them
*/

/*
** gridlines
** color == line color;
** color2 == background color
*/

static void	load_pattern1(t_wolf *w, int tex_number, int color,
		int color2)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < TEX_HEIGHT)
	{
		x = 0;
		while (x < TEX_WIDTH)
		{
			if (y % 16 == 0 || x % 16 == 0)
				w->tex[tex_number].texture[y][x] = color;
			else
				w->tex[tex_number].texture[y][x] = color2;
			x++;
		}
		y++;
	}
}

/*
** horizontal lines
*/

static void	load_pattern2(t_wolf *w, int tex_number, int color,
		int color2)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < TEX_HEIGHT)
	{
		x = 0;
		while (x < TEX_WIDTH)
		{
			if (y % 16 == 0 || y % 16 == 1 || y % 16 == 2)
				w->tex[tex_number].texture[y][x] = color;
			else
				w->tex[tex_number].texture[y][x] = color2;
			x++;
		}
		y++;
	}
}

/*
** flat color
*/

static void	load_pattern3(t_wolf *w, int tex_number, int color,
		int unused)
{
	int		x;
	int		y;

	(void)unused;
	x = 0;
	y = 0;
	while (y < TEX_HEIGHT)
	{
		x = 0;
		while (x < TEX_WIDTH)
		{
			w->tex[tex_number].texture[y][x] = color;
			x++;
		}
		y++;
	}
}

/*
** gradient from color
*/

static void	load_pattern4(t_wolf *w, int tex_number, int color,
		int unused)
{
	int		x;
	int		y;
	double	ycolor;

	(void)unused;
	y = 0;
	while (y < TEX_HEIGHT)
	{
		ycolor = ((double)y / (double)TEX_HEIGHT);
		x = 0;
		while (x < TEX_WIDTH)
		{
			w->tex[tex_number].texture[y][x] = ((double)color * ycolor);
			x++;
		}
		y++;
	}
}

/*
** fills in the texture arrays
*/

void		basic_texture_handle(t_wolf *w)
{
	load_pattern1(w, 0, 0xff0000, 0x000000);
	load_pattern2(w, 0, 0xffffff, 0x000000);
	load_pattern1(w, 0, 0x00ff00, 0x000000);
	load_pattern3(w, 0, 0xff0000, 0x000000);
	load_pattern3(w, 1, 0x00ff00, 0x000000);
	load_pattern3(w, 2, 0x0000ff, 0x000000);
	load_pattern3(w, 3, 0xffffff, 0x000000);
	load_pattern4(w, 0, 0xff0000, 0x000000);
	load_pattern5(w, 1, 0x00ff00, 0x000000);
	load_pattern7(w, 2, 0xf0000f, 0x000000);
	load_pattern7(w, 3, 0x00ff00, 0x000000);
}
