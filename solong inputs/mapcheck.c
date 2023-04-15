/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapcheck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:08:33 by dgarizad          #+#    #+#             */
/*   Updated: 2023/04/14 15:18:51 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
// NOTICE THAT ERRORS SHOULD BE PRINTED IN fd 2. stderr. 
void	ft_error(char *err)
{
	printf("%s", err);
	exit(-1);
}

int	ft_read_map(t_data *data, int fd)
{
	data->bytes = read(fd, data->map, BUFFER_SIZE);
	if (data->bytes == -1 || data->bytes == 0)
		ft_error(READ_ERR);
	data->map[data->bytes] = '\0';

	return (0);
}
/**
 * @brief Norminette issues. 
 * This counts the first row columns.
 * @param data 
 * @return int 
 */
static int 	ft_first_col(t_data *data)
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
void	ft_is_rectang(t_data *data)
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
 * @brief Checks if there is at least 1 coin, exactly 1 player 
 * and 1 exit. Stores the number of coins in data.
 * @param data 
 * @return int 
 */
int	ft_check_chars(t_data *data)
{
	int		i;
	int		flags[3] = {0, 0, 0};
	char	wd;

	i = 0;
	while (data->map[i] != '\0')
	{
		wd = data->map[i];
		if (wd == 'C')
			flags[0]++;
		if (wd == 'P')
			flags[1]++;
		if (wd == 'E')
			flags[2]++;
		if (wd != '0' && wd != '1' && wd != 'C'\
		&& wd != 'E' && wd != 'P' && wd != '\n')
			ft_error(MAP_CHAR);
		i++;
	}
	if (flags[0] < 1 || flags[1] != 1 || flags[2] != 1)
		ft_error(MAP_CHAR2);
	data->coins = flags[0];
	return (0);
}

int	ft_char_index(t_data *map)
{
	return (0);
}

/**
 * @brief Checks the outter borders and returns 1 if something is 
 * not '1'. auxiliary function for surround ft.
 * @param map 
 * @param c 
 * @param flag 
 * @param data 
 * @return int 
 */
static int	ft_look(char **map, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map_w)
	{
		if (map[0][i] != '1' || map[data->map_h - 1][i] != '1')
			return (1);
		i++;
	}
	i = 0;
	while (i < data->map_h)
	{
		if (map[i][0] != '1' || map[i][data->map_w - 1] != '1')
			return (1);
		i++;
	}
	return (0);
}
/**
 * @brief Checks if the map is properly borded.
 * This functions splits the map in a widthxheight array.
 * and free it after that.
 * @param data 
 * @return int 
 */
int	ft_surround(t_data *data)
{
	char	**map_s;

	map_s = ft_split(data->map, '\n');
	if (ft_look(map_s, data) == 1)
	{
		free(map_s);
		ft_error(MAP_BORDER);
	}
	free(map_s);
	return (0);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_data	data;

	if (argc != 2)
		ft_error(INPUT_NBR);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error(INPUT_FILE);
	ft_read_map(&data, fd);
	ft_is_rectang(&data);
	ft_check_chars(&data);
	ft_surround(&data);
	printf("\nok: '%d'\n%s\n\n", data.bytes, data.map);
	_close(fd);
	ft_breath_first(&data);
	return (0);
}
