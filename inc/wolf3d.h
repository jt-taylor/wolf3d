/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:28:10 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/14 21:09:21 by jtaylor          ###   ########.fr       */
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
# define WIN_W (1024 * 2)
# define WIN_H (512 * 2)
# define TEX_SIZE 64

/*
** the map data
*/
typedef struct	s_map
{
	int		height;
	int		width;
	int		xstart;
	int		ystart;
	int		fd;
	int		**map;
}				t_map;

/*
** Player data
*/

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
}				t_player;

/*
** variables for the raycaster
*/

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

/*
** texture data
*/

typedef struct	s_texture
{
//	int			bpp;
//	int			sizeline;
//	int			endian;
//	void		*img;
//	char		*data;
	int			texture[TEX_SIZE][TEX_SIZE];

}				t_texture;

/*
** variables for bresenhams line drawing alg
*/

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

/*
** unused atm
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
** mlx doesn't currently have a loop for key repeat atm
** so keypress and keyrelease should toggle variables so the mlx loop
** can know that a key is being held down
** one variable for each key that we want to hold down
*/

typedef struct	s_wolf_mlx_key_hold
{
	int			key_up;
	int			key_down;
	int			key_left;
	int			key_right;
}				t_wolf_mlx_key_hold;

/*
** all the pointers to use for mlx
*/

typedef struct	s_wolf_mlx
{
	void					*mlx_ptr;
	void					*window_ptr;
	void					*img_ptr;
	char					*data_start;
	int						bpp;
	int						endian;
	int						size_line;
	t_wolf_mlx_key_hold		keys;
}				t_wolf_mlx;

/*
** holds all the other structs
*/

typedef struct	s_wolf
{
	t_wolf_mlx	mlx;
	t_map		*map;
	t_player	player;
	t_line		*line;
	t_shape		*shape;
	t_raycast	r;
	t_texture	tex[4];
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
** image_interface.c
*/

void		test(t_wolf *wolf);
void		ft_mlx_draw_line(t_line *l, t_wolf *wolf);
void		ft_mlx_pixel_put(t_wolf *wolf, int x_cord, int y_cord);
void		ft_mlx_pixel_put_texture(t_wolf *wolf, int x_cord, int y_cord,
		int texture_code);
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
int		wolf3d_key_release(int key_code, t_wolf *wolf);

/*
** mlx_move_options.c
*/

int			wolf3d_mlx_loop(t_wolf *wolf);

/*
** free_the_mlx
*/

void	free_mlx_ptr(void *mlx_ptr);

/*
** basic_textures.c
*/

void		basic_texture_handle(t_wolf *wolf);

#endif
