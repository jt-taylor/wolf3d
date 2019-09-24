/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:28:10 by jtaylor           #+#    #+#             */
/*   Updated: 2019/09/24 14:35:23 by jtaylor          ###   ########.fr       */
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
** only used to populate the map
*/
typedef struct	s_map
{
	//map size at start of file
	int		height;
	int		width;
	int		fd;
}				t_map;

/*
** I might just use sdl2 instead of mlx not sure yet
*/
typedef struct	s_wolf_mlx
{
	void		*mlx_ptr;
	void		*window_ptr;
	void		*img_ptr;
	void		*data_start;
	int			bpp;
	int			endian;
	int			size_line;
}				t_wolf_mlx;

typedef struct	s_wolf
{
	t_wolf_mlx	mlx;
	int			**map;
}				t_wolf;

/*
** main_wolf3d.c
*/

void			wolf3d_usage_msg(int i, char *str);

/*
** populate_map.c
*/
int				**populate_map_from_file(char *file);


#endif
