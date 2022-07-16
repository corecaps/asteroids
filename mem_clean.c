/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:42:03 by jgarcia           #+#    #+#             */
/*   Updated: 2022/07/12 21:42:07 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asteroid.h"

/*******************************************************************************
 * Cleanly free heap allocated space for the data structures                   *
 ******************************************************************************/

void main_memory_clean(t_data *data)
{
	t_asteroid_lst *ast_node = data->asteroid_lst;
	t_asteroid_lst *ast_tmp = NULL;
	t_particle_lst *part_node = data->particle_lst;
	t_particle_lst *part_tmp = NULL;

	mlx_destroy_image(data->mlx,data->img_buffer->img);
	free(data->player);
	if (ast_node != NULL)
	{
		while (ast_node)
		{
			if (ast_node->asteroid != NULL)
				free(ast_node->asteroid);
			ast_tmp = ast_node;
			ast_node = ast_node->next;
			free(ast_tmp);
		}
	}
	if (part_node != NULL)
	{
		while(part_node)
		{
			if (part_node->particle != NULL)
				free(part_node->particle);
			part_tmp = part_node;
			part_node = part_node->next;
			free(part_tmp);
		}
	}
	free(data->img_buffer);
	free(data->mlx);
	free(data);
}