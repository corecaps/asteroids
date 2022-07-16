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
/*******************************************************************************
 * apply translate on asteroid x,y with vector dx,dy                           *
 * warp coordinate                                                             *
 ******************************************************************************/
void	asteroid_translate(t_asteroid *asteroid, t_data *data)
{
	asteroid->x += asteroid->dx * data->elapsed_time;
	asteroid->y += asteroid->dy * data->elapsed_time;
	if (asteroid->x > SIZE_X)
		asteroid->x -= SIZE_X;
	if (asteroid->x < 0)
		asteroid->x = asteroid->x + SIZE_X;
	if (asteroid->y > SIZE_Y)
		asteroid->y -= SIZE_Y;
	if (asteroid->y < 0)
		asteroid->y = asteroid->y + SIZE_Y;
}

/*******************************************************************************
 * go through the asteroids linked list to apply translation with              *
 * asteroid_translate()                                                        *
 ******************************************************************************/

void	asteroid_move(t_data *data)
{
	t_asteroid_lst	*node = data->asteroid_lst;

	while (node)
	{
		asteroid_translate(node->asteroid,data);
		node = node->next;
	}
}

/*******************************************************************************
 * apply translate to player x,y via vector dx,dy & warp coordinates           *
 ******************************************************************************/

void	player_move(t_data *data)
{
	data->player->x += data->player->dx;
	data->player->y += data->player->dy;
	warp_coord_double(&data->player->x,&data->player->y);
}

/*******************************************************************************
 * apply translate to every particles in particles_lst                         *
 ******************************************************************************/

void	partile_move(t_data *data)
{
	t_particle_lst *node = data->particle_lst;
	while (node)
	{
		if (node != NULL && node->particle != NULL)
		{
			node->particle->x += node->particle->dx;
			node->particle->y += node->particle->dy;
			warp_coord_double(&node->particle->x, &node->particle->y);
		}
		node = node->next;
	}
}