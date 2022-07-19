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
# include "config.h"
# define RADIAN 0.0174532925
typedef struct s_point
{
	double x;
	double y;
} t_point;
typedef struct s_bullet
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	int 	ttl;
} t_bullet;
typedef struct s_bullet_lst
{
	t_bullet 	*bullet;
	struct s_bullet_lst *next;
} t_bullet_lst;
typedef struct s_particle
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	int 	ttl;
} t_particle;
typedef struct s_particle_lst
{
	t_particle	*particle;
	struct s_particle_lst *next;
} t_particle_lst;
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
	double	x;
	double 	y;
	int 	size;
	t_point	points[10];
	int		offset[10];
	double	dx;
	double 	dy;
} t_asteroid;
typedef struct s_asteroid_lst
{
	struct s_asteroid_lst	*next;
	t_asteroid 				*asteroid;
} t_asteroid_lst;
typedef struct	s_player
{
	double 	x;
	double 	y;
	double 	dx;
	double	dy;
	double	angle;
	int		alive;
	int		score;
} t_player;

typedef struct	s_data
{
	int				size_x;
	int				size_y;
	double 			elapsed_time;
	struct timespec last_frame;
	void			*mlx;
	void			*mlx_win;
	t_buffer		*img_buffer;
	t_asteroid_lst	*asteroid_lst;
	t_player 		*player;
	t_particle_lst	*particle_lst;
	t_bullet_lst	*bullet_lst;
	int 			level;
} t_data;
void 			push_asteroid(t_data *data, int size, double dx, double dy,double x, double y);
int 			key_pressed(int keycode, t_data *data);
int				my_mlx_pixel_put(t_buffer *data, int x, int y, int color);
void 			warp_coord(int *x, int *y);
void			warp_coord_double(double *x, double *y);
void 			draw_line(int x_from,int y_from,int x_to,int y_to,t_data *data, int color);
void			clear_buffer(t_data *data);
void			draw_player(t_data *data);
int 			render(t_data *data);
t_data			*main_init(void);
void			draw_lst_asteroid(t_data *data);
void			draw_asteroid(t_data *data, t_asteroid *asteroid, double angle_offset);
void			main_memory_clean(t_data *data);
void			asteroid_translate(t_asteroid *asteroid, t_data *data);
void			asteroid_move(t_data *data);
void			player_move(t_data *data);
void			get_elapsed_time(t_data *data);
double			get_rnd_delta();
void			push_bullet(t_data *data, double x, double y, double dx, double dy);
void			clean_bullet_lst(t_data *data);
void			draw_bullet_lst(t_data *data);
void			collision_detection(t_data *data);
void			bullet_move(t_data *data);
t_particle_lst	*particle_last(t_particle_lst *head);
void			clean_particle_lst(t_data *data);
void			push_particle(t_data *data, double x, double y, double dx, double dy);
void			particle_move(t_data *data);
void			draw_particle_lst(t_data *data);
void 			kill_asteroid(t_data *data,t_asteroid_lst *asteroid_node);
// test functions :
void 	test_line(t_data *data);
void	test_line2(t_data *data);
#endif