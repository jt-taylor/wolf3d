/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 19:58:25 by jtaylor           #+#    #+#             */
/*   Updated: 2019/09/25 19:33:43 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** this fills in a 2d int array from the input file
**
** I would rather have each map as a seperate c file that just loads the map
** but the map has to be decoupled from the executable so no recompilation
** 	is done to change maps
*/
static t_map	*get_dimensions(char *file)
{
	char	*line;
	char	**arr;
	t_map	*tmp;

	tmp = (t_map *)malloc(sizeof(t_map));
	if (!(tmp->fd = open(file, O_RDONLY)))
		// open error;
		wolf3d_usage_msg(2, "error opening file");
	get_next_line(tmp->fd, &line);
	if (!line || !tmp)
		//exit error read map;
		wolf3d_usage_msg(2, "erorr reading from file || t_map failed malloc");
	arr = ft_strsplit(line, ' ');
	if (!arr[0] || !arr[1])
		//exit erorr;
		wolf3d_usage_msg(3, "dimensions not provided by input file");
	tmp->width = ft_atoi(arr[0]);
	tmp->height = ft_atoi(arr[1]);
	ft_freestrarr(arr);
	free(line);
	return (tmp);
}

static void		parse_line(char **arr, int *l, t_map *tmp)
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

static int		**get_map_data(t_map *tmp)
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
		wolf3d_usage_msg(0, "input dimensios must be between 10 and 50 on\
				either axis");
	tmp->map = get_map_data(tmp);
	tmp->xco = (WIN_W / tmp->width);
	tmp->yco = (WIN_H / tmp->height);
	return (tmp);
}
