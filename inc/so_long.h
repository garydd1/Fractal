/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 19:24:07 by dgarizad          #+#    #+#             */
/*   Updated: 2023/04/09 22:01:51 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"


# define WIDTH 1500
# define HEIGHT 1000

typedef struct s_macro_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			steps;
} t_data;

//HOOKS
void		ft_set_hooks(t_data *data);
void		ft_hook(void* param);

#endif