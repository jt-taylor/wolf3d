/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 14:57:30 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/19 10:15:31 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** i don't have to explain this do i
** blame norme
*/

void				wolf3d_free_map_norm(char *line, char **split)
{
	free(line);
	ft_freestrarr(split);
}

/*
** so this isn't in raycast because norm (coding guidlines)
** has a limit of 5 functions per file
**
** this draws the base colors for the "skybox" && "floor"
** then runs the raycast loop and pushes the image to the window
** then zeros the image so we don't get afterimages
*/

void				raycast_loop_overhead(t_wolf *w)
{
	fill_skybox_floor(w);
	raycast_loop(w);
	mlx_put_image_to_window(w->mlx.mlx_ptr, w->mlx.window_ptr,
			w->mlx.img_ptr, 0, 0);
	ft_bzero(w->mlx.data_start, (WIN_W * WIN_H * 4));
}
