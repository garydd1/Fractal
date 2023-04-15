/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:21:27 by dgarizad          #+#    #+#             */
/*   Updated: 2023/04/15 12:30:40 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/so_long.h"
#include <string.h>

void lseaks(void)
{
	system("leaks -fullContent so_long");
}

int	main(int argc, char **argv)
{
	atexit(lseaks);
	
	if (argc != 2)
		printf("\nCREATE AN EXIT!\n");
	//ft_map_check(argc, argv);
	argv = NULL;
	 // Init mlx with a canvas size of 256x256 and the ability to resize the window.
	mlx_t* mlx = mlx_init(800, 800, "MLX42", true);
    // Create a 128x128 image.
    //mlx_image_t* img = mlx_new_image(mlx, 32, 32);
	// LEARN TEXTURES 
	mlx_texture_t *texture = mlx_load_png("./png/kyrby.png"); //THIS HAS 2 POINTERS TO BE FREED
	mlx_image_t* img = mlx_texture_to_image(mlx, texture);//THIS HAS TO BE FREED
	//END LEARN TEXTURES
	//SAVE ALL VARIABLES IN A STRUCT THAT TRAVELS THE MULTIVERSE
	t_data data;
	data.mlx  = mlx;
	data.img = img;
	data.steps = 0;
	// ABOVE WE ARE INITIALIZING AL data VALUES;
    mlx_image_to_window(mlx, img, 128-16, 128-16);
	// ft_memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));
	// mlx_put_pixel(img, 16, 16, 0xFF0000FF);
    // Draw the image at coordinate (0, 0).

    // Run the main loop and terminate on quit.  
	ft_set_hooks(&data);
	mlx_loop_hook(mlx, ft_hook, &data);
    mlx_loop(mlx);
	free(texture);
	free(texture->pixels);
	//mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	// system("leaks so_long");
	return (0);
}
