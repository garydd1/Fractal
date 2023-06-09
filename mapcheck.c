/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapcheck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:24:43 by dgarizad          #+#    #+#             */
/*   Updated: 2023/04/16 11:51:58 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/so_long.h"

/**
 * @brief Norminette issues. 
 * This counts the first row columns.
 * @param data 
 * @return int 
 */
static int	ft_first_col(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i] != '\n')
		i++;
	return (i);
}

/**
 * @brief Checks if the number of columns is the same for each row. 
 * doesnt check anything else. if all okey, updates the info of width
 * and height of the map.
 * @param data 
 * @return int 
 */
static void	ft_is_rectang(t_data *data)
{
	int	col_watchdog;
	int	i;
	int	lines;
	int	cols;

	col_watchdog = ft_first_col(data);
	i = 0;
	lines = 1;
	cols = -1;
	while (data->map[i] != '\0')
	{
		cols++;
		if (data->map[i] == '\n')
		{
			if (col_watchdog != cols)
				ft_error(MAP_RECT);
			lines++;
			cols = -1;
		}
		i++;
	}
	if (col_watchdog != ++cols)
		ft_error(MAP_RECT);
	data->map_h = lines;
	data->map_w = col_watchdog;
}

/**
 * @brief reads the fd and stores it in a buffer. 
 * @param data 
 * @param fd 
 * @return int 
 */
static int	ft_read_map(t_data *data, int fd)
{
	data->bytes = read(fd, data->map, BUFFER_SIZE);
	if (data->bytes == -1 || data->bytes == 0)
		ft_error(READ_ERR);
	data->map[data->bytes] = '\0';
	return (0);
}

/**
 * @brief Checks if the input file is readable, rectangular, 
 * has correct number and type of characters,
 * is properly borded and if the map is playable.
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int	ft_map_check(int argc, char **argv, t_data *data)
{
	int		fd;

	if (argc != 2)
		ft_error(INPUT_NBR);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error(INPUT_FILE);
	ft_read_map(data, fd);
	ft_is_rectang(data);
	ft_check_chars(data);
	ft_surround(data);
	close(fd);
	ft_bfs(data);
	return (0);
}
