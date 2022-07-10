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
	t_buffer	*dbl_buffer;
} t_data;

#endif
