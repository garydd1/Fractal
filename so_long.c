/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:21:27 by dgarizad          #+#    #+#             */
/*   Updated: 2023/04/16 18:26:42 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/so_long.h"
#include <string.h>

void	lseaks(void)
{
	system("leaks -fullContent so_long");
}

void	ft_error(char *err)
{
	ft_putstr_fd(err, 2);
	exit(-1);
}

int	ft_free_sprites(t_data *data)
{
	int	i;

	i = 0;
	while (i < SPRITES_COUNT)
	{
		free(data->xpm[i]);
		free(data->xpm[i]->texture.pixels);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	atexit(lseaks);
	t_data data;

	if (argc != 2)
		ft_error(INPUT_NBR);
	ft_memset(&data, '\0', sizeof(data));
	ft_map_check(argc, argv, &data);
	ft_load_sprites(&data);
	return (0);
}
