//
// Created by corecaps on 12/07/22.
//

#include "asteroid.h"
t_asteroid_lst *last_asteroid(t_asteroid_lst *list)
{
	t_asteroid_lst *node = list;
	while (node->next)
		node = node->next;
	return (node);
}

void init_asteroid(int size, float speed, t_asteroid_lst *asteroid_node);
void draw_asteroid(t_data *data)
{
	t_asteroid_lst *node;

	node = data->asteroid_lst;
	while (node)
	{
		for (int i = 2;i < 20;i += 2)
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
		node = node->next;
	}
}
void pop_asteroid(t_data *data, int size, float speed)
{
	t_asteroid_lst 	*new_node;
	t_asteroid_lst	*last_node;
	new_node = malloc(sizeof (t_asteroid_lst));
	new_node->asteroid = malloc(sizeof (t_asteroid));
	init_asteroid(size, speed, new_node);
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

void init_asteroid(int size, float speed, t_asteroid_lst *asteroid_node)
{
	int offset;

	asteroid_node->asteroid->size = size;
	asteroid_node->asteroid->x = rand() % (SIZE_X - size);
	asteroid_node->asteroid->y = rand() % (SIZE_Y - size);
	asteroid_node->asteroid->velocity = speed;
	asteroid_node->asteroid->angle = 0.0f;
	for (int i = 0; i < 10; i++)
	{
		offset = rand() % (size / 2);
		asteroid_node->asteroid->points[i * 2] = (int) (
				asteroid_node->asteroid->x +
				(((size / 2) + offset) * sin(i * 36 * RADIAN)));
		asteroid_node->asteroid->points[(i * 2) + 1] = (int) (
				asteroid_node->asteroid->y +
				(((size / 2) + offset) * cos(i * 36 * RADIAN)));
	}
}