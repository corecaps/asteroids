/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:47:57 by jgarcia           #+#    #+#             */
/*   Updated: 2022/07/11 17:48:03 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asteroid.h"

void init_player(t_data *data);

t_data *alloc_data(t_data *data)
{
	data = malloc(sizeof(t_data));
	if (data == NULL)
	{
		printf("ALLOCATION ERROR");
		exit(-1);
	}
	data->img_buffer = malloc(sizeof(t_buffer));
	data->player = malloc(sizeof (t_player));
	if (data->img_buffer == NULL || data->player == NULL)
	{
		printf("ALLOCATION ERROR");
		exit(-1);
	}
	return data;
}

void main_mlx_init(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, data->size_x,
								   data->size_y, "Asteroids");
	data->img_buffer->img = mlx_new_image(data->mlx,
										  data->size_x + 1,
										  data->size_y + 1);
	data->img_buffer->address = mlx_get_data_addr(data->img_buffer->img,
												  &data->img_buffer->bit_per_pixel,
												  &data->img_buffer->line_length,
												  &data->img_buffer->endian);
}

void init_player(t_data *data)
{
	data->player->x = SIZE_X / 2;
	data->player->y = SIZE_Y / 2;
	data->player->accel = 0.0f;
	data->player->velocity = 0.0f;
	data->player->angle = 0.0f;
}

void set_data(t_data *data)
{
	data->size_x = SIZE_X;
	data->size_y = SIZE_Y;
	data->asteroid_lst = NULL;
	pop_asteroid(data,50,((float)(rand() % 100))/10);
	pop_asteroid(data,50,((float)(rand() % 100))/10);
	pop_asteroid(data,50,((float)(rand() % 100))/10);
	pop_asteroid(data,50,((float)(rand() % 100))/10);
	data->time_stamp = 0;
	init_player(data);
}


/*******************************************************************************
 * main_init()
 * alloc memory for the data structures                                        *
 * initialize the data structure with correct data                            *
 * create the main window                                                      *
 * create the img buffer                                                       *
 * hook the render function & key_events                                       *
 ******************************************************************************/

t_data *main_init(void)
{
	t_data *data;

	data = alloc_data(data);
	set_data(data);
	main_mlx_init(data);
	mlx_hook(data->mlx_win, 2, 1L<<0, win_close, data);
	mlx_loop_hook(data->mlx, render, data);
	return (data);
}