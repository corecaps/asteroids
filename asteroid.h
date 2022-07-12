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
# include <math.h>
# define SIZE_X 800
# define SIZE_Y 600
# define FRAME_MAX 10
# define RADIAN 0.0174532925

typedef struct s_buffer
{
	void	*img;
	char 	*address;
	int 	bit_per_pixel;
	int 	line_length;
	int 	endian;
} t_buffer;
typedef struct s_asteroid
{
	int		x;
	int 	y;
	int 	size;
	int 	points[20];
	float	velocity;
	float	angle;
} t_asteroid;
typedef struct s_asteroid_lst
{
	struct s_asteroid_lst	*next;
	t_asteroid 				*asteroid;
} t_asteroid_lst;
typedef struct	s_player
{
	int 	x;
	int 	y;
	float	angle;
	float	accel;
	float	velocity;
	int 	point[6];
} t_player;
typedef struct	s_data
{
	int				size_x;
	int				size_y;
	int 			time_stamp;
	void			*mlx;
	void			*mlx_win;
	t_buffer		*img_buffer;
	t_asteroid_lst	*asteroid_lst;
	t_player 		*player;
} t_data;
void	win_close(int keycode, t_data *data);
int		my_mlx_pixel_put(t_buffer *data, int x, int y, int color);
void 	draw_line(int x_from,int y_from,int x_to,int y_to,t_data *data, int color);
void	clear_buffer(t_data *data);
int 	render(t_data *data);
t_data *main_init(void);
void	pop_asteroid(t_data *data, int size, float speed);
void	draw_asteroid(t_data *data);
// test functions :
void 	test_line(t_data *data);
void	test_line2(t_data *data);
#endif