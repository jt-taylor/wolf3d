/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 18:01:39 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/19 17:02:45 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** didn't make a struct for rays so the x/y are seperated
*/

/*
** caculate the ray distance to the wall , stepping in the direction
** of the ray
*/

static inline void	dda_calc(t_wolf *w)
{
	if (w->r.ray_dir_x < 0)
	{
		w->r.step_x = -1;
		w->r.dist_to_side_x =
			(w->player.x_cord - w->r.map_pos_x) * w->r.change_dist_x;
	}
	else
	{
		w->r.step_x = 1;
		w->r.dist_to_side_x =
			(w->r.map_pos_x + 1.0 - w->player.x_cord) * w->r.change_dist_x;
	}
	if (w->r.ray_dir_y < 0)
	{
		w->r.step_y = -1;
		w->r.dist_to_side_y =
			(w->player.y_cord - w->r.map_pos_y) * w->r.change_dist_y;
	}
	else
	{
		w->r.step_y = 1;
		w->r.dist_to_side_y =
			(w->r.map_pos_y + 1.0 - w->player.y_cord) * w->r.change_dist_y;
	}
}

/*
** so it doesn't try to check out of index array and crash
** the raycast keeps looking until it hits a wall , this
** just makes it so that if it would try to check outside the bounds
** of the map matrix it instead finds the wall at either
** (0,0) // (MAP_WIDTH - 1, MAP_HEIGHT - 1)
*/

static inline void	dda_protect_no_wall(t_wolf *w, int opt)
{
	ft_dprintf(2, "missing wall ?? ray->map_pos = [%d][%d]",
			w->r.map_pos_x, w->r.map_pos_y);
	wolf3d_close(w);
	if (opt)
	{
		w->r.map_pos_x = w->map->width - 1;
		w->r.map_pos_y = w->map->height - 1;
		w->r.hit_wall = 1;
	}
	else
	{
		w->r.map_pos_x = 0;
		w->r.map_pos_y = 0;
		w->r.hit_wall = 1;
	}
}

/*
** loops until the ray hits a wall , the x / y steps are calculated
** seperately because i didn't make a ray struct ,
** numbers over 0 are displayed as walls but
** the collision is just checking if != 0 so negative map values
** are invisible walls
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
		if (w->r.map_pos_y >= w->map->height ||
					w->r.map_pos_x >= w->map->width ||
					w->r.map_pos_x < 0 || w->r.map_pos_y < 0)
			(w->r.map_pos_y >= w->map->height ||
			w->r.map_pos_x >= w->map->width)
				? dda_protect_no_wall(w, 1) : dda_protect_no_wall(w, 0);
		else if (w->map->map[w->r.map_pos_y][w->r.map_pos_x] > 0)
			w->r.hit_wall = 1;
	}
	calc_texture_code(w);
}

/*
** calculates the height of the line to draw
** looking back at this i see that i spelled it pepindicular
** instead of perpendicular I blame vim's auto complete
*/

static inline void	distance_to_wall_and_line_height(t_wolf *w)
{
	if (w->r.side == 0)
		w->r.pepindicular = (w->r.map_pos_x - w->player.x_cord +
				(1 - w->r.step_x) / 2) / w->r.ray_dir_x;
	else
		w->r.pepindicular = (w->r.map_pos_y - w->player.y_cord +
				(1 - w->r.step_y) / 2) / w->r.ray_dir_y;
	if (w->r.pepindicular == 0)
		w->r.pepindicular += .00001;
	calc_line_height(w);
}

/*
** this runs dda for each x column in the window -- calcs the start/end y
** values in that column runs the texture funtions and draws the line
*/

void				raycast_loop(t_wolf *w)
{
	int		x;

	x = 0;
	while (x < WIN_W)
	{
		ray(w, x);
		dda_calc(w);
		dda_run(w);
		distance_to_wall_and_line_height(w);
		calc_line_texture(w);
		ft_draw_line_textured(w, w->line,
				(w->line->yfinal - w->line->ystart), x);
		x++;
	}
}
