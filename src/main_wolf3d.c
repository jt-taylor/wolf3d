/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_wolf3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:27:38 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/10 15:52:58 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** not sure how I want to store the maps yet ,
**
** the map is 2d (a la wolfenstein hence raycasting)
** raycasting only needs to calculate for each column on the scren
**
** there are quite a few projects on github that showoff raycasting ;
**
** links : (standard link disclaimer , i dont own or maintain these)
**		2d raycasting ----------------------------------------------------------
**	https://lodev.org/cgtutor/raycasting.html (this goes over wolfensteins
**			raycasting specificaly)
**	https://ncase.me/sight-and-light/
**	https://www.redblobgames.com/articles/visibility/
**	https://www.youtube.com/watch?v=TOEi6T2mtHo
**	^^ https://www.youtube.com/watch?v=vYgIKn7iDH8 ------------------------------
**
** blinky project ---------------------------------------------------------------
** not super relevent but i thought it was cool
** exploration of peripharol vision using the quake demo
** https://www.youtube.com/watch?v=f9v_XN7Wxh8
** https://github.com/shaunlebron/blinky
*/

void		wolf3d_usage_msg(int i, char *str)
{
	ft_dprintf(2, "err_string: %s\nerr_code: %i\n", str, i);
	exit(0);
}

static inline void	wolf_3d_init_keys(t_wolf *wolf)
{
	wolf->mlx.keys.key_left = 0;
	wolf->mlx.keys.key_right = 0;
	wolf->mlx.keys.key_up = 0;
	wolf->mlx.keys.key_down = 0;
}

/*
** This initializes the all of the components of the mlx img functionality
** you don't have to use mlx_image but it's significantly faster than
** just using mlx's builtin pixel_put
**
** Technicaly I'm allowed to use other librarys but only what has counter-
** parts with the mlx lib. so ..?
*/

static void	wolf3d_init_mlx(t_wolf *wolf, char *name)
{
	wolf->mlx.mlx_ptr = mlx_init();
	wolf->mlx.window_ptr =
			mlx_new_window(wolf->mlx.mlx_ptr, WIN_W, WIN_H, name);
	wolf->mlx.img_ptr = mlx_new_image(wolf->mlx.mlx_ptr, WIN_W, WIN_H);
	wolf->mlx.data_start = mlx_get_data_addr(wolf->mlx.img_ptr,
			&wolf->mlx.bpp, &wolf->mlx.size_line, &wolf->mlx.endian);
	wolf_3d_init_keys(wolf);
}

int			main(int ac, char **argv)
{
	t_wolf	*wolf;

	if (!(wolf = (t_wolf *)malloc(sizeof(t_wolf))))
		wolf3d_usage_msg(1, "malloc error");
	if (!(wolf->line = (t_line *)malloc(sizeof(t_wolf))))
		wolf3d_usage_msg(1, "malloc error");
	if (ac != 2)
		wolf3d_usage_msg(0, "Specify exactly one map file");
	wolf->map = populate_map_from_file(argv[1]);
	wolf3d_init_mlx(wolf, argv[1]);
	wolf3d_init_player(wolf);
	raycast_loop_overhead(wolf);
	mlx_hook(wolf->mlx.window_ptr, 2, (1L << 0), wolf3d_key_press, wolf);
	mlx_hook(wolf->mlx.window_ptr, 3, (1L << 1), wolf3d_key_release, wolf);
	mlx_hook(wolf->mlx.window_ptr, 17, 0, wolf3d_close, wolf);
	mlx_loop_hook(wolf->mlx.mlx_ptr, wolf3d_mlx_loop, wolf);
	mlx_loop(wolf->mlx.mlx_ptr);
	return (0);
}
