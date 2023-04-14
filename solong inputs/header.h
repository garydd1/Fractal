#define INPUT_NBR "Error\nOnly 1 argument needed"
#define INPUT_FILE "Error\nwrong open file"
#define READ_ERR "Error\nMap could not be read"
#define MAP_RECT "Error\nMAP IS NOT RECTANGULAR"
#define MAP_CHAR "Error\nMAP HAS DR.STRANGE CHARS"
#define MAP_CHAR2 "Error\nMAP HAS WRONG PRECONFIG"
#define MAP_BORDER "Error\nMAP_BORDER"
#define BUFFER_SIZE 700

#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <stdlib.h>


typedef struct s_queue
{
    int row;
    int col;
    char **visited;
    int target[2];
    struct s_queue *next;
    
}   t_queue;

/**
 * @brief 
 * bytes: number of chars in the map.
 * coins: sum of coins.
 */
typedef struct s_macro_data
{
    int     bytes;
    int     map_w;
    int     map_h; 
    int     coins;
    char    map[BUFFER_SIZE];


} t_data;

void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
char	**ft_split(char const *s, char c);      
char	*ft_substr(char const *s, size_t start, size_t len);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strchr(const char *s, int c);
unsigned int	ft_strlen(const char *s);
int     ft_breath_first(t_data *data);
t_queue	*ft_newqueue(void *content, t_queue *queue);
t_queue	*ft_getlast(t_queue *lst);
void	ft_add_back(t_queue *lst, t_queue *newn);
