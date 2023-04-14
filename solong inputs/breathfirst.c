
#include "header.h"

void   print_visited(t_queue *queue)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (queue->visited[j])
    {
        printf("visited: %s\n",queue->visited[j]);
        j++;
    }
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
int ft_find_coords(char **map_s, t_data *data, char c, int *coord)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < data->map_h)
    {
        j = 0;
        while (j < data->map_w)
        {
            if (map_s[i][j] == c)
            {
                coord[0]= i;
                coord[1]= j;
                return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

int ft_add2queue(t_queue *queue, int row, int col)
{
    t_queue *new;   
    int     coords[2];

    coords[0] = row;
    coords[1] = col;
    printf("\nWTFreceived coord: %d,%d\n", row, col);    
    print_visited(queue);
    (queue->visited)[row][col] = 'Y';
    new = ft_newqueue(coords, queue);
    ft_add_back(queue, new);
    printf("\nnewww first coord: %d,%d\n", queue->next->row, queue->next->col);
    return (0);
}
/**
 * @brief sets an array to keep track
 * of the "visited" nodes.
 * @param data 
 * @param queue 
 * @return int 
 */
int ft_set_visited(t_data *data, t_queue *queue)
{
    int i;
    int j;
    
    queue->visited = ft_split(data->map, '\n');//NEED TO BE FREED
    j = 1;
    while (j < data->map_h -1)
    {
        i = 1;
        while (i < data->map_w -1)
        {
            queue->visited[j][i] = 'N';
            i++;
        }
        j++;
    }
    return (0);
}

t_queue    *ft_pop_queue(t_queue *queue)
{
    t_queue *aux;

    aux = queue->next;
    queue->next = queue->next->next;
    aux->next = NULL;
    return (aux);
}

/**
 * @brief Returns 0 if finds the target.
 * Analize the neighbors and add them to queue if
 * needed.
 * @param queue 
 * @param row 
 * @param col 
 * @param map_s 
 * @return int 
 */
int ft_neighbors(t_queue *queue, int row, int col, char **map_s)
{
    int i;
    int j;
    
    i = 1;
    j = 0;
    while(j < 2)
    {
        printf("\nneightbor col:%c\n",map_s[row][col+i]);
        printf("\nneightbor row:%c\n",map_s[row+i][col]);
        if(map_s[row][col+i]  == map_s[queue->target[0]][queue->target[1]]||\
        map_s[row+i][col] == map_s[queue->target[0]][queue->target[1]])
            return (0);
        if(queue->visited[row][col + i] == 'N' && map_s[row][col + i] != '1')
        {
            queue->visited[row][col + i] = 'Y';
            ft_add2queue(queue, row, col + i);
        }
        if(queue->visited[row + i][col] == 'N' && map_s[row + i][col] != '1')
        {
            queue->visited[row + i][col] = 'Y';
            ft_add2queue(queue, row + i, col);
        }
        j++;
        i *= -1;
    }
    return (1);
}


/**
 * @brief This function intends to apply the BFS principles to 
 * determine if ther is a path between Coins an player.
 * @param data 
 * @return int 
 */
int ft_breath_first(t_data *data)
{
    char    **map_s;
    t_queue queue;
    int     coord[2];
    ft_bzero(&queue, sizeof(t_queue));
    map_s = ft_split(data->map, '\n'); //NEED TO BE FREED
    ft_set_visited(data, &queue);
    //DEFINING TARGET AND STARTING POINT FOR FINDPATH
    ft_find_coords(map_s, data, 'E', coord);
    printf("\nExit is at:\n%d,%d",coord[0],coord[1]);
    queue.target[0] = coord[0];
    queue.target[1] = coord[1];
    ft_find_coords(map_s, data, 'C', coord);
    printf("\nFirst Coin is at:\n%d,%d",coord[0],coord[1]);
    print_visited(&queue);
    ft_add2queue(&queue, coord[0], coord[1]);
    //END DEFINING
    print_visited(&queue);
    //FINDPATH TAKE 
    while (queue.next != NULL)
    {
        t_queue *aux;
        
        aux = ft_pop_queue(&queue); //NEED TO BE FREED!
        printf("\npopped:%d,%d\n",aux->row,aux->col);
        (queue.visited)[aux->row][aux->col] = 'Y';
        //printf("\nvisited:\n%s",(queue.visited)[aux->row]);
        print_visited(&queue);
        if (ft_neighbors(&queue, aux->row,aux->col, map_s) == 0) 
        {
            printf("\nEUREKA!!!!!!!!!!!!!!\n");
            break;
        }
    }
    printf("\nend popping\n");

    return (0);
}