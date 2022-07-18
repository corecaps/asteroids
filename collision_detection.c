//
// Created by corecaps on 18/07/22.
//

#include "asteroid.h"

int is_in_circle(double x, double y, double radius,double x_b,double y_b)
{
	double dx = x - x_b;
	double dy = y - y_b;
	if (sqrt(dx * dx + dy * dy) < radius)
		return (1);
	else
		return (0);
}

int bullet_collide(t_asteroid_lst *asteroid_node,t_data *data)
{
	t_bullet_lst *bullet_node = data->bullet_lst;
	int collision = 0;
	while (bullet_node)
	{
		collision += is_in_circle(asteroid_node->asteroid->x,
								  asteroid_node->asteroid->y,
								  (double)(asteroid_node->asteroid->size * 2),
								  bullet_node->bullet->x,
								  bullet_node->bullet->y);
		bullet_node = bullet_node->next;
	}
	return (collision);
}

int player_collide(t_asteroid_lst *asteroid_node,t_data *data)
{
	return (is_in_circle(asteroid_node->asteroid->x,
						 asteroid_node->asteroid->y,
						 (double)(asteroid_node->asteroid->size * 2 + ((double)PLAYER_SIZE / 2)),
						 data->player->x,
						 data->player->y));
}

void	collision_detection(t_data *data)
{
	t_asteroid_lst *asteroid_node=data->asteroid_lst;
	int	killed = 0;

	while(asteroid_node)
	{
		killed += bullet_collide(asteroid_node,data);
		killed += player_collide(asteroid_node,data);
		if (killed)
			printf("boom");
		killed = 0;
		asteroid_node = asteroid_node->next;
	}
}