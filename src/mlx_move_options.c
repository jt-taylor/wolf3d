/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_move_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 20:25:21 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/10 16:08:10 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static inline void		move_wolf_camera_plane(t_wolf *w, int opt)
{
	double		rot;
	double		old;

	rot = .02;
	if (opt == 1)//key right
	{
		old = w->player.dir_x;
		w->player.dir_x = w->player.dir_x * cos(-rot) - w->player.dir_y * sin(-rot);
		w->player.dir_y = old * sin(-rot) + w->player.dir_y * cos(-rot);
		old = w->player.plane_x;
		w->player.plane_x = w->player.plane_x * cos(-rot) - w->player.plane_y * sin(-rot);
		w->player.plane_y = old * sin(-rot) + w->player.plane_y * cos(-rot);
	}
	else if (opt == 2)//key left
	{
		old = w->player.dir_x;
		w->player.dir_x = w->player.dir_x * cos(rot) - w->player.dir_y * sin(rot);
		w->player.dir_y = old * sin(rot) + w->player.dir_y * cos(rot);
		old = w->player.plane_x;
		w->player.plane_x = w->player.plane_x * cos(rot) - w->player.plane_y * sin(rot);
		w->player.plane_y = old * sin(rot) + w->player.plane_y * cos(rot);
	}
}

static inline void		move_forward_backward(t_wolf *w, int opt)
{
	static double		ms;

	ms = .03;
	if (opt == 1)//key up;
	{
		(w->map->map[(int)w->player.y_cord][(int)(w->player.x_cord + w->player.dir_x * ms)] == 0) ?
			w->player.x_cord += w->player.dir_x * ms: 0;
		(w->map->map[(int)(w->player.y_cord + w->player.dir_y * ms)][(int)w->player.x_cord] == 0) ?
			w->player.y_cord += w->player.dir_y * ms : 0;
	}
	else if (opt == -1)//key down
	{
		(w->map->map[(int)w->player.y_cord][(int)(w->player.x_cord - w->player.dir_x * ms)] == 0) ?
			w->player.x_cord -= w->player.dir_x * ms : 0;
		(w->map->map[(int)(w->player.y_cord - w->player.dir_y * ms)][(int)w->player.x_cord] == 0) ?
			w->player.y_cord -= w->player.dir_y * ms : 0;
	}
}

int			wolf3d_mlx_loop(t_wolf *wolf)
{
	if (wolf->mlx.keys.key_up == 1 || wolf->mlx.keys.key_down == 1)
		(wolf->mlx.keys.key_up) ? move_forward_backward(wolf, 1) :
			move_forward_backward(wolf, -1);
	if (wolf->mlx.keys.key_right || wolf->mlx.keys.key_left)
		(wolf->mlx.keys.key_right) ? move_wolf_camera_plane(wolf, 1) :
			move_wolf_camera_plane(wolf, 2);
	raycast_loop_overhead(wolf);
	return (0);
}
