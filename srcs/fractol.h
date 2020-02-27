/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khakala <khakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:28:52 by khakala           #+#    #+#             */
/*   Updated: 2020/02/26 12:58:28 by khakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define WIDTH 1400
# define HEIGHT 1000
# define THREADS 200
# define THREAD_WIDTH 5
# define ESC 53
# define ARROW_UP 126
# define ARROW_DOWN 125
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define O 31
# define M 46
# define N 45
# define PLUS 69
# define MINUS 78
# define P 35
# define SLASH 44
# define R 15
# define C 8
# define I 34
# define H 4

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>

typedef struct		s_fractol
{
	int				x;
	int				y;
	int				y_max;
	double			x1;
	double			y1;
	int				z;
	int				z1;
	int				fractal;
	int				iterations;
	int				max_iterations;
	int				color;
	double			tmp;
	double			zoom;
	double			c_x;
	double			c_y;
	double			z_x;
	double			z_y;
	int				julia_mouse;
	int				show_text;
	int				psychedelics;
	int				change_color;
	int				help_screen;
	int				color_pattern;
	void			*mlx;
	void			*win;
	void			*img;
	void			*img_ptr;
}					t_fractol;

typedef struct		s_mlx
{
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_mlx;

int					calculate_fractals(t_fractol *data);
int					ft_close(void);
int					choose_fractal(t_fractol *data, char **av);
void				initialize_fractal(t_fractol *data);

int					mouse_julia(int x, int y, t_fractol *data);
int					key_hook(int key, t_fractol *data);
int					mouse_hook(int mousecode, int x, int y, t_fractol *data);

void				initialize_julia(t_fractol *data);
void				calculate_julia(t_fractol *data);
void				*julia(void *tab);
void				julia_pthread(t_fractol *data);

void				initialize_mandelbrot(t_fractol *data);
void				calculate_mandelbrot(t_fractol *data);
void				*mandelbrot(void *tab);
void				mandelbrot_pthread(t_fractol *data);
void				burningship_pthread(t_fractol *data);
void				initialize_burningship(t_fractol *data);

void				put_pxl_to_img(t_fractol *data, int x, int y, int color);
void				display_text(t_fractol *data);
void				help_screen(t_fractol *data);
void				change_color_pattern(int key, t_fractol *data);

#endif
