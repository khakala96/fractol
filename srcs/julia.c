/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khakala <khakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 13:11:15 by khakala           #+#    #+#             */
/*   Updated: 2020/02/27 14:42:39 by khakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mouse_julia(int x, int y, t_fractol *data)
{
	if (data->julia_mouse == 1)
	{
		if (x < WIDTH / 2 && y > HEIGHT / 2)
			data->c_x -= 10;
		if (x > WIDTH / 2 && y < HEIGHT / 2)
			data->c_x += 10;
		if (x < WIDTH / 2 && y < HEIGHT / 2)
			data->c_y -= 10;
		if (x > WIDTH / 2 && y > HEIGHT / 2)
			data->c_y += 10;
	}
	calculate_fractals(data);
	return (0);
}

void	initialize_julia(t_fractol *data)
{
	data->max_iterations = 50;
	data->zoom = 200;
	data->x1 = -3.0;
	data->y1 = -3.0;
	data->color = 265;
	data->c_x = 53;
	data->c_y = 315;
	data->julia_mouse = 1;
}

void	calculate_julia(t_fractol *data)
{
	data->z_x = data->x / data->zoom + data->x1;
	data->z_y = data->y / data->zoom + data->y1;
	data->iterations = 0;
	while (data->z_x * data->z_x + data->z_y * data->z_y
		< 4 && data->iterations < data->max_iterations)
	{
		data->tmp = data->z_x;
		data->z_x = data->z_x * data->z_x - data->z_y *
			data->z_y - 0.8 + (data->c_x / WIDTH);
		data->z_y = 2 * data->z_y * data->tmp + data->c_y / HEIGHT;
		data->iterations++;
	}
	if (data->iterations == data->max_iterations)
		put_pxl_to_img(data, data->x, data->y, 0x000000);
	else
		put_pxl_to_img(data, data->x, data->y,
		(data->color * data->iterations));
}

void	*julia(void *tab)
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
			calculate_julia(data);
			data->y++;
		}
		data->x++;
	}
	return (tab);
}

void	julia_pthread(t_fractol *data)
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
		pthread_create(&t[i], NULL, julia, &tab[i]);
		i++;
	}
	while (i--)
		pthread_join(t[i], NULL);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
