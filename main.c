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

/*******************************************************************************
 * Main takes no args at the moment, config is done in config.h              *
 ******************************************************************************/

int main(void)
{
	t_data *data = NULL;

	data = main_init();
	mlx_loop(data->mlx);
	main_memory_clean(data);
	return (0);
}