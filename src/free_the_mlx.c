/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_the_mlx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 22:39:02 by jtaylor           #+#    #+#             */
/*   Updated: 2019/10/05 22:40:38 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenGL/gl3.h>
#include <stdlib.h>
#include "mlx_int.h"

void	free_mlx_ptr(void *mlx_ptr)
{
	free(((mlx_ptr_t *)(mlx_ptr))->font->buffer);
	free(((mlx_ptr_t *)(mlx_ptr))->font);
	free(mlx_ptr);
}
