/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khakala <khakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:30:15 by khakala           #+#    #+#             */
/*   Updated: 2020/02/25 11:32:11 by khakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	initialize_fractal(t_fractol *data)
{
	if (data->max_iterations < 0)
		data->max_iterations = 0;
	else if (data->fractal == 0)
		initialize_julia(data);
	else if (data->fractal == 1)
		initialize_mandelbrot(data);
	else if (data->fractal == 2)
		initialize_burningship(data);
	calculate_fractals(data);
}

int		calculate_fractals(t_fractol *data)
{
	if (data->fractal == 0)
		julia_pthread(data);
	if (data->fractal == 1)
		mandelbrot_pthread(data);
	if (data->fractal == 2)
		burningship_pthread(data);
	if (data->show_text == 1)
		display_text(data);
	help_screen(data);
	return (0);
}

void	mlx_window_init(t_fractol *data, t_mlx *minilibx)
{
	data->show_text = 1;
	data->color_pattern = 0;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Fractol");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img_ptr = mlx_get_data_addr(data->img, &minilibx->bits_per_pixel,
	&minilibx->size_line, &minilibx->endian);
}

int		choose_fractal(t_fractol *data, char **av)
{
	if (ft_strcmp(av[1], "julia") == 0)
		data->fractal = 0;
	else if (ft_strcmp(av[1], "mandelbrot") == 0)
		data->fractal = 1;
	else if (ft_strcmp(av[1], "burningship") == 0)
		data->fractal = 2;
	else
	{
		ft_putendl("Error usage ./fractol julia/mandelbrot/burningship");
		return (0);
	}
	return (1);
}

int		main(int ac, char **av)
{
	t_fractol	*data;
	t_mlx		*minilibx;

	data = (t_fractol*)malloc(sizeof(t_fractol));
	minilibx = (t_mlx*)malloc(sizeof(t_mlx));
	if (ac != 2)
	{
		ft_putendl("Error usage ./fractol julia/mandelbrot/burningship");
		exit(-1);
	}
	mlx_window_init(data, minilibx);
	if (choose_fractal(data, av) == 0)
		return (0);
	initialize_fractal(data);
	mlx_hook(data->win, 6, 0, mouse_julia, data);
	mlx_hook(data->win, 17, 0L, ft_close, data);
	mlx_key_hook(data->win, key_hook, data);
	mlx_mouse_hook(data->win, mouse_hook, data);
	mlx_loop(data->mlx);
	return (0);
}
