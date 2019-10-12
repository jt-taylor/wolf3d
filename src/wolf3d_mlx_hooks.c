/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_mlx_hooks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 15:38:56 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/11 15:17:36 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
//#include <OpenGL/gl3.h>
//#include "mlx_int.h"

static inline void	free_int_matrix(t_wolf *w)
{
	int		col;

	col = 0;
	while (col < w->map->height)
	{
		free(w->map->map[col]);
		col++;
	}
	free(w->map->map);
}

/*
** minilibx doesn't supply a way to free the mlx_ptr returned from mlx_init
** the mlx_ptr->font->buffer and the mlx_ptr->font become leaks if you
** free the mlx_ptr without manually freeing them
*/

static inline void	free_the_things(t_wolf *w)
{
	// ? free data_start / not sure if mlx_destroy image_does this
	mlx_destroy_image(w->mlx.mlx_ptr, w->mlx.img_ptr);
	mlx_destroy_window(w->mlx.mlx_ptr, w->mlx.window_ptr);
	//free(w->mlx.mlx_ptr);
	free_mlx_ptr(w->mlx.mlx_ptr);
	free_int_matrix(w);
	free(w->map);
	free(w->line);
	free(w);
}

int		wolf3d_close(void *param)
{
	free_the_things((t_wolf *)param);
	//free everything that I malloc'd
	//and posibly what mlx malloc'd
	//everything I malloc'd should be free'd here
	exit(0);
}

/*
** mlx doesn't have a builtin way to handle a key being held down
** 	only keypress and key release
** 	so on keypress toggle the flag on and on keyrelease set it off
**
** 0x35 = ESC
** 0x7b = KEY_LEFT
** 0x7c = KEY_RIGHT
** 0x7d = KEY_DOWN
** 0x7e = KEY_UP
*/

int		wolf3d_key_press(int key_code, t_wolf *wolf)
{
	if (key_code == 0x35)
		wolf3d_close(wolf);
	else if (key_code >= 0x7b && key_code <= 0x7e)
	{
		if (key_code == 0x7b)
			wolf->mlx.keys.key_left = 1;
		else if (key_code == 0x7c)
			wolf->mlx.keys.key_right = 1;
		else if (key_code == 0x7d)
			wolf->mlx.keys.key_down = 1;
		else if (key_code == 0x7e)
			wolf->mlx.keys.key_up = 1;
	}
	return (0);
}

int		wolf3d_key_release(int key_code, t_wolf *wolf)
{
	if (key_code >= 0x7b && key_code <= 0x7e)
	{
		if (key_code == 0x7b)
			wolf->mlx.keys.key_left = 0;
		else if (key_code == 0x7c)
			wolf->mlx.keys.key_right = 0;
		else if (key_code == 0x7d)
			wolf->mlx.keys.key_down = 0;
		else if (key_code == 0x7e)
			wolf->mlx.keys.key_up = 0;
	}
	return (0);
}
