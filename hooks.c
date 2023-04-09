/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:28:22 by dgarizad          #+#    #+#             */
/*   Updated: 2023/04/09 22:18:49 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/so_long.h"

void ft_hook(void* param)
{
	t_data *data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		data->img->instances[0].y -= 5;
		ft_putstr_fd("upmoto", 1);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		data->img->instances[0].y += 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		data->img->instances[0].x -= 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		data->img->instances[0].x += 5;
	// printf("\nWIDTH:  | HEIGHT: \n");
}

static void	ft_steps(t_data *data)
{
	(data->steps)++;
	ft_putstr_fd("Steps: ", 1);
	ft_putendl_fd(ft_itoa((data->steps)),1);
}
void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data *data = param;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		data->img->instances[0].x += 16;
		ft_steps(data);
	}
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		data->img->instances[0].x -= 16;
		ft_steps(data);
	}
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	{
		data->img->instances[0].y -= 16;
		ft_steps(data);
	}	
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
	{
		data->img->instances[0].y += 16;
		ft_steps(data);
	}
	
}

void	my_scrollhook(double xdelta, double ydelta, void *param)
{
	param = NULL;
	xdelta = 0;
	if (ydelta > 0)
		ft_putstr_fd("Up!", 1);
	else if (ydelta < 0)
		ft_putstr_fd("AND Down!", 1);
}

void	ft_set_hooks(t_data *data)
{
	mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_scroll_hook(data->mlx, &my_scrollhook, NULL);
}
