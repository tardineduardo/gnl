#include "get_next_line_bonus.h"


/**********************************************************************************/

// to do: understand why the remainder is not being saved in remainder for the next line read


/**********************************************************************************/





static char *read_loop_heap(int fd, char *nextline)
{
	char		*buffer;
	char		*temp_read_loop;
	int			size_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	while(!ft_strchr(nextline, '\n'))
	{
		size_read = read(fd, buffer, BUFFER_SIZE);
		if (size_read == -1)
		{
			free(buffer);
			buffer = NULL;
			return (NULL);
		}
		buffer[size_read] = 0;
		temp_read_loop = nextline;
		nextline = ft_strjoin(nextline, buffer);
		free(temp_read_loop);
		temp_read_loop = NULL;
		if (size_read < BUFFER_SIZE)
			break;
	}
	free(buffer);
	buffer = NULL;
	return(nextline);
}

static void	ft_extract_remain(char *nextline, char *remainder)
{
	int		a;
	int		len;

	len = ft_strlen(nextline);
	if (remainder == NULL)
		remainder = malloc(BUFFER_SIZE);
	a = 0;
	while(nextline[a] != '\n' && nextline[a] != 0)
		a++;
	ft_strlcpy(remainder, &nextline[a + 1], BUFFER_SIZE);
	nextline[a + 1] = 0;
	remainder[len - a] = 0;
}

char	*get_next_line(int fd)
{
	char		*nextline;
	static char	**remainder;
	
	if (read(fd, 0, 0) == -1)
		return (NULL);
	if (remainder == NULL)
		remainder = malloc(1024 * sizeof(char *));

	nextline = ft_strdup(remainder[fd]);
	remainder[fd] = 0;
	if (!nextline)
		return (NULL);
	nextline = read_loop_heap(fd, nextline);	
	if (!nextline || nextline[0] == 0)
	{
		free(nextline);
		nextline = NULL;
		return (NULL);
	}
	if (ft_strchr(nextline, '\n'))
		ft_extract_remain(nextline, remainder[fd]);
	return (nextline);
}


int main(void)
{
    int file = open("test1.txt", O_RDONLY); // Open a file for reading
    int a = 0; // Counter for lines
    int b = 1; // Line number for printing
    char *newline; // Pointer to store the line read
	char *tmp;
	int	max_files_opened;


	newline = malloc (1*1);
	tmp = newline;

	max_files_opened = _POSIX_OPEN_MAX;
	printf("%d\n", max_files_opened);

    while(newline) 
    {
        newline = get_next_line(file); // Get the next line from the file
        if (newline == NULL) // If NULL is returned (EOF or error)
		{
			break; // Exit the loop
		}
        printf("newline %d -> %s", b, newline); // Print the line
		free(newline); // Free the line after printing to prevent memory leaks

        a++; // Increment line counter
        b++; // Increment line number
    }
	free(tmp); // Free the line after printing to prevent memory leaks
	tmp = NULL;
    return (0); // Return success
}