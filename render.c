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
		//TODO clean_bullet_lst
		//TODO clean_particle_lst
		frame ++;
	}
	else if (frame == 1)
	{
		get_elapsed_time(data);
		asteroid_move(data);
		player_move(data);
		// TODO player_move(data);
		// TODO bullet_move(data);
		// TODO particle_move(data);
		// TODO collision(data);
		frame ++;
	}
	else if (frame == 2)
	{
		draw_lst_asteroid(data);
		draw_player(data);
		// TODO draw_player
		// TODO draw_bullets
		// TODO draw_particle
		frame ++;
	}
	else if (frame >= FRAME_MAX)
	{
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_buffer->img, 0 ,0);
		mlx_string_put(data->mlx,data->mlx_win,SIZE_X / 4 + 50,20,0xFFFFFF,"42-ASTEROIDs Alpha-Press ESC to exit-Score : 0");
		frame = 0;
	}
	else
	{
		frame ++;
	}
	return (0);
}

/*******************************************************************************
 * get elapsed time since last calculation frame in seconds                   *
 ******************************************************************************/
void get_elapsed_time(t_data *data)
{
	struct timespec current_frame;

	clock_gettime(CLOCK_MONOTONIC, &current_frame);
	data->elapsed_time = round((double)(current_frame.tv_nsec -
										data->last_frame.tv_nsec) / 1.0e6) / 1000;
	if (data->elapsed_time < 0)
		data->elapsed_time = 0.001;
	data->last_frame = current_frame;
}