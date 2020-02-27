/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khakala <khakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 13:12:47 by khakala           #+#    #+#             */
/*   Updated: 2020/02/26 12:54:48 by khakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	initialize_mandelbrot(t_fractol *data)
{
	data->max_iterations = 50;
	data->x1 = -2.4;
	data->y1 = -1.25;
	data->zoom = 400;
	data->color = 265;
}

void	calculate_mandelbrot(t_fractol *data)
{
	data->c_x = data->x / data->zoom + data->x1;
	data->c_y = data->y / data->zoom + data->y1;
	data->z_x = 0;
	data->z_y = 0;
	data->iterations = 0;
	while (data->z_x * data->z_x + data->z_y * data->z_y
		< 4 && data->iterations < data->max_iterations)
	{
		data->tmp = data->z_x;
		data->z_x = data->z_x * data->z_x - data->z_y *
			data->z_y + data->c_x;
		data->z_y = 2 * data->z_y * data->tmp + data->c_y;
		data->iterations++;
	}
	if (data->iterations == data->max_iterations)
		put_pxl_to_img(data, data->x, data->y, 0x000000);
	else
		put_pxl_to_img(data, data->x, data->y,
		(data->color * data->iterations));
}

void	*mandelbrot(void *tab)
{
	t_fractol	*data;
	int			tmp;

	data = (t_fractol *)tab;
	data->x = 0;
	tmp = data->y;
	while (data->x < WIDTH)
	{
		data->y = tmp;
		while (data->y < data->y_max)
		{
			calculate_mandelbrot(data);
			data->y++;
		}
		data->x++;
	}
	return (tab);
}

void	mandelbrot_pthread(t_fractol *data)
{
	t_fractol	tab[THREADS];
	pthread_t	t[THREADS];
	int			i;

	i = 0;
	while (i < THREADS)
	{
		ft_memcpy((void*)&tab[i], (void*)data, sizeof(t_fractol));
		tab[i].y = THREAD_WIDTH * i;
		tab[i].y_max = THREAD_WIDTH * (i + 1);
		pthread_create(&t[i], NULL, mandelbrot, &tab[i]);
		i++;
	}
	while (i--)
		pthread_join(t[i], NULL);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
