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

/*******************************************************************************
 * allocate space on the heap for the game basic data structures               *
 * in case of error a message is printed and exit(-1) is called                *
 ******************************************************************************/

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

/*******************************************************************************
 * initialize the mlx library, create the main window and the img buffer       *
 ******************************************************************************/

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

/*******************************************************************************
 * set initials values for the player struct                                   *
 ******************************************************************************/

void init_player(t_data *data)
{
	data->player->x = SIZE_X / 2;
	data->player->y = SIZE_Y / 2;
	data->player->accel = 0.0f;
	data->player->velocity = 0.0f;
	data->player->angle = 0.0f;
}

/*******************************************************************************
 * set initial values for the data structures, pop the first asteroids         *
 ******************************************************************************/

void set_data(t_data *data)
{
	data->size_x = SIZE_X;
	data->size_y = SIZE_Y;
	data->asteroid_lst = NULL;
	for (int n=0;n < 10;n++)
		pop_asteroid(data, 50, get_rnd_delta(), get_rnd_delta());
	clock_gettime(CLOCK_MONOTONIC, &data->last_frame);
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
	t_data *data = NULL;
	srand(time(NULL));
	data = alloc_data(data);
	set_data(data);
	main_mlx_init(data);
	mlx_hook(data->mlx_win, 2, 1L<<0, win_close, data);
	mlx_loop_hook(data->mlx, render, data);
	return (data);
}