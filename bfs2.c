/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:04:03 by dgarizad          #+#    #+#             */
/*   Updated: 2023/04/14 20:39:57 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/so_long.h"

// UTILS FOR BREADHTFIRST
void	ft_free_splits(char **splited)
{
	int i;
	
	i = 0;
	while (splited[i] != NULL)
		free(splited[i++]);
	free(splited[i]);
	free(splited);
}
t_queue	*ft_getlast(t_queue *lst)
{
	while (lst)
	{
		if (!(lst -> next))
			return (lst);
		lst = lst ->next;
	}
	return (NULL);
}

void	ft_add_back(t_queue *lst, t_queue *newn)
{
	t_queue	*ptr;

	ptr = ft_getlast(lst);
	if (!ptr)
		lst = newn;
	else
		ptr -> next = newn;
}

t_queue	*ft_newqueue(void *content, t_queue *queue)
{
	t_queue	*new_node;

	printf("\nnewqreceived coord: %d,%d\n", ((int *)content)[0], ((int *)content)[1]);
	new_node = malloc(sizeof(t_queue));
	if (!new_node)
		return (NULL);
	new_node->row = ((int *)content)[0];
	new_node->col = ((int *)content)[1];
	new_node -> next = NULL;
	new_node->visited = queue->visited;
	new_node->target[0] = queue->target[0];
	new_node->target[1] = queue->target[1];
	printf("\nnew node coorde: %d,%d\n", new_node->row, new_node->col);
	return (new_node);
}

int	ft_add2queue(t_queue *queue, int row, int col)
{
	t_queue	*new;
	int		coords[2];

	coords[0] = row;
	coords[1] = col;
	printf("\nWTFreceived coord: %d,%d\n", row, col);
	print_visited(queue);
	(queue->visited)[row][col] = 'Q';
	new = ft_newqueue(coords, queue);
	ft_add_back(queue, new);
	printf("\nnewww first coord: %d,%d\n", queue->next->row, queue->next->col);
	return (0);
}
