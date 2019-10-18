/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 19:58:25 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/18 16:24:35 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** this file parses from the supplied map file , the map file should be in the
** following format :
** width           height
** start_x         start_y
** map values ...
** -----------------------------------------------------------------------------
** example
** -----------------------------------------------------------------------------
** 24 24
** 2 2
** 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
** 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
** 1 0 0 0 0 0 0 0 7 0 0 0 7 0 0 0 0 0 0 0 0 0 0 1
** 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
** 1 0 0 0 0 0 2 2 2 2 2 0 0 0 0 3 0 3 0 3 0 0 0 1
** 1 0 0 0 0 0 2 0 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0 1
** 1 0 0 0 0 0 2 0 0 0 2 0 0 0 0 3 0 0 0 3 0 0 0 1
** 1 0 0 0 0 0 2 0 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0 1
** 1 0 0 0 0 0 2 2 0 2 2 0 0 0 0 3 0 3 0 3 0 0 0 1
** 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
** 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
** 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
** 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
** 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
** 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
** 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
** 1 4 4 4 4 4 4 4 4 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
** 1 4 0 4 0 0 0 0 4 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
** 1 4 0 0 0 0 5 0 4 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
** 1 4 0 4 0 0 0 0 4 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
** 1 4 0 4 4 4 4 4 4 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
** 1 4 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
** 1 4 4 4 4 4 4 4 4 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
** 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
** -----------------------------------------------------------------------------
** other notes
** if the dimensions of the map are smaller than the inputed supplied dimensions
** 	then the rest of the points in the int ** are set to 0
** it's a good idea to have the outermost layer of the map be 1 (or any wall)
** 	the raycaster should handle it if it isn't but you can
** 		never get all of the edge cases
** try to make sure the map is enclosed in walls , the raycaster won't crash but
** 	it looks a bit buggy , could improve it but i think the modus operandi is
** 	on making a map that has no walls
** 		the raycaster will calculate missing walls at either (0, 0) or
** 		(width - 1, height - 1) ,
** 		so it doesn't segfault from accesing outside of the int ** array,
** 		the intersections of walls are unaligned in this case
** try not to start inside a wall boundry if (1, 1) facing (0, 0) , -->
** 		doesn't display the wall while inside it
*/

static inline void	grab_start_cord(int fd, char **arr, t_map *map)
{
	char	*line;
	char	**split;

	map->width = ft_atoi(arr[0]);
	map->height = ft_atoi(arr[1]);
	get_next_line(fd, &line);
	split = ft_strsplit(line, ' ');
	if (split[2] || !split[0] || !split[1])
	{
		wolf3d_free_map_norm(line, split);
		wolf3d_usage_msg(2, "erorr reading (x,y) start");
	}
	else
	{
		map->xstart = ft_atoi(split[0]);
		map->ystart = ft_atoi(split[1]);
		if (map->xstart <= 0 || map->xstart >= map->width ||
				map->ystart <= 0 || map->ystart >= map->width)
		{
			wolf3d_free_map_norm(line, split);
			wolf3d_usage_msg(2, "starting (x,y) must be between 0 && width");
		}
	}
	wolf3d_free_map_norm(line, split);
}

/*
** this specifically malloc's the struct s_map
** and grabs the supplied width / height dimensions;
*/

static t_map		*get_dimensions(char *file)
{
	char	*line;
	char	**arr;
	t_map	*tmp;

	tmp = (t_map *)malloc(sizeof(t_map));
	if (!(tmp->fd = open(file, O_RDONLY)))
	{
		free(tmp);
		wolf3d_usage_msg(2, "error opening file");
	}
	get_next_line(tmp->fd, &line);
	if (!line || !tmp)
		wolf3d_usage_msg(2, "erorr reading from file || less much less likely\
				t_map failed malloc");
	arr = ft_strsplit(line, ' ');
	if (!arr[0] || !arr[1])
		ft_dprintf(2, "dimensions not provided by input file");
	else
		grab_start_cord(tmp->fd, arr, tmp);
	ft_freestrarr(arr);
	free(line);
	return (tmp);
}

static void			parse_line(char **arr, int *l, t_map *tmp)
{
	int		x;
	int		fail;

	x = 0;
	fail = 0;
	while (x < tmp->width)
	{
		if (!fail && !*(arr + x))
			fail++;
		l[x] = !(fail) ? ft_atoi(arr[x]) : 0;
		x++;
	}
}

static int			**get_map_data(t_map *tmp)
{
	int		**map;
	char	*line;
	char	**arr;
	int		y;

	y = 0;
	map = (int **)malloc(sizeof(int *) * (tmp->height));
	while (get_next_line(tmp->fd, &line) || y < tmp->height)
	{
		map[y] = (int *)malloc(sizeof(int) * (tmp->width));
		if (line[0] && !ft_strstr(line, " "))
		{
			ft_dprintf(2, "line == '%s'", line);
			wolf3d_usage_msg(2, "no spaces in line");
		}
		arr = ft_strsplit(line, ' ');
		parse_line(arr, map[y], tmp);
		free(line);
		ft_freestrarr(arr);
		y++;
	}
	free(line);
	return (map);
}

t_map				*populate_map_from_file(char *file)
{
	t_map	*tmp;

	tmp = get_dimensions(file);
	if (tmp->width < 10 || tmp->height < 10)
		wolf3d_usage_msg(0, "input dimensios must be greater then 10 on\
				either axis");
	tmp->map = get_map_data(tmp);
	if (tmp->map[tmp->ystart][tmp->xstart] != 0)
	{
		wolf3d_usage_msg(2, "x / y start_cordinates are not 0");
	}
	return (tmp);
}
