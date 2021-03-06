/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:00:29 by jgarcia           #+#    #+#             */
/*   Updated: 2022/07/16 15:00:36 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asteroid.h"
/*******************************************************************************
 * return last elements from particle linked list                              *
 ******************************************************************************/
t_particle_lst *particle_last(t_particle_lst *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

/*******************************************************************************
 * create a new particle and push it at the end of the linked list             *
 ******************************************************************************/

void	push_particle(t_data *data, double x, double y, double dx, double dy)
{
	t_particle_lst	*new_node;
	t_particle_lst	*last_node;
	new_node = malloc(sizeof(t_particle_lst));
	if (new_node == NULL)
	{
		printf("ALLOCATION ERROR");
		exit(-1);
	}
	new_node->particle = malloc(sizeof(t_particle));
	if (new_node->particle == NULL)
	{
		printf("ALLOCATION ERROR");
		exit(-1);
	}
	new_node->next = NULL;
	new_node->particle->x = x;
	new_node->particle->y = y;
	new_node->particle->dx = dx;
	new_node->particle->dy = dy;
	new_node->particle->ttl = PARTICLE_TTL;
	if (data->particle_lst == NULL)
	{
		data->particle_lst = new_node;
	}
	else
	{
		last_node = particle_last(data->particle_lst);
		last_node->next = new_node;
	}
}

/*******************************************************************************
 * delete particles which time to live (ttl) is down to 0                      *
 ******************************************************************************/

void	clean_particle_lst(t_data *data)
{
	t_particle_lst *node = data->particle_lst;
	t_particle_lst *prev_node = NULL;
	t_particle_lst *del_node = NULL;

	if (node == NULL)
		return ;
	while (node)
	{
		if (node->particle->ttl == 0)
		{
			if (prev_node != NULL)
				prev_node->next = node->next;
			if (node == data->particle_lst && node->next == NULL)
			{
				data->particle_lst = NULL;
				free (node);
				return ;
			}
			else if (node == data->particle_lst && node->next != NULL)
			{
				data->particle_lst = node->next;
			}
			del_node = node;
			node = node->next;
			free(del_node);
		}
		else
		{
			prev_node = node;
			node = node->next;
		}
	}
}
