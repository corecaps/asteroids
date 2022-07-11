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
 * main_init()
 * alloc memory for the data structures                                        *
 * initialize the data structure with correct datas                            *
 * create the main window                                                      *
 * create the img buffer                                                       *
 * hook the render function & key_events                                       *
 ******************************************************************************/

t_data *main_init(void)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
	{
		printf("ALLOCATION ERROR");
		exit(-1);
	}
	data->mlx = mlx_init();
	data->img_buffer = malloc(sizeof(t_buffer));
	if (data->img_buffer == NULL)
	{
		printf("ALLOCATION ERROR");
		exit(-1);
	}
	data->size_x = SIZE_X;
	data->size_y = SIZE_Y;
	data->mlx_win = mlx_new_window(data->mlx, data->size_x,
								   data->size_y, "Asteroids");
	data->img_buffer->img = mlx_new_image(data->mlx,
										  data->size_x + 1,
										  data->size_y + 1);
	data->img_buffer->addr = mlx_get_data_addr(data->img_buffer->img,
											   &data->img_buffer->bit_per_pixel,
											   &data->img_buffer->line_length,
											   &data->img_buffer->endian);
	mlx_hook(data->mlx_win, 2, 1L<<0, win_close, data);
	mlx_loop_hook(data->mlx, render, data);
	return (data);
}

/*******************************************************************************
 * Cleanly free heap allocated space for the data structures                   *
 ******************************************************************************/

void main_memory_clean(t_data *data)
{
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
	t_data *data;

	data = main_init();
	mlx_loop(data->mlx);
	main_memory_clean(data);
	return (0);
}