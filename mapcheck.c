/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapcheck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:24:43 by dgarizad          #+#    #+#             */
/*   Updated: 2023/04/14 23:05:49 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/so_long.h"

// NOTICE THAT ERRORS SHOULD BE PRINTED IN fd 2. stderr. 
void	ft_error(char *err)
{
	printf("%s", err);
	exit(0);
}

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

int	ft_map_check(int argc, char **argv)
{
	int		fd;
	t_data	data;
	
	if (argc != 2)
		ft_error(INPUT_NBR);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error(INPUT_FILE);
	ft_memset(&data, 0, sizeof(t_data));
	ft_read_map(&data, fd);
	ft_is_rectang(&data);
	ft_check_chars(&data);
	ft_surround(&data);
	printf("\nok: '%d'\n%s\n\n", data.bytes, data.map);
	close(fd);
	ft_bfs(&data);
	return (0);
}
