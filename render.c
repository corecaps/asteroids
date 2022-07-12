/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:48:09 by jgarcia           #+#    #+#             */
/*   Updated: 2022/07/11 17:48:15 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asteroid.h"

/*******************************************************************************
 * Render (data) is hooked to the refresh loop                                 *
 ******************************************************************************/

int render(t_data *data)
{
	static int frame = 0;
	if (frame == 0)
	{
		clear_buffer(data);
		frame ++;
	}
	else if (frame == 1)
	{
		// TODO game logic
		frame ++;
	}
	else if (frame == 2)
	{
		draw_lst_asteroid(data);
		// TODO graphic calc
//		test_line(data);
//		test_line2(data);
		frame ++;
	}
	else if (frame >= FRAME_MAX)
	{
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_buffer->img, 0 ,0);
		frame = 0;
	}
	else
	{
		frame ++;
	}
	return (0);
}