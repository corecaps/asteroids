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

int my_mlx_pixel_put(t_buffer *data, int x, int y, int color)
{
	char	*dst;

	if (x > SIZE_X || x < 0)
	{
//		printf("trying to draw outside canvas x:%d y%d", x, y);
		return (1);
	}
	if (y > SIZE_Y || y < 0)
	{
//		printf("trying to draw outside canvas x:%d y%d", x, y);
		return (1);
	}
	dst = data->addr + (y * data->line_length + x * (data->bit_per_pixel / 8));
	*(unsigned int*)dst = color;
	return (0);
}

/* Bresenham's line algorithm
** https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#Line_equation
*/
static int ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}
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
	y = y_from;
	for (x = x_from; x <= x_to;x++)
	{
		my_mlx_pixel_put(data->dbl_buffer,x,y,color);
		if (D > 0)
		{
			y += y_inc;
			D = D + (2 * (dy - dx));
		}
		else
			D = D + 2 * dy;
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
	x = x_from;
	for (y = y_from;y <= y_to;y ++)
	{
		my_mlx_pixel_put(data->dbl_buffer,x,y,color);
		if (D > 0)
		{
			x += x_inc;
			D = D + (2 * (dx - dy));
		}
		else
			D = D + 2 * dx;
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

void clear_img(t_data *data)
{
	int x,y;
	y = 0;
	while (y < data->size_y - 1)
	{
		x = 0;
		while (x < data->size_x - 1)
		{
			my_mlx_pixel_put(data->dbl_buffer,x,y,0);
			x ++;
		}
		y ++;
	}


}

int render(t_data *data)
{
	static int frame = 0;
	static int anim = 1;
	int			i = 0;
	int 		j = 0;

	if (frame == 0)
	{
		clear_img(data);
		frame ++;
	}
	else if (frame == 1)
	{
		if (anim >= 20)
			anim = 1;
		else
			anim ++;
		i = 0;
		j = 0;
		while (i < data->size_x)
		{
			draw_line(i, j,data->size_x,data->size_y,data,0x7F0000);
			i += anim;
		}
		j = 0;
		i = 0;
		while (j < data->size_y)
		{
			draw_line(i, j,data->size_x,data->size_y,data,0x7F00);
			j += anim;
		}
		i = 0;
		j = SIZE_Y;
		while (i < data->size_x)
		{
			draw_line(i, j,0,0,data,0x7F0000);
			i += anim;
		}
		j = 0;
		i = SIZE_X;
		while (j < data->size_y)
		{
			draw_line(i, j,0,0,data,0x7F00);
			j += anim;
		}

		frame ++;
	}
	else if (frame == 2)
	{
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->dbl_buffer->img, 0 ,0);
		frame ++;
	}
	else if (frame >= FRAME_MAX)
	{
		frame = 0;
	}
	else
	{
		frame ++;
	}
	return (0);
}