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
t_bullet_lst *bullet_last(t_bullet_lst *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

/*******************************************************************************
 * create a new particle and push it at the end of the linked list             *
 ******************************************************************************/

void	push_bullet(t_data *data, double x, double y, double dx, double dy)
{
	t_bullet_lst 	*new_node;
	t_bullet_lst 	*last_node;
	new_node = malloc(sizeof(t_bullet_lst));
	if (new_node == NULL)
	{
		printf("ALLOCATION ERROR");
		exit(-1);
	}
	new_node->bullet = malloc(sizeof(t_bullet));
	if (new_node->bullet == NULL)
	{
		printf("ALLOCATION ERROR");
		exit(-1);
	}
	new_node->next = NULL;
	new_node->bullet->x = x ;
	new_node->bullet->y = y;
	new_node->bullet->dx = dx;
	new_node->bullet->dy = dy;
	new_node->bullet->ttl = BULLET_TTL;
	if (data->bullet_lst == NULL)
	{
		data->bullet_lst = new_node;
	}
	else
	{
		last_node = bullet_last(data->bullet_lst);
		last_node->next = new_node;
	}
}

/*******************************************************************************
 * delete particles which time to live (ttl) is down to 0                      *
 ******************************************************************************/

void	clean_bullet_lst(t_data *data)
{
	t_bullet_lst *node = data->bullet_lst;
	t_bullet_lst *prev_node = NULL;
	t_bullet_lst *del_node = NULL;

	if (node == NULL)
		return ;
	while (node)
	{
		if (node->bullet->ttl == 0)
		{
			if (prev_node != NULL)
				prev_node->next = node->next;
			if (node == data->bullet_lst && node->next == NULL)
			{
				data->bullet_lst = NULL;
				free (node);
				return ;
			}
			else if (node == data->bullet_lst && node->next != NULL)
			{
				data->bullet_lst = node->next;
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