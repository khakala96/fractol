/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bindings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khakala <khakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 13:36:46 by khakala           #+#    #+#             */
/*   Updated: 2020/02/28 11:37:08 by khakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		key_hook2(int key, t_fractol *data)
{
	if (key == P)
		data->psychedelics = 1;
	else if (key == O)
		data->psychedelics = 0;
	else if (key == R)
	{
		data->color_pattern = 0;
		data->show_text = 1;
		data->help_screen = 0;
		data->color = 265;
		initialize_fractal(data);
	}
	else if (key == C)
		data->julia_mouse = !data->julia_mouse;
	return (0);
}

int		key_hook(int key, t_fractol *data)
{
	if (key == ESC)
		exit(1);
	if (key == H)
	{
		data->show_text = 0;
		data->help_screen = 1;
		calculate_fractals(data);
	}
	if (key == M)
		change_color_pattern(key, data);
	if (key == ARROW_RIGHT)
		data->x1 -= 20 / data->zoom;
	if (key == ARROW_LEFT)
		data->x1 += 20 / data->zoom;
	if (key == ARROW_UP)
		data->y1 += 20 / data->zoom;
	if (key == ARROW_DOWN)
		data->y1 -= 20 / data->zoom;
	if (key == PLUS && data->max_iterations < 200)
		data->max_iterations += 30;
	if (key == MINUS && data->max_iterations > 30)
		data->max_iterations -= 30;
	key_hook2(key, data);
	calculate_fractals(data);
	return (0);
}

void	ft_zoom_in(int x, int y, t_fractol *data)
{
	data->x1 = (x / data->zoom + data->x1) - (x / (data->zoom * 1.3));
	data->y1 = (y / data->zoom + data->y1) - (y / (data->zoom * 1.3));
	data->zoom *= 1.3;
	if (data->psychedelics == 1)
		data->color *= 1.1;
}

void	ft_zoom_out(int x, int y, t_fractol *data)
{
	data->x1 = (x / data->zoom + data->x1) - (x / (data->zoom / 1.3));
	data->y1 = (y / data->zoom + data->y1) - (y / (data->zoom / 1.3));
	data->zoom /= 1.3;
	if (data->psychedelics == 1)
		data->color /= 1.1;
}

int		mouse_hook(int mousecode, int x, int y, t_fractol *data)
{
	if (mousecode == 4 || mousecode == 1)
		ft_zoom_in(x, y, data);
	else if (mousecode == 5 || mousecode == 2)
		ft_zoom_out(x, y, data);
	calculate_fractals(data);
	return (0);
}
