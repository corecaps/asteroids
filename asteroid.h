/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asteroid.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 16:44:26 by jgarcia           #+#    #+#             */
/*   Updated: 2022/07/10 16:44:30 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTEROIDS_ASTEROID_H
# define ASTEROIDS_ASTEROID_H
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <time.h>
# include <string.h>
# define SIZE_X 800
# define SIZE_Y 600
# define FRAME_MAX 10

typedef struct s_buffer
{
	void	*img;
	char 	*addr;
	int 	bit_per_pixel;
	int 	line_length;
	int 	endian;
} t_buffer;
typedef struct	s_data
{
	int			size_x;
	int			size_y;
	void		*mlx;
	void		*mlx_win;
	t_buffer	*img_buffer;
} t_data;
void	win_close(int keycode, t_data *data);
int		my_mlx_pixel_put(t_buffer *data, int x, int y, int color);
void 	draw_line(int x_from,int y_from,int x_to,int y_to,t_data *data, int color);
void	clear_buffer(t_data *data);
int 	render(t_data *data);
// test functions :
void 	test_line(t_data *data);
void	test_line2(t_data *data);
#endif