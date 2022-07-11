/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:43:18 by jgarcia           #+#    #+#             */
/*   Updated: 2022/07/11 16:43:21 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asteroid.h"

void test_line(t_data *data)
{
	static int	anim = 1;
	int 		i;
	int 		j;
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
		draw_line(i, j,SIZE_X - i,SIZE_Y - j,data,0x7F00);
		j += anim;
	}

}

void	test_line2(t_data *data)
{
	static anim_x = 0;
	static anim_y = 0;

	if (anim_x >= SIZE_X-1)
		anim_x = 0;
	else
		anim_x ++;
	if (anim_y >= SIZE_Y-1)
		anim_y = 0;
	else
		anim_y ++;
	draw_line(anim_x,0,SIZE_X-1-anim_x,SIZE_Y-1,data,0xFF0000);
	draw_line(SIZE_X - 1,anim_y,0,SIZE_Y-1-anim_y,data,0xFF00);
}