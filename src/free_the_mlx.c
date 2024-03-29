/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_the_mlx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 22:39:02 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/18 11:46:08 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenGL/gl3.h>
#include <stdlib.h>
#include "mlx_int.h"

/*
** free's the mlx buffers
** this is in it's own file because 'mlx_int.h' has different definitions
** than 'mlx.h' and doesn't compile together
*/

void	free_mlx_ptr(void *mlx_ptr)
{
	free(((mlx_ptr_t *)(mlx_ptr))->font->buffer);
	free(((mlx_ptr_t *)(mlx_ptr))->font);
	free(mlx_ptr);
}
