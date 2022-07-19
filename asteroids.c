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
	return ((double)((rand() % 400) - 200) / 2);
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

void init_asteroid(int size, t_asteroid_lst *asteroid_node, double dx, double dy,double x,double y)
{
	int offset;

	asteroid_node->asteroid->size = size;
	asteroid_node->asteroid->x = x;
	asteroid_node->asteroid->y = y;
	asteroid_node->asteroid->dx = dx;
	asteroid_node->asteroid->dy = dy;
	for (int i = 0; i < 10; i++)
	{
		asteroid_node->asteroid->offset[i] = rand() % (size / 2);
	}
}

/*******************************************************************************
 * Create a new asteroid and put it @ the end of the linked list               *
 ******************************************************************************/

void push_asteroid(t_data *data, int size, double dx, double dy,double x, double y)
{
	t_asteroid_lst 	*new_node;
	t_asteroid_lst	*last_node;
	new_node = malloc(sizeof (t_asteroid_lst));
	new_node->asteroid = malloc(sizeof (t_asteroid));
	init_asteroid(size, new_node, dx, dy,x,y);
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

void kill_asteroid(t_data *data,t_asteroid_lst *asteroid_node)
{
	t_asteroid_lst	*node = data->asteroid_lst;
	int 			create = 0;
	double 			size,dx, dy,x,y;
	if (node != asteroid_node)
	{
		while (node->next != asteroid_node)
			node = node->next;
	}
	node->next = asteroid_node->next;
	if (asteroid_node->asteroid->size > ASTEROID_SIZE_3)
	{
		size = ((double)asteroid_node->asteroid->size) / 2;
		dx = asteroid_node->asteroid->dx;
		dy = asteroid_node->asteroid->dy;
		x = asteroid_node->asteroid->x;
		y = asteroid_node->asteroid->y;
		create = 1;
	}
	if (asteroid_node->asteroid->size >= ASTEROID_SIZE_1)
		data->player->score += 250;
	else if (asteroid_node->asteroid->size <= ASTEROID_SIZE_2 &&
	asteroid_node->asteroid->size > ASTEROID_SIZE_3)
		data->player->score += 500;
	else if (asteroid_node->asteroid->size <= ASTEROID_SIZE_1)
		data->player->score += 1000;
	if (data->asteroid_lst != asteroid_node)
		free(asteroid_node);
	else
		data->asteroid_lst = data->asteroid_lst->next;
	if (create)
	{
		push_asteroid(data, (int)round(size),
					  -dx,
					  dy,x,y);
		push_asteroid(data, (int)round(size),
					  dx,
					  -dy,x,y);

	}
}