/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khakala <khakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:06:38 by khakala           #+#    #+#             */
/*   Updated: 2020/02/28 11:36:12 by khakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	change_color_pattern(int key, t_fractol *data)
{
	if (key == M && data->color_pattern < 7)
	{
		data->color_pattern++;
		if (data->color_pattern == 6)
			data->color_pattern = 0;
		if (data->color_pattern == 0)
			data->color = 265;
		if (data->color_pattern == 1)
			data->color = 1677216;
		if (data->color_pattern == 2)
			data->color = 13158600;
		if (data->color_pattern == 3)
			data->color = 655360;
		if (data->color_pattern == 4)
			data->color = 7680;
		if (data->color_pattern == 5)
			data->color = 13107400;
	}
}

void	display_text(t_fractol *data)
{
	char *text;
	char *number;

	number = ft_itoa(data->max_iterations);
	text = ft_strjoin("Current iterations : ", number);
	mlx_string_put(data->mlx, data->win, 20, 20, 0xFFFFFF, text);
	ft_strdel(&text);
	ft_strdel(&number);
	mlx_string_put(data->mlx, data->win, 400, 20, 0xFFFFFF,
	"Press 'H' for help screen");
	if (data->psychedelics == 1)
		mlx_string_put(data->mlx, data->win, 1100, 20, 6618980,
		"Psychedelic effect on");
}

void	put_pxl_to_img(t_fractol *data, int x, int y, int color)
{
	if (data->x < WIDTH && data->y < HEIGHT)
	{
		color = mlx_get_color_value(data->mlx, color);
		ft_memcpy(data->img_ptr + 4 * WIDTH * y + x * 4,
			&color, sizeof(int));
	}
}

void	help_screen(t_fractol *data)
{
	if (data->help_screen == 1)
	{
		data->color = 0;
		mlx_string_put(data->mlx, data->win, 900, 40,
		16724530, "PRESS 'R' TO RESET AND TO GO BACK TO THE FRACTAL");
		mlx_string_put(data->mlx, data->win, 100, 40,
		6618980, "--------------------- MOVEMENT ---------------------");
		mlx_string_put(data->mlx, data->win, 100, 70,
		0xFFFFFF, "USE ARROW KEYS TO MOVE THE IMAGE AROUND");
		mlx_string_put(data->mlx, data->win, 100, 100, 0xFFFFFF,
		"USE MOUSE SCROLL TO ZOOM IN AND OUT OR ALTERNATIVELY MOUSE 1 OR 2");
		mlx_string_put(data->mlx, data->win, 800, 100, 16776960,
		"(PLACE CURSOR WHERE YOU WANT TO ZOOM)");
		mlx_string_put(data->mlx, data->win, 100, 150,
		6618980, "------------------- FRACTOL APPEARANCE -------------------");
		mlx_string_put(data->mlx, data->win, 100, 200, 0xFFFFFF,
		"USE '+' OR '-' (NUMPAD) TO INCREASE/DECREASE AMOUNT OF ITERATIONS");
		mlx_string_put(data->mlx, data->win, 100, 250, 0xFFFFFF,
		"PRESS 'P' TO ACTIVTE PSYCHEDELIC MODE AND 'O' TO DEACTIVATE IT");
		mlx_string_put(data->mlx, data->win, 100, 300, 0xFFFFFF,
		"PRESS 'M' TO CYCLE THROUGH THE DIFFERENT COLOR MAPS");
		mlx_string_put(data->mlx, data->win, 100, 350, 16776960,
		"IN JULIA FRACTAL PRESS 'C' TO DISABLE/ENABLE CHANGE BY MOVING MOUSE");
	}
}

int		ft_close(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}
