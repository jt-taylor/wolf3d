/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_mlx_hooks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 15:38:56 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/11 11:03:38 by jtaylor          ###   ########.fr       */
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
** moving forward and backwards is just adding the x/y components of the directional ray
** the collision check the x / y component seperately because i didn't make a struct for vectors/rays
** panning left / right (ie moving the camera) we need to change the camera direction && plane
** to rotate the camera plane we need to change the dirrection vector and the camera plane porpotionaly
*/

//static inline void	wolf3d_move(int key_code, t_wolf *w)
//{
//	//need to add in the timeing functions to decouple the rnedering from the
//	//making the steps smaller will reduce the angle 
//	//movement speed
//	double	ms;
//	double	old;
//	double	rot;
//
//	rot = .3;
//	ms = 0.05;
//	if (key_code == 0x7d)//key down
//	{
//		(w->map->map[(int)w->player.y_cord][(int)(w->player.x_cord - w->player.dir_x * ms)] == 0) ?
//			w->player.x_cord -= w->player.dir_x * ms : 0;
//		(w->map->map[(int)(w->player.y_cord - w->player.dir_y * ms)][(int)w->player.x_cord] == 0) ?
//			w->player.y_cord -= w->player.dir_y * ms : 0;
//	}
//	else if (key_code == 0x7e)//key up;
//	{
//		(w->map->map[(int)w->player.y_cord][(int)(w->player.x_cord + w->player.dir_x * ms)] == 0) ?
//			w->player.x_cord += w->player.dir_x * ms: 0;
//		(w->map->map[(int)(w->player.y_cord + w->player.dir_y * ms)][(int)w->player.x_cord] == 0) ?
//			w->player.y_cord += w->player.dir_y * ms : 0;
//	}
//	else if (key_code == 0x7c)//key right
//	{
//		old = w->player.dir_x;
//		w->player.dir_x = w->player.dir_x * cos(-rot) - w->player.dir_y * sin(-rot);
//		w->player.dir_y = old * sin(-rot) + w->player.dir_y * cos(-rot);
//		old = w->player.plane_x;
//		w->player.plane_x = w->player.plane_x * cos(-rot) - w->player.plane_y * sin(-rot);
//		w->player.plane_y = old * sin(-rot) + w->player.plane_y * cos(-rot);
//	}
//	else if (key_code == 0x7b)//key left
//	{
//		old = w->player.dir_x;
//		w->player.dir_x = w->player.dir_x * cos(rot) - w->player.dir_y * sin(rot);
//		w->player.dir_y = old * sin(rot) + w->player.dir_y * cos(rot);
//		old = w->player.plane_x;
//		w->player.plane_x = w->player.plane_x * cos(rot) - w->player.plane_y * sin(rot);
//		w->player.plane_y = old * sin(rot) + w->player.plane_y * cos(rot);
//	}
//}

/*
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
