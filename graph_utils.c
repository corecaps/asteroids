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

/*******************************************************************************
 * Gestion des evenements liees au touches presses
 * TODO gerer les differents etats du jeu (LVL, UI)
 ******************************************************************************/

int key_pressed(int keycode, t_data *data)
{
	// ESC to quit
	if (keycode == 65307)
		mlx_destroy_window(data->mlx, data->mlx_win);
	if (keycode == 119 || keycode == 65362)
	{
		data->player->dx +=	sin(data->player->angle * RADIAN)
				* 20.0f * data->elapsed_time;
		data->player->dy += -cos(data->player->angle * RADIAN)
				* 20.0f * data->elapsed_time;
		for(int n = 0; n < 2;n += 1)
		{
			push_particle(data, data->player->x + n, data->player->y + n,
						  -data->player->dx, -data->player->dy);
			push_particle(data, data->player->x - n, data->player->y - n,
						  -data->player->dx, -data->player->dy);
		}
	}
	if (keycode == 32)
	{
		printf("fire !!\n");
	}

	if (keycode == 97 || keycode == 65361)
	{
		data->player->angle -= 10.0;
		if (data->player->angle < 0)
			data->player->angle = 360;
	}
	if (keycode == 100 || keycode == 65363)
	{
		data->player->angle += 10.0;
		if (data->player->angle > 360)
			data->player->angle = 0.0;
	}
	return (0);
}

/*******************************************************************************
** pixel put to image                                                          *
** found on : https://s.42l.fr/putpximg                                        *
*******************************************************************************/

int my_mlx_pixel_put(t_buffer *data, int x, int y, int color)
{
	char	*dst;
	warp_coord(&x, &y);
	dst = data->address + (y * data->line_length + x * (data->bit_per_pixel / 8));
	*(unsigned int*)dst = color;
	return (0);
}

/*******************************************************************************
 * warp integer coordinates                                                    *
 ******************************************************************************/

void warp_coord(int *x, int *y)
{
	if ((*x) < 0)
		(*x) = SIZE_X -(-(*x) % SIZE_X);
	if ((*x) > SIZE_X)
		(*x) = (*x) % SIZE_X;
	if ((*y) < 0)
		(*y) = SIZE_Y -(-(*y) % SIZE_Y);
	if ((*y) > SIZE_Y)
		(*y) = (*y) % SIZE_Y;
}

/*******************************************************************************
 * warp floating point coordinates
 ******************************************************************************/

void warp_coord_double(double *x, double *y)
{
	if ((*x) > (double)SIZE_X)
		(*x) -= (double)SIZE_X;
	if ((*x) < 0)
		(*x) = (*x) + (double)SIZE_X;
	if ((*y) > (double)SIZE_Y)
		(*y) -= (double)SIZE_Y;
	if ((*y) < 0)
		(*y) = (*y) + (double)SIZE_Y;
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

void draw_asteroid(t_data *data, t_asteroid *asteroid, double angle_offset)
{
	t_point	*pt_array = asteroid->points;
	int 	size = asteroid->size;
	int 	*offset = asteroid->offset;
	for (int i = 0; i < 10;i ++)
	{
		pt_array[i].x =
				asteroid->x +
				((((double)size / 2) + offset[i]) * sin(((i * 36)+ angle_offset)* RADIAN));
		pt_array[i].y = asteroid->y +
						((((double)size / 2) + offset[i]) * cos(((i * 36)+angle_offset) * RADIAN));
	}
	for (int i = 1; i < 10; i ++)
	{
		draw_line((int)round(pt_array[i - 1].x),
				  (int)round(pt_array[i - 1].y),
				  (int)round(pt_array[i].x),
				  (int)round(pt_array[i].y),
				  data, 0xFFFFFF);
	}
	draw_line((int)round(pt_array[9].x),
			  (int)round(pt_array[9].y),
			  (int)round(pt_array[0].x),
			  (int)round(pt_array[0].y),
			  data,0xFFFFFF);
}

/*******************************************************************************
 * call draw_asteroid for every asteroid in the linked list                    *
 ******************************************************************************/

void draw_lst_asteroid(t_data *data)
{
	t_asteroid_lst *node;
	static double 	angle_offset = 0;

	if (angle_offset == 360)
		angle_offset = 0;
	else
		angle_offset += 0.25;
	node = data->asteroid_lst;
	while (node)
	{
		draw_asteroid(data, node->asteroid, angle_offset);
		node = node->next;
	}
}
/*******************************************************************************
 * Draw player                                                                 *
 ******************************************************************************/
void	draw_player(t_data *data)
{
	double	x= data->player->x;
	double	y= data->player->y;
	double	angle = data->player->angle;
	t_point	pt_array[3];

	pt_array[0].x = x +	(PLAYER_SIZE * sin((angle)* RADIAN));
	pt_array[0].y = y +	(PLAYER_SIZE * -cos((angle)* RADIAN));
	pt_array[1].x = x +	(((double)PLAYER_SIZE / 2) * sin(((angle - 120))* RADIAN));
	pt_array[1].y = y +	(((double)PLAYER_SIZE / 2) * -cos(((angle - 120))* RADIAN));
	pt_array[2].x = x +	(((double)PLAYER_SIZE / 2) * sin(((angle + 120))* RADIAN));
	pt_array[2].y = y +	(((double)PLAYER_SIZE / 2) * -cos(((angle + 120))* RADIAN));

	draw_line((int)round(pt_array[0].x),
			  (int)round(pt_array[0].y),
			  (int)round(pt_array[1].x),
			  (int)round(pt_array[1].y),
			  data,0xffffff);
	draw_line((int)round(pt_array[0].x),
			  (int)round(pt_array[0].y),
			  (int)round(pt_array[2].x),
			  (int)round(pt_array[2].y),
			  data,0xffffff);
	draw_line((int)round(x),
			  (int)round(y),
			  (int)round(pt_array[1].x),
			  (int)round(pt_array[1].y),
			  data,0xffffff);
	draw_line((int)round(x),
			  (int)round(y),
			  (int)round(pt_array[2].x),
			  (int)round(pt_array[2].y),
			  data,0xffffff);
}

/*******************************************************************************
 * go through the particle linked list and draw particles
 ******************************************************************************/

void	draw_particle_lst(t_data *data)
{
	t_particle_lst *node = data->particle_lst;

	if (node == NULL)
		return ;
	while (node)
	{
		if (node->particle->ttl > 0)
		{
			node->particle->ttl --;
			my_mlx_pixel_put(data->img_buffer,
							 (int)round(node->particle->x),
							 (int)round(node->particle->y),
							 0xFF0000);
		}
		node = node->next;
	}
}