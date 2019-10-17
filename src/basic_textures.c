/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:26:21 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/17 14:40:24 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"


/*
** solid color blocks
*/

static inline void	load_pattern1(t_wolf *w, int tex_number, int color)
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
			if (y % 2 == 0)
				w->tex[tex_number].texture[y][x] = color;
			else
				w->tex[tex_number].texture[y][x] = 0x00;
			x++;
		}
		y++;
	}
}

void		basic_texture_handle(t_wolf *w)
{
	load_pattern1(w, 1, 0xff0000);
	load_pattern1(w, 2, 0x00ff00);
	load_pattern1(w, 3, 0x0000ff);
	load_pattern1(w, 0, 0xffffff);
}
