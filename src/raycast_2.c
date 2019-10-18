/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:02:48 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/18 15:16:43 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** reset the ray values
*/

void	ray(t_wolf *w, int x)
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
** get which direction the wall is facing
*/

void	calc_texture_code(t_wolf *w)
{
	if (w->r.side == 1)
	{
		if (w->r.step_y < 0)
			w->tex_code = 0;
		else
			w->tex_code = 1;
	}
	else
	{
		if (w->r.step_x < 0)
			w->tex_code = 2;
		else
			w->tex_code = 3;
	}
}

/*
** the x (column) value to load the color from in the texture array
*/

void	calc_line_texture(t_wolf *w)
{
	double		which;
	int			tex_x_value;

	if (w->r.side == 0)
		which = w->player.y_cord + w->r.pepindicular * w->r.ray_dir_y;
	else
		which = w->player.x_cord + w->r.pepindicular * w->r.ray_dir_x;
	which -= (int)((which));
	tex_x_value = (int)(which * (double)(TEX_WIDTH));
	if ((w->r.side == 0 && w->r.ray_dir_x > 0) ||
			(w->r.side == 1 && w->r.ray_dir_y < 0))
		tex_x_value = TEX_WIDTH - tex_x_value - 1;
	w->r.tex_x_value = tex_x_value;
}

/*
** the start and finish y values to draw the line for a given x value
*/

void	calc_line_height(t_wolf *w)
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
