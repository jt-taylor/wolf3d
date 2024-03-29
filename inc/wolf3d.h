/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:28:10 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/19 10:15:59 by jtaylor          ###   ########.fr       */
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
# define WIN_W (1024)
# define WIN_H (512)
# define TEX_HEIGHT 64
# define TEX_WIDTH 64

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
	int		tex_x_value;
}				t_raycast;

/*
** texture data
*/

typedef struct	s_texture
{
	int				x;
	int				y;
	int				texture[TEX_HEIGHT][TEX_WIDTH];
}				t_texture;

/*
** used to be for bresenhams alg , but you don't really need that
** 		for raycasting lul
*/

typedef struct	s_line
{
	int		ystart;
	int		yfinal;
}				t_line;

/*
** mlx doesn't currently have a loop for key repeat atm
** so keypress and keyrelease should toggle variables so the mlx loop
** can know that a key is being held down
** one variable for each key that we want to hold down
*/

typedef struct	s_wolf_mlx_key_hold
{
	int				key_up;
	int				key_down;
	int				key_left;
	int				key_right;
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
	t_raycast	r;
	t_texture	tex[4];
	int			tex_code;
}				t_wolf;

/*
** main_wolf3d.c
*/

void			wolf3d_usage_msg(int i, char *str);

/*
** populate_map.c
*/

t_map			*populate_map_from_file(char *file);

/*
** image_interface.c
*/

void			ft_draw_line_textured(t_wolf *w, t_line *l,
		int line_height, int x);
void			fill_skybox_floor(t_wolf *w);

/*
** raycast.c
*/

void			raycast_loop(t_wolf *w);

/*
** raycast_2.c
*/

void			ray(t_wolf *w, int x);
void			calc_texture_code(t_wolf *w);
void			calc_line_texture(t_wolf *w);
void			calc_line_height(t_wolf *w);

/*
** player.c
*/

void			wolf3d_init_player(t_wolf *wolf);

/*
** wolf3d_mlx_hooks.c
*/

int				wolf3d_key_press(int key_code, t_wolf *wolf);
int				wolf3d_close(void *param);
int				wolf3d_key_release(int key_code, t_wolf *wolf);

/*
** mlx_move_options.c
*/

int				wolf3d_mlx_loop(t_wolf *wolf);

/*
** free_the_mlx
*/

void			free_mlx_ptr(void *mlx_ptr);

/*
** basic_textures.c
*/

void			basic_texture_handle(t_wolf *wolf);

/*
** more_texture_patterns.c
*/

void			load_pattern5(t_wolf *w, int tex_number, int color, int color2);
void			load_pattern6(t_wolf *w, int tex_number, int color, int color2);
void			load_pattern7(t_wolf *w, int tex_number, int color, int color2);

/*
** misc.c
*/

void			wolf3d_free_map_norm(char *line, char **split);
void			raycast_loop_overhead(t_wolf *w);

#endif
