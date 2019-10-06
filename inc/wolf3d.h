/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:28:10 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/05 22:41:24 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include "mlx.h"
# include "ft_printf.h"
# include <math.h>
# include <fcntl.h>

/*
** MACRO(s[?])
*/
# define WIN_W 1024
# define WIN_H 512

/*
** the map data ,
** width and height so we don't check out of bounds memory;
** [M U[M#U
*/
typedef struct	s_map
{
	int		height;
	int		width;
	int		xco;
	int		yco;
	int		fd;
	int		**map;
}				t_map;

typedef struct	s_player
{
	double	x_cord;
	double	y_cord;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	time;
	double	old_time;
	//not sure what to use for the looking direction yet
	//inventory ?
	//modifiers ?
	
}				t_player;

typedef struct	s_raycast
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	dist_to_side_x;
	double	dist_to_side_y;
	double	change_dist_x;
	double	change_dist_y;
	double	pepindicular;
	int		map_pos_x;
	int		map_pos_y;
	int		step_x;
	int		step_y;
	int		hit_wall;
	int		side;
}				t_raycast;

typedef struct	s_line
{
	int		xstart;
	int		xfinal;
	int		ystart;
	int		yfinal;
	int		dx;
	int		sx;
	int		dy;
	int		sy;
	int		err1;
	int		err2;
}				t_line;

/*change this to a queue system
 */
typedef struct	s_shape
{
	int		q1x;
	int		q1y;
	int		q2x;
	int		q2y;
	int		q3x;
	int		q3y;
	int		q4x;
	int		q4y;
}				t_shape;

/*
** I might just use sdl2 instead of mlx not sure yet
*/
typedef struct	s_wolf_mlx
{
	void		*mlx_ptr;
	void		*window_ptr;
	void		*img_ptr;
	char		*data_start;
	int			bpp;
	int			endian;
	int			size_line;
}				t_wolf_mlx;

typedef struct	s_wolf
{
	t_wolf_mlx	mlx;
	t_map		*map;
	t_player	player;
	t_line		*line;
	t_shape		*shape;
	t_raycast	r;
}				t_wolf;

/*
** main_wolf3d.c
*/

void			wolf3d_usage_msg(int i, char *str);

/*
** populate_map.c
*/

t_map				*populate_map_from_file(char *file);

/*
** 2d_display
*/

//void		display_2d_grid(t_wolf *wolf);
//void		wolf_2d_check_adjacent(t_wolf *w, int x, int y);

/*
** image_interface.c
*/

void		test(t_wolf *wolf);
void		ft_mlx_draw_line(t_line *l, t_wolf *wolf);
void		ft_mlx_pixel_put(t_wolf *wolf, int x_cord, int y_cord);
void		ft_mlx_draw_quad(t_wolf *wolf, t_shape *shape);

/*
** raycast.c
*/

void		raycast_loop_overhead(t_wolf *w);

/*
** player.c
*/

void		wolf3d_init_player(t_wolf *wolf);

/*
** wolf3d_mlx_hooks.c
*/

int		wolf3d_key_press(int key_code, t_wolf *wolf);
int		wolf3d_close(void *param);

/*
** free_the_mlx
*/

void	free_mlx_ptr(void *mlx_ptr);

#endif
