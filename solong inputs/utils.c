#include <stdio.h>
#include <stdlib.h>
#include "header.h"

unsigned int	ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == 0)
		return ((char *)(s + i));
	else
		return (0);
	return ((char *)s);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	i;

	if (!dst && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		*((char *)(dst + i)) = *((char *)(src + i));
		if ((char *)(src + i) == (void *)0)
			return (dst);
		i++;
	}
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;

	ptr = (char *)malloc(ft_strlen(s1) + 1);
	if (!ptr)
		return (NULL);
	ptr = ft_memcpy(ptr, s1, ft_strlen(s1));
	ptr[ft_strlen(s1)] = '\0';
	return (ptr);
}


char	*ft_substr(char const *s, size_t start, size_t len)
{
	char	*substring;

	if (s == NULL)
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	substring = (char *)malloc(len + 1);
	if (!substring)
		return (NULL);
	substring = ft_memcpy(substring, &s[start], len);
	substring[len] = '\0';
	return (substring);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;

	if (n == 0)
		return ;
	i = 0;
	while (i < n)
	{
		*((char *)(s + i)) = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

static int	ft_count_del(char const *s, char c)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	if (*s && *s != c)
		count++;
	while (s[i])
	{
		if ((s[i] == c && s[i + 1] != c && s[i + 1]))
			count++;
		i++;
	}
	return (count);
}

static char	**ft_abort(char **new_array, unsigned int i)
{
	while (i-- > 0)
		free(new_array[i]);
	free(new_array);
	return (0);
}

static char	**ft_array_gen(char const *s, char c, char **new_array)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			j = 0;
			while (*s && *s != c)
			{
				j++;
				s++;
			}
			new_array[i++] = ft_substr(s - j, 0, j);
			if (!new_array[i - 1])
				return (ft_abort(new_array, i));
		}
		else
			s++;
	}
	return (new_array);
}

char	**ft_split(char const *s, char c)
{
	char			**new_array;

	new_array = (char **)ft_calloc((ft_count_del(s, c) + 1), sizeof (char *));
	if (!new_array)
		return (NULL);
	new_array = ft_array_gen(s, c, new_array);
	return (new_array);
}

// UTILS FOR BREADHTFIRST
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