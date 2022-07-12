//
// Created by corecaps on 12/07/22.
//

#include "asteroid.h"

/*******************************************************************************
 * Cleanly free heap allocated space for the data structures                   *
 ******************************************************************************/

void main_memory_clean(t_data *data)
{
	// TODO Clean player structure
	// TODO Clean asteroid_lst linked list
	mlx_destroy_image(data->mlx,data->img_buffer->img);
	free(data->img_buffer);
	free(data->mlx);
	free(data);
}