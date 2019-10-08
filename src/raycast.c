/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 18:01:39 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/07 17:41:44 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** init's the values for each column along the screen
** runs once for each column in the window
*/

static inline void	ray(t_wolf *w, int x)
{
	w->r.camera_x = 2 * x / (double)WIN_W - 1;
	w->r.ray_dir_x = w->player.dir_x + w->player.plane_x * w->r.camera_x;
	w->r.ray_dir_y = w->player.dir_y + w->player.plane_y * w->r.camera_x;
	(w->r.ray_dir_y == 0) ? w->r.ray_dir_y += .001 : 0;
	w->r.map_pos_x = w->player.x_cord;
	w->r.map_pos_y = w->player.y_cord;
	w->r.dist_to_side_x = 0;
	w->r.dist_to_side_y = 0;
	w->r.change_dist_x = fabs(1 / w->r.ray_dir_x);
	w->r.change_dist_y = fabs(1 / w->r.ray_dir_y);
	w->r.pepindicular = 0;
	w->r.step_x = 0;
	w->r.step_y = 0;
	w->r.hit_wall = 0;
	w->r.side = 0;
}

/*
** calculates the values for the dda alg;
** (delta distance alg);
*/

static inline void	dda_calc(t_wolf *w)
{
	//left
	if (w->r.ray_dir_x < 0)
	{
		w->r.step_x = -1;
		w->r.dist_to_side_x = (w->player.x_cord - w->r.map_pos_x) * w->r.change_dist_x;
	}
	//right
	else
	{
		w->r.step_x = 1;
		w->r.dist_to_side_x = (w->r.map_pos_x + 1.0 - w->player.x_cord) * w->r.change_dist_x;
	}
	//up
	if (w->r.ray_dir_y < 0)
	{
		w->r.step_y = -1;
		w->r.dist_to_side_y = (w->player.y_cord - w->r.map_pos_y) * w->r.change_dist_y;
	}
	//down
	else
	{
		w->r.step_y = 1;
		w->r.dist_to_side_y = (w->r.map_pos_y + 1.0 - w->player.y_cord) * w->r.change_dist_y;
	}
}

/*
** actually run dda
*/

static inline void	dda_run(t_wolf *w)
{
	while (w->r.hit_wall == 0)
	{
		if (w->r.dist_to_side_x < w->r.dist_to_side_y)
		{
			w->r.dist_to_side_x += w->r.change_dist_x;
			w->r.map_pos_x += w->r.step_x;
			w->r.side = 0;
		}
		else
		{
			w->r.dist_to_side_y += w->r.change_dist_y;
			w->r.map_pos_y += w->r.step_y;
			w->r.side = 1;
		}
		//need to protect agains out of array access
		//or require the map to be inclosed in walls
		if (w->map->map[w->r.map_pos_x][w->r.map_pos_y] > 0)
			w->r.hit_wall = 1;
	}
}

/*
** the start and finish y values to draw the line for a given x value
*/

static inline void	calc_line_height(t_wolf *w)
{
	int		line_height;

	line_height = (WIN_H / w->r.pepindicular);
	w->line->ystart = -line_height / 2 + WIN_H / 2;
	if (w->line->ystart < 0)
		w->line->ystart = 0;
	if (w->line->ystart >= WIN_H)
		w->line->ystart = 0;
	w->line->yfinal = line_height / 2 + WIN_H / 2;
	if (w->line->yfinal < 0)
		w->line->yfinal = 0;
	if (w->line->yfinal >= WIN_H)
		w->line->yfinal = WIN_H - 1;
}

/*
** calculates the perpindicular distance to the wall rather than the actual distance
** when extremely close to a wall (~15 digits after 0) the wall displays a lil buggy
*/

static inline void	distance_to_wall_and_line_height(t_wolf *w)
{
	if (w->r.side == 0)
		w->r.pepindicular = (w->r.map_pos_x - w->player.x_cord + (1 - w->r.step_x) / 2) / w->r.ray_dir_x;
	else
		w->r.pepindicular = (w->r.map_pos_y - w->player.y_cord + (1 - w->r.step_y) / 2) / w->r.ray_dir_y;
	calc_line_height(w);
}

/*
** using delta distance alg
*/

static inline void				raycast_loop(t_wolf *wolf)
{
	int		x;

	x = 0;
	while (x < WIN_W)
	{
		// these check for wall
		ray(wolf, x);
		dda_calc(wolf);
		dda_run(wolf);
		//calculate the distance to wall;
		//and how big of a line to draw;
		distance_to_wall_and_line_height(wolf);
		wolf->line->xstart = x;
		wolf->line->xfinal = x;
		ft_mlx_draw_line(wolf->line, wolf);
		//fill in texture later
		x++;
	}
}

void				raycast_loop_overhead(t_wolf *w)
{
//	while (1)
	{
		raycast_loop(w);
		mlx_put_image_to_window(w->mlx.mlx_ptr, w->mlx.window_ptr,
				w->mlx.img_ptr, 0, 0);
		ft_bzero(w->mlx.data_start, (WIN_W * WIN_H * 4));
	}
}
