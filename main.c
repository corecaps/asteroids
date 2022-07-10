/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 16:44:10 by jgarcia           #+#    #+#             */
/*   Updated: 2022/07/10 16:44:14 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asteroid.h"

int main(void)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
	{
		printf("ALLOCATION ERROR");
		return (-1);
	}
	data->mlx = mlx_init();
	return (0);
}
