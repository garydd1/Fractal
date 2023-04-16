/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:10:59 by dgarizad          #+#    #+#             */
/*   Updated: 2023/04/16 18:19:47 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/so_long.h"

int	ft_movement_calc(t_data *data, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS && \
	data->map_s[data->playery][data->playerx + 1] != '1')
	{
		data->f = 1;
		data->playerx += 1;
	}
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS && \
	data->map_s[data->playery][data->playerx - 1] != '1')
	{
		data->f = 1;
		data->playerx -= 1;
	}
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS && \
	data->map_s[data->playery - 1][data->playerx] != '1')
	{
		data->f = 1;
		data->playery -= 1;
	}
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS && \
	data->map_s[data->playery + 1][data->playerx] != '1')
	{
		data->f = 1;
		data->playery += 1;
	}
	return (0);
}
