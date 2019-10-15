/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:26:21 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/14 21:28:25 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"


/*
** solid color blocks
*/

static inline void	basic_texture_gen(t_wolf *w)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < TEX_SIZE)
	{
		x = 0;
		while (x < TEX_SIZE)
		{
			if (x % 2 == 0)
			{
				w->tex[0].texture[y][x] = 0x0066ff;
				w->tex[1].texture[y][x] = 0xff0000;
				w->tex[2].texture[y][x] = 0x003300;
				w->tex[3].texture[y][x] = 0xff0009;
			}
			else
			{
				w->tex[0].texture[y][x] = 0x00;
				w->tex[1].texture[y][x] = 0x00;
				w->tex[2].texture[y][x] = 0x00;
				w->tex[3].texture[y][x] = 0x00;
			}
			x++;
		}
		y++;
	}
}

void		basic_texture_handle(t_wolf *wolf)
{
	basic_texture_gen(wolf);
}
