/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 14:57:30 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/18 15:21:24 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void				wolf3d_free_map_norm(char *line, char **split)
{
	free(line);
	ft_freestrarr(split);
}

void				raycast_loop_overhead(t_wolf *w)
{
	fill_skybox_floor(w);
	raycast_loop(w);
	mlx_put_image_to_window(w->mlx.mlx_ptr, w->mlx.window_ptr,
			w->mlx.img_ptr, 0, 0);
	ft_bzero(w->mlx.data_start, (WIN_W * WIN_H * 4));
}
