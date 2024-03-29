/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_texture_patterns.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 16:52:44 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/19 16:25:33 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** xor
*/

void	load_pattern5(t_wolf *w, int tex_number, int color, int color2)
{
	int		x;
	int		y;
	int		xorcolor;

	(void)color2;
	(void)color;
	y = 0;
	while (y < TEX_HEIGHT)
	{
		x = 0;
		xorcolor = (x * 256 / TEX_WIDTH) ^ (y * 256 / TEX_HEIGHT);
		while (x < TEX_WIDTH)
		{
			w->tex[tex_number].texture[y][x] = xorcolor;
			x++;
		}
		y++;
	}
}

/*
** "bricks"
*/

void	load_pattern6(t_wolf *w, int tex_number, int color, int color2)
{
	int		x;
	int		y;

	(void)color2;
	y = 0;
	while (y < TEX_HEIGHT)
	{
		x = 0;
		while (x < TEX_WIDTH)
		{
			w->tex[tex_number].texture[y][x] = color * 128 *
				(x % (TEX_WIDTH / 16) && y % (TEX_HEIGHT / 16));
			x++;
		}
		y++;
	}
}

/*
** diagnol x
** need to fix this supposed to be a gradient but had integer overflow
** so this is what it is for now
*/

void	load_pattern7(t_wolf *w, int tex_number, int color, int color2)
{
	int			x;
	int			y;
	double		mod;

	(void)color2;
	y = 0;
	while (y < TEX_HEIGHT)
	{
		x = 0;
		while (x < TEX_WIDTH)
		{
			mod = ((double)y / (double)TEX_HEIGHT + (double)x /
					(double)TEX_WIDTH) / (double)2;
			w->tex[tex_number].texture[y][x] = (double)color * mod *
				(x != y && x != TEX_WIDTH - y);
			x++;
		}
		y++;
	}
}

/*
** void	load_pattern8(t_wolf *w, int tex_number, int color, int color2)
** {
** 	int		x;
** 	int		y;
**
** 	y = 0;
** 	while (y < TEX_HEIGHT)
** 	{
** 		x = 0;
** 		while (x < TEX_WIDTH)
** 		{
** 			w->tex[tex_number].texture[y][x] =
** 			x++;
** 		}
** 		y++;
** 	}
** }
**
** void	load_pattern9(t_wolf *w, int tex_number, int color, int color2)
** {
** 	int		x;
** 	int		y;
**
** 	y = 0;
** 	while (y < TEX_HEIGHT)
** 	{
** 		x = 0;
** 		while (x < TEX_WIDTH)
** 		{
** 			w->tex[tex_number].texture[y][x] =
** 			x++;
** 		}
** 		y++;
** 	}
** }
*/
