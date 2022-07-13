/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:48:57 by jgarcia           #+#    #+#             */
/*   Updated: 2022/07/13 13:49:05 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asteroid.h"

void	asteroid_translate(t_asteroid *asteroid, t_data *data)
{
	t_point	*pt_array = asteroid->points;

	asteroid->x += asteroid->dx * data->elapsed_time;
	asteroid->y += asteroid->dy * data->elapsed_time;
	for (int i = 0;i < 10;i ++)
	{
		pt_array[i].x += asteroid->dx;
		pt_array[i].y += asteroid->dy;
	}
}

void	asteroid_rotate(t_asteroid *asteroid, t_data *data)
{
	t_point	*pt_array = asteroid->points;
	int		i = 0;

}

void	asteroid_move(t_data *data)
{
	t_asteroid_lst	*node = data->asteroid_lst;

	while (node)
	{
		asteroid_translate(node->asteroid,data);
		asteroid_rotate(node->asteroid,data);
		node = node->next;
	}
}