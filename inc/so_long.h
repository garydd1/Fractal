/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 19:24:07 by dgarizad          #+#    #+#             */
/*   Updated: 2023/04/14 19:36:32 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
#include <fcntl.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"

#define INPUT_NBR "Error\nOnly 1 argument needed"
#define INPUT_FILE "Error\nwrong open file"
#define READ_ERR "Error\nMap could not be read"
#define MAP_RECT "Error\nMAP IS NOT RECTANGULAR"
#define MAP_CHAR "Error\nMAP HAS DR.STRANGE CHARS"
#define MAP_CHAR2 "Error\nMAP HAS WRONG PRECONFIG"
#define MAP_BORDER "Error\nBAD BORDERS"
#define MAP_NOPATH "Error\nPATH ISSUES, FIX MAP!"
#define BUFFER_SIZE 700
# define WIDTH 1500
# define HEIGHT 1000

/**
 * @brief bytes is the amount of chars in the input, including borders.
 * map[] is the file read including \\n char. Its only 1 line.
 * 
 */
typedef struct s_macro_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			steps;
	int			bytes;
	int			map_w;
	int			map_h; 
	int			coins;
	char		map[BUFFER_SIZE];
} t_data;

/**
 * @brief Stores row-col in a list for checking later.
 * Visited is a copy of the map but indicating which
 * nodes have been visited
 */
typedef struct s_queue
{
    int row;
    int col;
    char **visited;
	char **map_s;
    int target[2];
    struct s_queue *next;
    
}   t_queue;

//DELETE OR COMMENT
void	print_visited(t_queue *queue);

//HOOKS
void		ft_set_hooks(t_data *data);
void		ft_hook(void* param);

//MAP CHECKS1
int			ft_map_check(int argc, char **argv);
void		ft_error(char *err);

//MAP CHECKS2
int			ft_check_chars(t_data *data);
int			ft_surround(t_data *data);
t_queue		*ft_mary_poppins(t_queue *queue);
int	ft_neighbors(t_queue *queue, int row, int col, char **map_s);

//BREADTH FIRST SEARCH
int			ft_bfs(t_data *data);
//BFS 2
int			ft_add2queue(t_queue *queue, int row, int col);
void		ft_free_splits(char **splited);
#endif