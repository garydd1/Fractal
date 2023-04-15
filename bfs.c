/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:45:08 by dgarizad          #+#    #+#             */
/*   Updated: 2023/04/14 23:40:08 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/so_long.h"
//DELETE OR COMMENT
void	print_visited(t_queue *queue)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (queue->visited[j])
	{
		printf("visited: %s\n", queue->visited[j]);
		j++;
	}
}

/**
 * @brief sets an array to keep track
 * of the "visited" nodes.
 * @param data 
 * @param queue 
 * @return int 
 */
int	ft_set_visited(t_data *data, t_queue *queue)
{
	int	i;
	int	j;

	queue->visited = ft_split(data->map, '\n');//NEED TO BE FREED
	j = 1;
	while (j < data->map_h -1)
	{
		i = 1;
		while (i < data->map_w -1)
		{
			if (queue->visited[j][i] != '1')
			queue->visited[j][i] = 'N';
			i++;
		}
		j++;
	}
	return (0);
}

/**
 * @brief Find the coordinates of specific characters
 * important note: 
 * coordinates in arrays are arr[row][column] first is the
 * y and secon is the x. (take care of that!)
 * @param map_s 
 * @param data 
 * @param c 
 * @return int* 
 */
int	ft_find_coords(char **map_s, t_data *data, char c, int *coord)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->map_h)
	{
		j = 0;
		while (j < data->map_w)
		{
			if (map_s[i][j] == c)
			{
				coord[0] = i;
				coord[1] = j;
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
/**
 * @brief Still bfs.
 * 
 * @param data 
 * @param queue 
 * @return int 
 */
int	ft_flood(t_queue *queue)
{
	t_queue	*aux;

	while (queue->next != NULL)
	{
		aux = ft_mary_poppins(queue);
		(queue->visited)[aux->row][aux->col] = 'Y';
		print_visited(queue);
		if (ft_neighbors(queue, aux->row, aux->col, queue->map_s) == 0)
		{
			free(aux);
			while (queue->next != NULL)
			{
				aux = ft_mary_poppins(queue);
				free(aux);
			}
			print_visited(queue);
			return (0);
		}
		free(aux);
	}
	return (1);
}

/**
 * @brief here is the Bfs logic.
 * 
 * @param data 
 * @param queue 
 * @return int 
 */
int	ft_is_path(t_data *data, t_queue *queue)
{
	int	exit_coord[2];
	int	player_coord[2];
	
	ft_find_coords(queue->map_s, data, 'E', exit_coord);
	queue->target[0] = exit_coord[0];
	queue->target[1] = exit_coord[1];
	ft_find_coords(queue->map_s, data, 'P', player_coord);
	ft_add2queue(queue, player_coord[0], player_coord[1]);
	if (ft_flood(queue) == 1)
		ft_error(MAP_NOPATH);
	return (0);
}

// int	ft_coins_path(t_data *data, t_queue *queue)
// {
// 	int	exit_coord[2];
// 	//int	player_coord[2];
// 	int	i;
// 	int	j;
	
// 	ft_find_coords(queue->map_s, data, 'E', exit_coord);
// 	queue->target[0] = exit_coord[0];
// 	queue->target[1] = exit_coord[1];
// 	i = 0;
// 	while (i < data->map_h - 1)
// 	{
// 		j = 1;
// 		while (j < data->map_w -1)
// 		{
// 			if (queue->map_s[i][j] == 'C')
// 				printf("\ncoin at: %d,%d\n", i,j);	
// 			j++;
// 		}
// 		i++;
// 	}
// 	// ft_find_coords(queue->map_s, data, 'P', player_coord);
// 	// ft_add2queue(queue, player_coord[0], player_coord[1]);
// 	// if (ft_flood(queue) == 1)
// 	// 	ft_error(MAP_NOPATH);
// 	return (0);
// }

/**
 * @brief Applies a "Flood Fill" logic to determine if
 * there is a valid path between Player-Exit. And Player-All Coins.
 * @param data 
 * @return int 
 */
int	ft_bfs(t_data *data)
{
	t_queue	queue;
	//int		coord[2];

	ft_bzero(&queue, sizeof(t_queue));
	queue.map_s = ft_split(data->map, '\n'); //NEED TO BE FREED
	ft_set_visited(data, &queue);
	print_visited(&queue);
	// ft_coins_path(data, &queue);
	ft_is_path(data, &queue);
	ft_free_splits(queue.map_s);
	ft_free_splits(queue.visited);
	return (0);
}
