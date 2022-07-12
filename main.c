/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 16:44:10 by jgarcia           #+#    #+#             */
/*   Updated: 2022/07/10 16:44:14 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asteroid.h"

/*******************************************************************************
 * Cleanly free heap allocated space for the data structures                   *
 ******************************************************************************/

void main_memory_clean(t_data *data)
{
	// TODO Clean player structure
	// TODO Clean asteroid_lst linked list
	mlx_destroy_image(data->mlx,data->img_buffer->img);
	free(data->img_buffer);
	free(data->mlx);
	free(data);
}

/*******************************************************************************
 * Main takes no args at the moment, config is done in asteroid.h              *
 ******************************************************************************/

int main(void)
{
	t_data *data = NULL;

	data = main_init();
	mlx_loop(data->mlx);
	main_memory_clean(data);
	return (0);
}