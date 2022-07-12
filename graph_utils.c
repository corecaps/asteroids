/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_utils.c                                      :+:      :+:    :+:   */
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

/*******************************************************************************
** pixel put to image                                                          *
** found on : https://s.42l.fr/putpximg                                        *
*******************************************************************************/

int my_mlx_pixel_put(t_buffer *data, int x, int y, int color)
{
	char	*dst;

	if (x > SIZE_X || x < 0 || y > SIZE_Y || y < 0)
		return (1);
	dst = data->address + (y * data->line_length + x * (data->bit_per_pixel / 8));
	*(unsigned int*)dst = color;
	return (0);
}
/*******************************************************************************
 * Absolute value utility function                                             *
 ******************************************************************************/

int ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

/*******************************************************************************
** Bresenham's line algorithm                                                  *
** https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm                  *
*******************************************************************************/

void	draw_line_low(int x_from,int y_from,int x_to,int y_to,t_data *data, int color)
{
	int dx, dy, y_inc, D, x, y;
	dx = x_to - x_from;
	dy = y_to - y_from;
	y_inc = 1;
	if (dy < 0)
	{
		y_inc = -1;
		dy = -dy;
	}
	D = (2 * dy) - dx;
	for (x = x_from,y = y_from; x <= x_to;x++)
	{
		my_mlx_pixel_put(data->img_buffer, x, y, color);
		if (D > 0)
		{
			y += y_inc;
			D += 2 * (dy - dx);
		}
		else
			D += 2 * dy;
	}
}

void	draw_line_high(int x_from,int y_from,int x_to,int y_to,t_data *data, int color)
{
	int dx, dy, x_inc, D, x, y;
	dx = x_to - x_from;
	dy = y_to - y_from;
	x_inc = 1;
	if (dx < 0)
	{
		x_inc = -1;
		dx = -dx;
	}
	D = (2 * dx) - dy;
	for (y = y_from, x = x_from;y <= y_to;y ++)
	{
		my_mlx_pixel_put(data->img_buffer, x, y, color);
		if (D > 0)
		{
			x += x_inc;
			D += 2 * (dx - dy);
		}
		else
			D += 2 * dx;
	}
}

void	draw_line(int x_from,int y_from,int x_to,int y_to,t_data *data, int color)
{
	if (ft_abs(y_to - y_from) < ft_abs(x_to - x_from))
	{
		if (x_from > x_to)
		{
			draw_line_low(x_to, y_to, x_from, y_from, data, color);
		}
		else
		{
			draw_line_low(x_from, y_from, x_to, y_to, data, color);
		}
	}
	else
	{
		if (y_from > y_to)
		{
			draw_line_high(x_to, y_to, x_from, y_from, data, color);
		}
		else
		{
			draw_line_high(x_from, y_from, x_to, y_to, data, color);
		}
	}
}

/*******************************************************************************
 * Fill img buffer with 0x0 (non transparent black)                            *
 ******************************************************************************/

void clear_buffer(t_data *data)
{
	for (int y = 0; y < (data->size_y - 1); y ++)
	{
		for (int x = 0;x < (data->size_x - 1);x ++)
			my_mlx_pixel_put(data->img_buffer, x, y, 0);
	}
}

/*******************************************************************************
 * draw the asteroid pointed by *node with the 20 points array in the struct   *
 ******************************************************************************/

void draw_asteroid(t_data *data, const t_asteroid_lst *node)
{
	for (int i = 2; i < 20; i += 2)
	{
		draw_line(node->asteroid->points[i-2],
				  node->asteroid->points[i-1],
				  node->asteroid->points[i],
				  node->asteroid->points[i+1],
				  data,0xFFFFFF);
	}
	draw_line(node->asteroid->points[18],
			  node->asteroid->points[19],
			  node->asteroid->points[0],
			  node->asteroid->points[1],
			  data,0xFFFFFF);
}

/*******************************************************************************
 * call draw_asteroid for every asteroid in the linked list                    *
 ******************************************************************************/

void draw_lst_asteroid(t_data *data)
{
	t_asteroid_lst *node;

	node = data->asteroid_lst;
	while (node)
	{
		draw_asteroid(data, node);
		node = node->next;
	}
}