/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_mlx_hooks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 15:38:56 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/07 14:24:22 by jtaylor          ###   ########.fr       */
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
** so there isn't a painless way to free all of the mlx pointers
** minilibx doesn't supply a way to free the mlx_ptr returned from mlx_init
** the mlx_ptr->font->buffer and the mlx_ptr->font become leaks if you
** free the mlx_ptr without doing something like this
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

static inline void	wolf3d_move(int key_code, t_wolf *w)
{
	//need to add in the timeing functions to decouple the rnedering from the
	//making the steps smaller will reduce the angle 
	//movement speed
	if (key_code == 0x7d)//key down
	{
		(w->map->map[(int)w->player.y_cord][(int)(w->player.x_cord - w->player.dir_x)] == 0) ?
			w->player.x_cord -= w->player.dir_x : 0;
		(w->map->map[(int)(w->player.y_cord - w->player.dir_y)][(int)w->player.x_cord] == 0) ?
			w->player.y_cord -= w->player.dir_y : 0;
	}
	else if (key_code == 0x7e)//key up;
	{
		(w->map->map[(int)w->player.y_cord][(int)(w->player.x_cord + w->player.dir_x)] == 0) ?
			w->player.x_cord += w->player.dir_x : 0;
		(w->map->map[(int)(w->player.y_cord + w->player.dir_y)][(int)w->player.x_cord] == 0) ?
			w->player.y_cord += w->player.dir_y : 0;
	}
	else if (key_code == 0x7c)//key right
	{
		;
	}
	else if (key_code == 0x7b)
	{
		;
	}
}

/*
** you can find a header will all the key codes that you need on github or
** manually get them
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
		wolf3d_move(key_code, wolf);
	raycast_loop_overhead(wolf);
	return (0);
}
