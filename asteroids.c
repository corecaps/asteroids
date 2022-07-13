/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asteroids.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:52:10 by jgarcia           #+#    #+#             */
/*   Updated: 2022/07/12 20:52:15 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asteroid.h"

/*******************************************************************************
 * return a random double value for dx / dy                                    *
 ******************************************************************************/

double get_rnd_delta()
{
	return ((double)((rand() % 400) - 200) / 200);
}

/*******************************************************************************
 * return a pointer to the last asteroid in the linked list                    *
 ******************************************************************************/

t_asteroid_lst *last_asteroid(t_asteroid_lst *list)
{
	t_asteroid_lst *node = list;
	while (node->next)
		node = node->next;
	return (node);
}

/*******************************************************************************
 * set initial values for a new asteroid                                       *
 ******************************************************************************/

void init_asteroid(int size, t_asteroid_lst *asteroid_node, double dx, double dy)
{
	int offset;

	asteroid_node->asteroid->size = size;
	asteroid_node->asteroid->x = rand() % (SIZE_X - size);
	asteroid_node->asteroid->y = rand() % (SIZE_Y - size);
	asteroid_node->asteroid->dx = dx;
	asteroid_node->asteroid->dy = dy;
	for (int i = 0; i < 10; i++)
	{
		offset = rand() % (size / 2);
		asteroid_node->asteroid->points[i].x = (int) (
				asteroid_node->asteroid->x +
				(((size / 2) + offset) * sin(i * 36 * RADIAN)));
		asteroid_node->asteroid->points[i].y = (int) (
				asteroid_node->asteroid->y +
				(((size / 2) + offset) * cos(i * 36 * RADIAN)));
	}
}

/*******************************************************************************
 * Create a new asteroid and put it @ the end of the linked list               *
 ******************************************************************************/

void pop_asteroid(t_data *data, int size, double dx, double dy)
{
	t_asteroid_lst 	*new_node;
	t_asteroid_lst	*last_node;
	new_node = malloc(sizeof (t_asteroid_lst));
	new_node->asteroid = malloc(sizeof (t_asteroid));
	init_asteroid(size, new_node, dx, dy);
	new_node->next = NULL;
	if (data->asteroid_lst == NULL)
	{
		data->asteroid_lst = new_node;
		return ;
	}
	else
	{
		last_node = last_asteroid(data->asteroid_lst);
		last_node->next = new_node;
	}
}