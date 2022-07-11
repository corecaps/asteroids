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

int main(void)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
	{
		printf("ALLOCATION ERROR");
		return (-1);
	}
	data->mlx = mlx_init();
	data->dbl_buffer = malloc(sizeof(t_buffer));
	if (data->dbl_buffer == NULL)
	{
		printf("ALLOCATION ERROR");
		return (-1);
	}
	data->size_x = SIZE_X;
	data->size_y = SIZE_Y;
	data->mlx_win = mlx_new_window(data->mlx, data->size_x,
								   data->size_y, "Asteroids");
	data->dbl_buffer->img = mlx_new_image(data->mlx,
										  data->size_x + 1,
										  data->size_y + 1);
	data->dbl_buffer->addr = mlx_get_data_addr(data->dbl_buffer->img,
											   &data->dbl_buffer->bit_per_pixel,
											   &data->dbl_buffer->line_length,
											   &data->dbl_buffer->endian);
	mlx_hook(data->mlx_win, 2, 1L<<0, win_close, data);
	mlx_loop_hook(data->mlx, render, data);
	mlx_loop(data->mlx);
	return (0);
}