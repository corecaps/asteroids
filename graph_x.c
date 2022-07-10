/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 16:47:24 by jgarcia           #+#    #+#             */
/*   Updated: 2022/07/10 16:47:26 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asteroid.h"

void win_close(int keycode, t_data *data)
{
	(void) keycode;
	mlx_destroy_window(data->mlx, data->mlx_win);
}

void	my_mlx_pixel_put(t_buffer *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bit_per_pixel / 8));
	*(unsigned int*)dst = color;
}

/* Bresenham's line algorithm
** https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#Line_equation
** https://www.thecrazyprogrammer.com/2017/01/bresenhams-line-drawing-algorithm-c-c.html
*/

void	draw_line(int x_from,int y_from,int x_to,int y_to,t_data *data, int color)
{
	int dx, dy, D, x,y;
	dx = x_to - x_from;
	dy = y_to - y_from;
	D = 2*dy - dx;
	y = y_from;
	x = x_from;
	while (x <= x_to)
	{
		my_mlx_pixel_put(data->dbl_buffer,x,y,color);
		if (D > 0)
		{
			y ++;
			D = D - 2 * dx;
		}
		D = D + 2 * dy;
		x++;
	}
}

void clear_img(t_data *data)
{
	int x,y;
	y = 0;
	while (y < data->size_y)
	{
		x = 0;
		while (x < data->size_x)
		{
			my_mlx_pixel_put(data->dbl_buffer,x,y,0);
			x ++;
		}
		y ++;
	}
}